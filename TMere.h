/*************************************************************************
                           TMere  -  Tâche gérant toutes les tâches
                             -------------------
    début                : 16/03/15
    copyright            : (C) 2015 par Franck Meyer
    e-mail               : franck.meyer@insa-lyon.fr
*************************************************************************/

//---------- Interface de la tâche <TMere> (fichier TMere.h) -------
#ifndef TMERE_H
#define TMERE_H

//------------------------------------------------------------------------
// Rôle de la tâche <TMere>
//	La tâche mère a pour but de gérer les autres tâches (initialisation et
//		destruction)
//
//------------------------------------------------------------------------

/////////////////////////////////////////////////////////////////  INCLUDE
//------------------------------------------------------------------ Types

	/** définition des couleurs disponibles pour les feux de circulation */
enum Colors{VERT, ORANGE, ROUGE};

	/** définition de la structure de la mémoire partagée de gestion de couleur des feux */
struct couleurs
{
	Colors colNS; // int
	Colors colEO; // int
};

	/** définition de la structure de la mémoire partagée de gestion de durée des feux*/
struct durees
{
	int dureeNS;
	int dureeEO;
};


	/** Case du tableau de sémaphore permettant le mutex pour chaque mémoire partagée */
const unsigned int colorsLoc = 0;
const unsigned int dureesLoc = 0;

#endif //TMERE_H
