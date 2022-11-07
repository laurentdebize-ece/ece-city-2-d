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

int afficherPlacerUneConstruction(Case** matriceCase, Case caseAConstruire, int* constructionPossible, int typeDeContruction){ // afficherPlacerUneHabitation (matriceCase, matriceCase[ligneAConstruire][colonneAConstruire], &constructionPossible, typeDeConstruction);

    ALLEGRO_COLOR vert;
    vert = al_map_rgb(57, 255, 20);

    if(typeDeContruction == 2) { // On construit une habitation 3*3
        for (int i = caseAConstruire.ligne; i < caseAConstruire.ligne + 3; i++) {
            for (int j = caseAConstruire.colonne; j < caseAConstruire.colonne + 3; j++) {

                if (matriceCase[i][j].type != 0) {
                    *constructionPossible = 0;
                    return 1;
                }
            }
        }

        al_draw_filled_rectangle((float)caseAConstruire.x, (float)caseAConstruire.y, (float)caseAConstruire.x + TAILLE_CASE*3, (float)caseAConstruire.y + TAILLE_CASE*3, vert);
        *constructionPossible = 1;
        return 0;
    }
    else if(typeDeContruction == 7 || typeDeContruction == 8) { // On construit un chateau ou une centrale 4*6
        for (int i = caseAConstruire.ligne; i < caseAConstruire.ligne + 6; i++) {
            for (int j = caseAConstruire.colonne; j < caseAConstruire.colonne + 4; j++) {

                if (matriceCase[i][j].type != 0) {
                    *constructionPossible = 0;
                    return 1;
                }
            }
        }

        al_draw_filled_rectangle((float)caseAConstruire.x, (float)caseAConstruire.y, (float)caseAConstruire.x + TAILLE_CASE*4, (float)caseAConstruire.y + TAILLE_CASE*6, vert);
        *constructionPossible = 1;
        return 0;
    }
    else{
        printf("Erreur afficherPlacerUneConstruction : type inconnu");
        return -1;
    }
}

int placerUneConstruction(Case** matriceCase, Case caseAConstruire, int constructionPossible, int typeDeConstruction){ // placerUneConstruction (matriceCase, matriceCase[ligneAConstruire][colonneAConstruire], constructionPossible, typeDeConstruction);

    if (constructionPossible == 1){

        //On place une habitation
        if(typeDeConstruction == 2) {
            for (int i = caseAConstruire.ligne; i < caseAConstruire.ligne + 3; i++) {
                for (int j = caseAConstruire.colonne; j < caseAConstruire.colonne + 3; j++) {

                    matriceCase[i][j].type = 2; //On met un terrain vague
                }
            }
            dessinerCarte(matriceCase);
            return 0;
        }

        //On place un chateau
        else if(typeDeConstruction == 7){
            for (int i = caseAConstruire.ligne; i < caseAConstruire.ligne + 6; i++) {
                for (int j = caseAConstruire.colonne; j < caseAConstruire.colonne + 4; j++) {

                    matriceCase[i][j].type = 7; //On met un chateau
                }
            }
            dessinerCarte(matriceCase);
            return 0;
        }

        //On place une centrale
        else if(typeDeConstruction == 8) {
            for (int i = caseAConstruire.ligne; i < caseAConstruire.ligne + 6; i++) {
                for (int j = caseAConstruire.colonne; j < caseAConstruire.colonne + 4; j++) {

                    matriceCase[i][j].type = 8; //On met une centrale
                }
            }
            dessinerCarte(matriceCase);
            return 0;
        }
        else{
            printf("Erreur placerUneConstruction : type inconnu");
            return -1;
        }
    }else{
        return 1;
    }
}