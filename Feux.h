/*************************************************************************
                           Feux  -  gestion des feux
                             -------------------
    début                : 16/03/15
    copyright            : (C) 2015 par Franck Meyer
    e-mail               : franck.meyer@insa-lyon.fr
*************************************************************************/

//---------- Interface de la tâche <Feux> (fichier Feux.h) -------
#ifndef FEUX_H
#define FEUX_H

//------------------------------------------------------------------------
// Rôle de la tâche <Feux>
//
//	La tâche Feux a pour Rôle de gérer les feux du carrefour sur les 2 axes.
//------------------------------------------------------------------------

pid_t CreerEtInitialiserFeux(int mtxFeux, int mColor, int mDuree);
// Mode d'emploi :
//	<mtxFeux> : Identifiant du tableau de sémaphore permettant la mise en place d'un mutex
//	<mColor> : L'identifiant de la mémoire partagée contenant la couleur des feux
//	<mDuree> : L'identifiant de la mémoire partagée contenant la durée
// Contrat :
//		- <mtxFeux> est un tableau de sémaphores de 2 cases, dont la première sert de mutex
//			à <mColor>, et la seconde à <mDuree>
//		- <mColor> est l'ID d'un mémoire partagée contenant 2 entiers
//		- <mDuree> est l'ID d'un mémoire partagée contenant 2 entiers

#endif // FEUX_H
