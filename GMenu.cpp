/*************************************************************************
                           GMenu  -  description
                             -------------------
    début                : 16/03/15
    copyright            : (C) 2015 par Robin Royer
    e-mail               : robin.royer@insa-lyon.fr
*************************************************************************/

//---------- Réalisation de la tâche <GMenu> (fichier GMenu.cpp) ---

/////////////////////////////////////////////////////////////////  INCLUDE
//-------------------------------------------------------- Include système
#include <sys/types.h>
#include <unistd.h>
#include <cstdlib>
#include <cstdlib>
#include <signal.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <unistd.h>
#include <signal.h>
#include <sys/msg.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>



//------------------------------------------------------ Include personnel
#include "GMenu.h"
#include "Menu.h"
#include "Outils.h"
#include "Generateur.h"
#include "Voiture.h"
#include "TMere.h"


///////////////////////////////////////////////////////////////////  PRIVE
//------------------------------------------------------------- Constantes

//------------------------------------------------------------------ Types

//---------------------------------------------------- Variables statiques
    //initialysé a false au cas ou on ferme l'application de suite
static bool generateurActif=false;
static unsigned int numVoiture = 1;
static durees * dureeFeux;
static pid_t pidGenerateur;
static int balVoiture;
static int MaxVoitureManuel = 199;

//------------------------------------------------------ Fonctions privées
//static type nom ( liste de paramètres )
// Mode d'emploi :
//
// Contrat :
//g
// Algorithme :
//
//{
//} //----- fin de nom

//////////////////////////////////////////////////////////////////  PUBLIC
//---------------------------------------------------- Fonctions publiques

pid_t CreerEtInitialiserGMenu(pid_t pidGene, int mtxFeux, int mDuree, int balCar)
{
	pid_t pGMenu;
	

	
	pidGenerateur=pidGene;
	balVoiture=balCar;

	// on attahce la mémoire partagée
	dureeFeux =(durees*) shmat(mDuree,NULL,0);

	if((pGMenu = fork()) == 0)
	{

		Menu();
		
	}
	else
	{
		return pGMenu;
	}
}

void Commande ( char code )
{
	if(code == 'Q'){

		// Si le generateur est etteint à la fin, on a un waitpid infini
		if (!generateurActif)
			kill(pidGenerateur,SIGCONT);
		//Detachement de la mémoire partagée
		shmdt(dureeFeux);
		exit(0);
	}

	if (code=='G')
	{
		if (generateurActif)
		{
			kill(pidGenerateur,SIGSTOP);
			generateurActif=false;
			//Modification de  l'affichage 
			Effacer(MESSAGE);
			Effacer(ETAT_GENERATEUR);
			Afficher(ETAT_GENERATEUR,"OFF",GRAS);
			Afficher(MESSAGE,"Le generateur a été eteint");
		}
		else
		{
			kill(pidGenerateur,SIGCONT);
			generateurActif=true;
			//Modification de l'affichage 
			Effacer(MESSAGE);
			Effacer(ETAT_GENERATEUR);
			Afficher(ETAT_GENERATEUR,"ON",GRAS);
			Afficher(MESSAGE,"Le generateur a été activé");
		}
	}
}

void Commande ( TypeVoie entree, TypeVoie sortie )
{
	//gérer le numero de la voiture
	//création de la voiture
	struct Voiture voitureManuelle ={entree, sortie, numVoiture};
	//création et envoit du message 
	struct MsgVoiture message={(long)(entree), voitureManuelle};
	msgsnd(balVoiture, &message,  sizeof (MsgVoiture), 0);

	

	//Modification de l'affichage
	Effacer(MESSAGE);
	OperationVoie(PLUS,entree);
	Afficher(MESSAGE,"Votre nouvelle voiture a été ajouté");
	Effacer(NUMERO);
	Afficher(NUMERO,numVoiture,GRAS);
	Effacer(ENTREE);
	Afficher(ENTREE,entree,GRAS);
	Effacer(SORTIE);
	Afficher(SORTIE,sortie,GRAS); 

	//incremente le numero de voiture
	if (numVoiture>numeroMaxManuel) numVoiture=1;
	else numVoiture++;

}

void Commande ( TypeVoie voie, unsigned int duree )
{
	/** structures pour les opérations sur la durée (lecture) */
		struct sembuf getDLock;
		getDLock.sem_num = dureesLoc;
		getDLock.sem_op = -1;
		getDLock.sem_flg = 0;

		struct sembuf releaseDLock;
		releaseDLock.sem_num = dureesLoc;
		releaseDLock.sem_op = 1;
		releaseDLock.sem_flg = 0;

	if( ( voie == OUEST ) || ( voie == EST ))
	{
		//Ecriture sur la memoire paratagée, protégée par semaphore
		semop(dureesLoc,&getDLock,1);
		dureeFeux->dureeEO = duree;
		semop(dureesLoc,&releaseDLock,1);

		//Modification de l'affichage
		Effacer(MESSAGE);
		Afficher(MESSAGE,"La durée des feux de l'axe EO a changé");
	}

	if( ( voie == SUD ) || ( voie == NORD ))
	{
		//Ecriture sur la memoire partagée, protégée par semaphore
		semop(dureesLoc,&getDLock,1);
		dureeFeux->dureeNS = duree;
		semop(dureesLoc,&releaseDLock,1);

		//Modification de l'affichage
		Effacer(MESSAGE);
		Afficher(MESSAGE,"La durée des feux de l'axe NS a changé");
	}
	
}
