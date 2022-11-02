#ifndef ECE_CITY_FONCTIONS_H
#define ECE_CITY_FONCTIONS_H

#include "stdio.h"
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>

#define LARGEUR_FENETRE 1024
#define HAUTEUR_FENETRE 768
#define NB_COLONES 45
#define NB_LIGNES 35

    //**********En nombre d'habitant**********//
#define TERRAIN_VAGUE 0
#define CABANE 10
#define MAISON 50
#define IMMEUBLE 100
#define GRATTE_CIEL 1000



    //**********Constructions**********//
typedef struct {
    int timer, niveau, nbHabitants,
        alimEau, alimElec;
}Habitation;

typedef struct {
    int coordonneesHG, coordonneesBD,
        niveau, capacite, quantiteDistribuee;
}Chateau;

typedef struct {
    int coordonneesHG, coordonneesBD,
        niveau, capacite, quantiteDistribuee;
}Centrale;



typedef struct {
    int argentBanque, nbHabitants, timer,
            coutCentrale, coutChateau, coutRoute, coutTerrainVague;
}Global;

typedef struct {
    int x, y, type;
    Habitation* pHabitation;
    Chateau* pChateau;
    Centrale* pCentrale;
}Case;






#endif