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
#define TAILLE_CASE 20

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
        alimEau, alimElec;
}Habitation;

typedef struct {
    int coordXHG, coordYHG,
        niveau, capacite, quantiteDistribuee;
}Chateau;

typedef struct {
    int coordXHG, coordYHG,
        niveau, capacite, quantiteDistribuee;
}Centrale;



typedef struct {
    int argentBanque, nbHabitants, timer,
            coutCentrale, coutChateau, coutRoute, coutTerrainVague;
}Global;

typedef struct {
    int x, y, colonne, ligne, type;
    Habitation* pHabitation;
    Chateau* pChateau;
    Centrale* pCentrale;
}Case;




int convertirEnCase(int x, int y,  int* ligne, int* colonne);
int afficherPlacerUneRoute(Case caseAConstruire, int* contructionPossible); // afficherPlacerUneRoute (matriceCase[ligneAConstruire][colonneAConstruire], &constructionPossible);
int placerUneRoute(Case** matriceCase, Case caseAConstruire, int constructionPossible); // placerUneRoute (matriceCase, matriceCase[ligneAConstruire][colonneAConstruire], constructionPossible);

#endif