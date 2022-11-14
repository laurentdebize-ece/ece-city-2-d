#ifndef ECE_CITY_FONCTIONS_H
#define ECE_CITY_FONCTIONS_H

#include "stdio.h"
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>


#define LARGEUR_FENETRE 1150
#define HAUTEUR_FENETRE 780
#define NB_COLONNES 45
#define NB_LIGNES 35
#define TAILLE_CASE 20
#define DECALAGE_GRILLE_X 125
#define DECALAGE_GRILLE_Y 40

#define MARGE_EAU_POUR_EVOLUER 0.7 // Soit 70%
#define MARGE_ELEC_POUR_EVOLUER 0.7 // Soit 70%

    //**********En nombre d'habitant**********//
#define TERRAIN_VAGUE 0
#define CABANE 10
#define MAISON 50
#define IMMEUBLE 100
#define GRATTE_CIEL 1000


    //**********Constructions**********//
typedef struct {
    int coordXHG, coordYHG,

        niveau, nbHabitants, timerHabitation,

        alimEau, alimElec, nbCaseEau, parcoureMatriceHabitation;

        alimEauOuiNon,// 0 non, 1 partielement, 2 completement
        alimElecOuiNon; // 0 non, 1 oui

    bool estDessine;

}Habitation;

typedef struct {
    int coordXHG, coordYHG,
        niveau, capacite, quantiteDistribuee;

    int distribution;//0 ou 1 (en train de distribuer ou non)

    bool estDessine;

}Chateau;

typedef struct {
    int coordXHG, coordYHG,
        niveau, capacite, quantiteDistribuee;
    int distribution;
    bool estDessine;
}Centrale;



typedef struct {
    int argentBanque, nbHabitants, timerPartie, modeDeJeu, //1=communiste, 2=capitaliste
            coutCentrale, coutChateau, coutRoute, coutTerrainVague, nbHabitation;
}Global;

typedef struct {

    int distribEau,
        x, y, colonne, ligne, type;
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


int convertirEnCase(int x, int y,  int* ligne, int* colonne);
int afficherPlacerUneRoute(Case** matriceCase, Case caseAConstruire, int* contructionPossible); // afficherPlacerUneRoute (matriceCase[ligneAConstruire][colonneAConstruire], &constructionPossible);
int placerUneRoute(Case** matriceCase, Case caseAConstruire, int constructionPossible); // placerUneRoute (matriceCase, matriceCase[ligneAConstruire][colonneAConstruire], constructionPossible);
int afficherPlacerUneConstruction(Case** matriceCase, Case caseAConstruire, int* constructionPossible, int typeDeContruction); // afficherPlacerUneConstruction (matriceCase, matriceCase[ligneAConstruire][colonneAConstruire], &constructionPossible, typeDeConstruction);
int placerUneConstruction(Case** matriceCase, Case caseAConstruire, int constructionPossible, int typeDeConstruction); // placerUneConstruction (matriceCase, matriceCase[ligneAConstruire][colonneAConstruire], constructionPossible, typeDeConstruction);

int payer(Global* structureglobale, int cout);
int calculerNbHabitants(Case** matriceCase);
void evolutionHabitation(Case** matriceCase, Global* structureGlobale, Habitation* habitationAEvoluer, int ligneAEvoluer, int colonneAEvoluer);

#endif