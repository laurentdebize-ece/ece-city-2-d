#ifndef ECE_CITY_LE_JEU_H
#define ECE_CITY_LE_JEU_H

/*
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <assert.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>*/

#include "../Fonctions/Fonctions.h"

int ecranQuitter(ALLEGRO_EVENT_QUEUE *queue, ALLEGRO_EVENT event, Case** matriceCases, Global* structureGlobale);
int leJeu (ALLEGRO_DISPLAY* fenetre);
void afficherInterface(ALLEGRO_DISPLAY* fenetre);

#endif
