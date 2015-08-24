/*************************************************************************
                           GMenu  -  description
                             -------------------
    début                : 16/03/15
    copyright            : (C) 2015 par Robin Royer
    e-mail               : XXX
*************************************************************************/

//---------- Interface de la tâche <GMenu> (fichier GMenu.h) -------
#if ! defined ( GMENU_H )
#define GMENU_H

//------------------------------------------------------------------------
// Rôle de la tâche <GMenu>
//
//
//------------------------------------------------------------------------
#include "Outils.h"

#include <sys/types.h>

pid_t CreerEtInitialiserGMenu(pid_t pidGene, int mtxFeux, int mDuree, int balCar);

void Commande ( char code );
void Commande ( TypeVoie entree, TypeVoie sortie );
void Commande ( TypeVoie voie, unsigned int duree );

#endif // GMENU_H
