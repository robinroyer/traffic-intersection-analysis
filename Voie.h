/*************************************************************************
                           Voie  -  description
                             -------------------
    début                : 16/03/15
    copyright            : (C) 2015 par Robin Royer
    e-mail               : XXX
*************************************************************************/

//---------- Interface de la tâche <Voie> (fichier Voie.h) -------
#if ! defined ( VOIE_H )
#define VOIE_H

//------------------------------------------------------------------------
// Rôle de la tâche <Voie>
//
//
//------------------------------------------------------------------------
#include "Outils.h"

pid_t CreerEtInitialiserVoie(TypeVoie voie, int msgCars, int mtxFeux, int mColors/* memoires partagees ou autres s'il y en a*/);

#endif // VOIE_H
