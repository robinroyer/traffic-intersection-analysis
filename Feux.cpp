 /*************************************************************************
						   Feux  -  Gestion des feux
							 -------------------
	début                : 16/03/15
	copyright            : (C) 2015 par Franck Meyer
	e-mail               : franck.meyer@insa-lyon.fr
*************************************************************************/

//---------- Réalisation de la tâche <Feux> (fichier Feux.cpp) ---

/////////////////////////////////////////////////////////////////  INCLUDE
//-------------------------------------------------------- Include système
#include <cstdlib>
#include <signal.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <unistd.h>

//------------------------------------------------------ Include personnel
#include "Feux.h"
#include "TMere.h"

#include "Outils.h"

///////////////////////////////////////////////////////////////////  PRIVE

//---------------------------------------------------- Variables statiques
static couleurs* couleursFeux;
static durees* dureesFeux;

//------------------------------------------------------ Fonctions privées

static void handleEnd(int noSignal)
// Mode d'emploi :
//		handler de fin d'application. Il permet de terminer proprement l'application
//			lors de l'envoi d'un SIGUSR2
//	<noSignal> : Numéro du signal ayant déclenché le handler
//
// Contrat : aucun
{
	if(noSignal == SIGUSR2)
	{
		/** Désattachement des mémoires partagées */
		shmdt(couleursFeux);
		shmdt(dureesFeux);

		exit(0);
	}
} // fin de handleEnd



static void couleurFeu(TypeZone tz, Colors couleur)
// Mode d'emploi :
//		Méthode permettant d'afficher la couleur du feu sur une zone donnée, à partir de
//			l'énumération <couleur>
//	<tz> : le type de zone où écrire (COULEUR_AXE_NS ou COULEUR_AXE_EO)
//	<couleur> : La couleur du feu (VERT, ORANGE ou ROUGE)
//
// Contrat : tz est l'une des 2 zones sus-citées
{
	switch (couleur)
	{
		case VERT:
			Afficher(tz, "Vert  ", GRAS);
			break;

		case ORANGE:
			Afficher(tz, "Orange", GRAS, INVERSE);
			break;

		case ROUGE:
			Afficher(tz, "Rouge ", GRAS, INVERSE);
			break;
	}

} // fin de couleurFeu

//////////////////////////////////////////////////////////////////  PUBLIC
//---------------------------------------------------- Fonctions publiques

pid_t CreerEtInitialiserFeux(int mtxFeux, int mColor, int mDuree)
// Mode d'emploi :
//	<mtxFeux> : Identifiant du tableau de sémaphore permettant la mise en place d'un mutex
//	<mColor> : L'identifiant de la mémoire partagée contenant la couleur des feux
//	<mDuree> : L'identifiant de la mémoire partagée contenant la durée
// Contrat :
//		- <mtxFeux> est un tableau de sémaphores de 2 cases, dont la première sert de mutex
//			à <mColor>, et la seconde à <mDuree>
//		- <mColor> est l'ID d'un mémoire partagée contenant 2 entiers
//		- <mDuree> est l'ID d'un mémoire partagée contenant 2 entiers
{
	pid_t pFeux;

	


	if((pFeux = fork()) == 0)
	{
		/** structures pour les opérations sur la durée (lecture) */
		struct sembuf getDLock;
		getDLock.sem_num = dureesLoc;
		getDLock.sem_op = 1;
		getDLock.sem_flg = 0;

		struct sembuf releaseDLock;
		releaseDLock.sem_num = dureesLoc;
		releaseDLock.sem_op = -1;
		releaseDLock.sem_flg = 0;


		/** structures pour les opérations sur la couleur (écriture) */
		struct sembuf getCLock;
		getCLock.sem_num = colorsLoc;
		getCLock.sem_op = 4;
		getCLock.sem_flg = 0;


		struct sembuf releaseCLock;
		releaseCLock.sem_num = colorsLoc;
		releaseCLock.sem_op = -4;
		releaseCLock.sem_flg = 0;

		/** Initialisation des variables locales */
		int tempsNS = 0;
		int tempsEO = 0;
		Colors couleurNS = ROUGE;
		Colors couleurEO = ROUGE;
		bool lastNS = false; // booléen permettant de savoir qui doit passer au vert

		couleursFeux = (couleurs*)shmat(mColor, NULL, 0);
		dureesFeux = (durees*)shmat(mDuree, NULL, 0);
		
		
		/** Mappage des signaux */
		struct sigaction action;
		action.sa_handler = handleEnd;
		sigemptyset(&action.sa_mask);
		action.sa_flags = 0;

		sigaction(SIGUSR2, &action, NULL);


		for(;;)
		{
			/** Gestion de l'axe NS */
			if(tempsNS <= 0)
			{
				switch (couleurNS)
				{
					case ROUGE:
						if(!lastNS)
						{
							couleurNS = VERT;
							lastNS = !lastNS;

							/** Récupération des durées, avec mutex */
							semop(mtxFeux, &getDLock, 1);

							tempsNS = dureesFeux->dureeNS;
							tempsEO = dureesFeux->dureeEO;

							semop(mtxFeux, &releaseDLock, 1);

							Afficher(DUREE_AXE_NS, tempsNS);
							Afficher(DUREE_AXE_EO, tempsEO);

							tempsEO = tempsNS + 5;
						}

						break;
					case VERT:
						couleurNS = ORANGE;
						tempsNS = 3;
						break;
					case ORANGE:
						couleurNS = ROUGE;
						tempsNS = 2;
						break;
				}
			}

			/** Gestion de l'axe EO */
			if(tempsEO <= 0)
			{
				switch (couleurEO)
				{
					case ROUGE:
						if(lastNS)
						{
							couleurEO = VERT;
							lastNS = !lastNS;


							/** Récupération des durées, avec mutex */
							semop(mtxFeux, &getDLock, 1);

							tempsNS = dureesFeux->dureeNS;
							tempsEO = dureesFeux->dureeEO;

							semop(mtxFeux, &releaseDLock, 1);

							Afficher(DUREE_AXE_NS, tempsNS);
							Afficher(DUREE_AXE_EO, tempsEO);

							tempsNS = tempsEO + 5;
						}
						break;
					case VERT:
						couleurEO = ORANGE;
						tempsNS = 3;
						break;
					case ORANGE:
						couleurEO = ROUGE;
						tempsNS = 2;
						break;
				}
			}

			Afficher(TEMPS_AXE_NS, tempsNS);
			Afficher(TEMPS_AXE_EO, tempsEO);
			couleurFeu(COULEUR_AXE_NS, couleurNS);
			couleurFeu(COULEUR_AXE_EO, couleurEO);

				/** Ecriture des couleurs des feux, avec mutex */
			semop(mtxFeux, &getCLock, 1);

			couleursFeux->colNS = couleurNS;
			couleursFeux->colEO = couleurEO;

			semop(mtxFeux, &releaseCLock, 1);
			
			tempsNS--;
			tempsEO--;
			sleep(1);

		}
	}
	else
	{
		return pFeux;
	}
} //----- fin de CreerEtInitialiserFeux
