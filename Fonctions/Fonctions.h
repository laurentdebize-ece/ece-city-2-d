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
#define NB_COLONNES 45
#define NB_LIGNES 35

    //**********En nombre d'habitant**********//
#define TERRAIN_VAGUE 0
#define CABANE 10
#define MAISON 50
#define IMMEUBLE 100
#define GRATTE_CIEL 1000



    //**********Constructions**********//
typedef struct {
    int coordXHG, coordYHG,
        timer, niveau, nbHabitants,
        alimEau, alimElec,nbCaseEau;
}Habitation;

typedef struct {
    int coordXHG, coordYHG,
        niveau, capacite, quantiteDistribuee;
    int distribution;
}Chateau;

typedef struct {
    int coordXHG, coordYHG,
        niveau, capacite, quantiteDistribuee;
}Centrale;



typedef struct {
    int argentBanque, nbHabitants, timer,
            coutCentrale, coutChateau, coutRoute, coutTerrainVague,nbHabitation;
}Global;

typedef struct {
    int x, y, type;
    int distribEau;
    Habitation* pHabitation;
    Chateau* pChateau;
    Centrale* pCentrale;
}Case;

typedef struct maillon{
    int num;
    int x,y;
    struct maillon*suiv;
}t_maillon;

typedef struct file{
    t_maillon*tete; //pointeur sur le premier maillon
    t_maillon*fin; //pointeur sur le dernier maillon
}t_file;




#endif