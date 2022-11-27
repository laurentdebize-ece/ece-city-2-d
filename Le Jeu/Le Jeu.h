#ifndef ECE_CITY_LE_JEU_H
#define ECE_CITY_LE_JEU_H

#include "../Fonctions/Fonctions.h"

int ecranQuitter(ALLEGRO_EVENT_QUEUE *queue, ALLEGRO_EVENT event, Case** matriceCase, Global* structureGlobale);
int leJeu (ALLEGRO_DISPLAY* fenetre, int modeDeJeu, bool nouvellePartie);
void afficherInterface();

#endif
