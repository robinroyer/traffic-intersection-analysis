/*************************************************************************
                           Voie  -  Gestion d'une voie
                             -------------------
    début                : 16/03/15
    copyright            : (C) 2015 par Robin Royer
    e-mail               : robin.royer@insa-lyon.fr
*************************************************************************/

//---------- Réalisation de la tâche <Voie> (fichier Voie.cpp) ---

/////////////////////////////////////////////////////////////////  INCLUDE
//-------------------------------------------------------- Include système

#include <unistd.h>


#include <sys/ipc.h>
#include <sys/msg.h>
#include <cstdlib>
#include <signal.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <unistd.h>
#include <vector>
#include <sys/wait.h> 


//------------------------------------------------------ Include personnel
#include "Voie.h"
#include "TMere.h"
#include "Voiture.h"
#include "Outils.h"

///////////////////////////////////////////////////////////////////  PRIVE
//------------------------------------------------------------- Constantes

//------------------------------------------------------------------ Types

//---------------------------------------------------- Variables statiques
static couleurs* couleursFeux;
static std::vector<pid_t> voitureRoulante;
static int balVoiture;
static TypeVoie voie;


static void handlFinVoiture(int noSignal)
{
	if(noSignal == SIGCHLD)
	{

		int status;
		pid_t voitureMorte =wait(&status);
		std::vector<pid_t> ::iterator it;
		it=voitureRoulante.begin();
		while((*it) != voitureMorte)
		{
			//on se place sur le bon pid
			it++;
			
		}	
 		voitureRoulante.erase(it);
			
		
	}
}


static void handleEnd(int noSignal)
// Mode d'emploi :
//		handler de fin d'application. Il permet de terminer proprement l'application
//			lors de l'envoi d'un SIGUSR2
//	<noSignal> : Numéro du signal ayant déclenché le handler
//
// Contrat : aucun
{
	struct sigaction ignore;
	ignore.sa_handler = SIG_IGN;
	sigemptyset(&ignore.sa_mask);
	ignore.sa_flags = 0;
	sigaction(SIGCHLD, &ignore, NULL);
	if(noSignal == SIGUSR2)
	{
		//on arrete proprement les voitures qui se déplacent encore

		for (pid_t voiture: voitureRoulante)
  		{
  			kill(voiture,SIGUSR2);
  		}

		for(int i = 0; i < voitureRoulante.size(); i++)
		{
			waitpid(-1, NULL, 0);
		}

		//liberation de la memeoire partagée
		shmdt(couleursFeux);
		exit(0);
	}
} // fin de handleEnd


static Colors regarderFeu(TypeVoie tv){
	// Mode d'emploi :
//		permet de récuperer la couleur du feu en fonction de la voie considérée
//	<TypeVoie> : le type de la voie qui l'indentifie NORD /SUD/ EST/ OUEST
//
// Contrat : aucun
	switch (tv)
			{
				case NORD:
				case SUD:
					return couleursFeux->colNS;
					break;

				case OUEST:
				case EST:
					return couleursFeux->colEO;
					break;
			}
}							

//////////////////////////////////////////////////////////////////  PUBLIC
//---------------------------------------------------- Fonctions publiques

 

pid_t CreerEtInitialiserVoie( TypeVoie tv , int msgCars, int mtxFeux,int mColor)
// Algorithme :
//
{
	pid_t pVoie;
	pid_t voiture;
	voie=tv;
	balVoiture=msgCars;

	if((pVoie = fork()) == 0)
	{

	

		/** structures pour les opérations sur la couleur (lecture) */
		struct sembuf getCLock;
		getCLock.sem_num = colorsLoc;
		getCLock.sem_op = 1;
		getCLock.sem_flg = 0;


		struct sembuf releaseCLock;
		releaseCLock.sem_num = colorsLoc;
		releaseCLock.sem_op = -1;
		releaseCLock.sem_flg = 0;


		//acces  à la memoire partagée
		couleursFeux = (couleurs*)shmat(mColor, NULL, 0);

		//initialisation de variable locale
		Colors couleurFeuVoie = ROUGE;

		//message de la Boite aux lettre
		struct MsgVoiture nouvelleVoiture;


		// Mappage des signaux 
				//---------------------------------SIGUSR2
		struct sigaction action;
		action.sa_handler = handleEnd;
		sigemptyset(&action.sa_mask);
		action.sa_flags = 0;

		sigaction(SIGUSR2, &action, NULL);
				//---------------------------------SIGCHLD
		struct sigaction actionVoitureMorte;
		actionVoitureMorte.sa_handler = handlFinVoiture;
		sigemptyset(&action.sa_mask);
		actionVoitureMorte.sa_flags=0;

		sigaction(SIGCHLD, &actionVoitureMorte, NULL);  
	
		for(;;)
		{ 
			

			// on test si il y a une nouvelle voiture dansq la BAL
			if (msgrcv(msgCars, &nouvelleVoiture, sizeof(MsgVoiture), tv,1)!=-1) 
			{
				
				DessinerVoitureFeu( nouvelleVoiture.uneVoiture.numero, nouvelleVoiture.uneVoiture.entree, nouvelleVoiture.uneVoiture.sortie);
				OperationVoie(MOINS,voie);

				do
				{
					sleep(1);
					// on regarde si le feu a changé de couleur
					semop(mtxFeux, &getCLock, 1);
					couleurFeuVoie = regarderFeu(voie);
					semop(mtxFeux, &releaseCLock, 1);
				}while(couleurFeuVoie != VERT);

				//on lance la voiture et stocke son pid
				voiture = DeplacerVoiture( nouvelleVoiture.uneVoiture.numero, nouvelleVoiture.uneVoiture.entree, nouvelleVoiture.uneVoiture.sortie);
				voitureRoulante.push_back(voiture);
			}
			
		
		}
	}
	else
	{


		return pVoie;
	}
} //----- fin de Nom

