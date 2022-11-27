#ifndef ECE_CITY_INITIALISATION_H
#define ECE_CITY_INITIALISATION_H

#include "../Fonctions/Fonctions.h"

void initCases(Case** matriceCases, bool nouvellePartie);
void initGlobal(Global* structureGlobale,bool nouvellePartie);
void sauvegardeJeu(Case** matriceCases, Global* structureGlobale);
void chargement(Case** matriceCases, Global* structureGlobale);
void FonctionNouvellePartie();


#endif