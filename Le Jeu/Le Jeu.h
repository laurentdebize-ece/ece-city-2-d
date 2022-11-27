#ifndef ECE_CITY_LE_JEU_H
#define ECE_CITY_LE_JEU_H

#include "../Fonctions/Fonctions.h"

int ecranQuitter(ALLEGRO_DISPLAY* fenetre, ALLEGRO_EVENT_QUEUE *queue, ALLEGRO_EVENT event, ALLEGRO_TIMER  *timer, Case** matriceCase, Global* structureGlobale);
int leJeu (ALLEGRO_DISPLAY* fenetre, int modeDeJeu, bool nouvellePartie);
void afficherInterface(ALLEGRO_DISPLAY* fenetre, Global* structureGlobale);

#endif
