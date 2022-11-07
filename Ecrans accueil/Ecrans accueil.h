#ifndef ECE_CITY_ECRANS_ACCUEIL_H
#define ECE_CITY_ECRANS_ACCUEIL_H
#include <stdio.h>
#include <allegro5/allegro.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <assert.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include "allegro5/allegro_primitives.h"

bool func_bouton(bool clic_mouse, int x_mouse, int y_mouse, int x1, int x2, int y1, int y2);

#define LARGEUR 930
#define HAUTEUR 524

void ecranAccueil(ALLEGRO_DISPLAY *fenetre);

#endif
