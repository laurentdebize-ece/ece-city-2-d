#ifndef ECE_CITY_FONCTIONS_H
#define ECE_CITY_FONCTIONS_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>



#define LARGEUR_FENETRE 1150
#define HAUTEUR_FENETRE 780
#define DECALAGE_GRILLE_X 125
#define DECALAGE_GRILLE_Y 40
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

typedef struct{
    int numChateau;
    int dejaAlim;
    int nbCases;

}AlimEau;

typedef struct Habitation {
    int coordXHG, coordYHG,
        numero,
        niveau, nbHabitants, timerHabitation,

        alimEau, alimElec, nbCaseEau, parcoureMatriceHabitation,
        numChateauAlim,
        alimEauOuiNon,// 0 non, 1 partielement, 2 completement
        alimElecOuiNon; // 0 non, 1 oui

    AlimEau nbCasesParChateau[10];
    bool estDessine;
    bool marquage;
    struct Habitation*suiv;

}Habitation;

typedef struct {
    int coordXHG, coordYHG,
        niveau, capacite, quantiteDistribuee,numero,
        parcoursMatriceChateau;

    int distribution;//0 ou 1 (en train de distribuer ou non)

    bool estDessine;

}Chateau;

typedef struct {
    int coordXHG, coordYHG,
        niveau, capacite, quantiteDistribuee,numero,
        parcoursMatriceChateau;
    int distribution;
    bool estDessine;
    Habitation* tab[40];
}Centrale;


typedef struct {
    int argentBanque, nbHabitants, timerPartieSec, timerPartieMin, modeDeJeu, //1=communiste, 2=capitaliste
            coutCentrale, coutChateau, coutRoute, coutTerrainVague, nbHabitation, nbCentrale, nbChateau, timerPartieMois, timerPartieAnnee;
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
    int numRoute;
    struct maillon*suiv;
}t_maillon;


typedef struct file{
    t_maillon*tete; //pointeur sur le premier maillon
    t_maillon*fin;//pointeur sur le dernier maillonn
    Habitation*avant;
    Habitation*apres;
}t_file;



void distributionEau(Case** matriceCases,Global* global);
int distributionEvolutionEAU(Case** matriceCases,Global* global,Habitation* habitation);
void distributionElec(Case** matriceCases,Global* global);
int ouiNonEvolution(Case** matriceCases,Global* global,Habitation* habitation);


int convertirEnCase(int x, int y,  int* ligne, int* colonne);
int afficherPlacerUneRoute(Case** matriceCase, Case caseAConstruire, int* contructionPossible); // afficherPlacerUneRoute (matriceCase[ligneAConstruire][colonneAConstruire], &constructionPossible);
int placerUneRoute(Case** matriceCase, Case caseAConstruire, int constructionPossible); // placerUneRoute (matriceCase, matriceCase[ligneAConstruire][colonneAConstruire], constructionPossible);
int afficherPlacerUneConstruction(Case** matriceCase, Case caseAConstruire, int* constructionPossible, int typeDeContruction); // afficherPlacerUneConstruction (matriceCase, matriceCase[ligneAConstruire][colonneAConstruire], &constructionPossible, typeDeConstruction);

int placerUneConstruction(Case** matriceCase, Case caseAConstruire, int constructionPossible, int typeDeConstruction, Global* structureGlobale); // placerUneConstruction (matriceCase, matriceCase[ligneAConstruire][colonneAConstruire], constructionPossible, typeDeConstruction);


int payer(Global* structureglobale, int cout);
int calculerNbHabitants(Case** matriceCase);
void evolutionHabitation(Case** matriceCase, Global* structureGlobale, Habitation* habitationAEvoluer, int ligneAEvoluer, int colonneAEvoluer, int onPeutEvoluer);

bool func_bouton(bool clic_mouse, int x_mouse, int y_mouse, int x1, int x2, int y1, int y2);
void fonctionPause(ALLEGRO_DISPLAY* fenetre,  ALLEGRO_EVENT_QUEUE* queue, ALLEGRO_EVENT event, ALLEGRO_TIMER* timer, Case** matriceCase, int y1, int y2, int cas);
void fonctionNouvellePartie ();

#endif