#ifndef ECE_CITY_CARTE_H
#define ECE_CITY_CARTE_H

#include "../Fonctions/Fonctions.h"

void niveau1 (Case** pMatriceCase, Habitation* habitation);
void niveau2 (Case** pMatriceCase, Habitation* habitation);
void lireFichierCarte(Case** matriceCases);
void dessinerCarte(Case** matriceCases);
#endif