#ifndef ECE_CITY_CARTE_H
#define ECE_CITY_CARTE_H

#include "../Fonctions/Fonctions.h"

void niveau1 (Case** pMatriceCase);
void niveau2(Case** pMatriceCase);
void lireFichierCarte(Case** matriceCases,Global* structGlobal);
void dessinerCarte(Case** matriceCases);
void capaciteChateau (ALLEGRO_EVENT_QUEUE *queue, ALLEGRO_EVENT event, Case** pMatriceCase);

#endif