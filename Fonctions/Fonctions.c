#include "Fonctions.h"
#include "../Carte/Carte.h"


int convertirEnCase(int x, int y,  int* ligne, int* colonne) {

    int colonneTemporaire = (int)(x/TAILLE_CASE);
    int ligneTemporaire = (int)(y/TAILLE_CASE);

    if(ligneTemporaire >= NB_LIGNES || colonneTemporaire >= NB_COLONNES) {//souris en dehors la zone de jeu
        *colonne = -1;
        *ligne = -1;
        return 1;
    }
    else {
        *colonne = colonneTemporaire;
        *ligne = ligneTemporaire;
        return 0;
    }
}

int afficherPlacerUneRoute(Case caseAConstruire, int* constructionPossible){ // afficherPlacerUneRoute (matriceCase[ligneAConstruire][colonneAConstruire], &constructionPossible);

    if (caseAConstruire.type != 0){
        *constructionPossible = 0;
        return 1;
    }else{ //On affiche le surlignage en vert

        ALLEGRO_COLOR vert;
        vert = al_map_rgb(57, 255, 20);

        al_draw_filled_rectangle((float)caseAConstruire.x, (float)caseAConstruire.y, (float)caseAConstruire.x + TAILLE_CASE, (float)caseAConstruire.y + TAILLE_CASE, vert);
        *constructionPossible = 1;
        return 0;
    }
}

int placerUneRoute(Case** matriceCase, Case caseAConstruire, int constructionPossible){ // placerUneRoute (matriceCase, matriceCase[ligneAConstruire][colonneAConstruire], constructionPossible);

    if (constructionPossible == 1){

        matriceCase[caseAConstruire.ligne][caseAConstruire.colonne].type = 1;

        dessinerCarte(matriceCase);

        /*
        ALLEGRO_BITMAP* route = al_load_bitmap("../Images/route.jpg");
        if (!route){
            printf("Erreur chargement image : Route");
        }

        al_draw_bitmap(route, (float)caseAConstruire.x, (float)caseAConstruire.y, 0);

        al_destroy_bitmap(route);
        route = NULL;
         */
        return 0;
    }else{
        return 1;
    }
}