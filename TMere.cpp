/*************************************************************************
                           TMere  -  Tâche gérant les autres
                             -------------------
    début                : 16/03/15
    copyright            : (C) 2015 par Franck Meyer
    e-mail               : franck.meyer@insa-lyon.fr
*************************************************************************/

//---------- Réalisation de la tâche <TMere> (fichier TMere.cpp) ---

/////////////////////////////////////////////////////////////////  INCLUDE
//-------------------------------------------------------- Include système
#include <signal.h>
#include <sys/msg.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>


//------------------------------------------------------ Include personnel
#include "Feux.h"
#include "GMenu.h"
#include "TMere.h"
#include "Voie.h"

#include "Generateur.h"
#include "Heure.h"
#include "Menu.h"
#include "Outils.h"

///////////////////////////////////////////////////////////////////  PRIVE
//------------------------------------------------------------- Constantes
#define DROITS 0660
#define REFERENCE "./Carrefour"


//////////////////////////////////////////////////////////////////  PUBLIC
//---------------------------------------------------- Fonctions publiques

int main ( void )
{
		/** Masquage des signaux */
	struct sigaction ignore;
	ignore.sa_handler = SIG_IGN;
	sigemptyset(&ignore.sa_mask);
	ignore.sa_flags = 0;

	sigaction(SIGINT, &ignore, NULL);
	sigaction(SIGUSR1, &ignore, NULL);
	sigaction(SIGUSR2, &ignore, NULL);


		/** pID des processus fils */
	pid_t tHeure, tGMenu, tFeux, tGen;
	pid_t tVoie[4];


		/** Ressources partagées/critiques */
	int mColor, mDuree;
	int mtxFeux;
	int msgCars;

	
	
		/**
		* Phase d'initialisation
		*/

	
	
	InitialiserApplication(XTERM);

		/** Initialisation des sémaphores */
	mtxFeux = semget(ftok(REFERENCE, 42), 2, IPC_CREAT | DROITS);
		//Pour les couleurs des feux (index 0)
	semctl(mtxFeux, colorsLoc, 4, 4);
		//Pour la duree des feux (index 1)
	semctl(mtxFeux, dureesLoc, 1, 1);

		/** Initialisation de la boite à lettres */
	msgCars = msgget(ftok(REFERENCE, 42), IPC_CREAT | IPC_EXCL | DROITS);


		/** Initialisation des mémoires partagées */
	mColor = shmget(IPC_PRIVATE, 2 * sizeof(int), IPC_CREAT | IPC_EXCL | DROITS);
	mDuree = shmget(IPC_PRIVATE, 2 * sizeof(int), IPC_CREAT | IPC_EXCL | DROITS);

		/** Initialisation des valeurs des mémoires partagées */
	couleurs* couleursFeux = (couleurs*)shmat(mColor, NULL, 0);
	couleursFeux->colEO = ROUGE;
	couleursFeux->colNS = ROUGE;
	shmdt(couleursFeux);

	durees* dureesFeux = (durees*)shmat(mDuree, NULL, 0);
	dureesFeux->dureeNS = 20;
	dureesFeux->dureeEO = 10;
	shmdt(dureesFeux);


		/** Initialisation des tâches */
	tHeure = CreerEtActiverHeure();
	tGen = CreerEtActiverGenerateur(0, msgCars);

	tFeux = CreerEtInitialiserFeux( mtxFeux, mColor, mDuree);

	tVoie[0] = CreerEtInitialiserVoie(NORD, msgCars, mtxFeux, mColor);
	tVoie[1] = CreerEtInitialiserVoie(EST, msgCars, mtxFeux, mColor);
	tVoie[2] = CreerEtInitialiserVoie(SUD, msgCars, mtxFeux, mColor);
	tVoie[3] = CreerEtInitialiserVoie(OUEST, msgCars, mtxFeux, mColor);


	tGMenu = CreerEtInitialiserGMenu( tGen , mtxFeux, mDuree , msgCars);
	waitpid(tGMenu, NULL, 0);

	
	
		/**
		* Phase de destruction
		*/

	
	
		/** Destruction des fils */
	for(int i = 0; i < 4; i++)
	{
		kill(tVoie[i], SIGUSR2);
	}
	kill(tFeux, SIGUSR2);
	kill(tGen, SIGUSR2);
	kill(tHeure, SIGUSR2);

		/** Destruction des mémoires partagées */
	shmctl(mColor, IPC_RMID, 0);
	shmctl(mDuree, IPC_RMID, 0);

		/** Destruction de la boite à lettres */
	msgctl(msgCars, IPC_RMID, 0);

		/** Destruction des sémaphores */
	semctl(mtxFeux, 0, IPC_RMID, 4);

	TerminerApplication();

		/** Attente de la fin de la destruction de tous les fils */
	for(int i = 0; i < 7; i++)
	{
		waitpid(-1, NULL, 0);
	}

	return 0;
} //----- fin de main

