#include "Fonctions.h"
#include "../Carte/Carte.h"


#define TAILLE_X_CHATEAU 4
#define TAILLE_Y_CHATEAU 6
#define POURCENTAGE_EVOLUTION 0,7

//boucle for nbchateau faire distribution

int choixChateau(Case** matriceCases) {
    int nbChateau = 0;

    for (int i = 0; i < NB_LIGNES; i++) {
        for (int j = 0; j < NB_COLONNES; j++) {
            if (matriceCases[i][j].pChateau != NULL && matriceCases[i][j].type == 7) {
                nbChateau++;
            }
        }
    }
    return nbChateau;
}

void enfiler(t_file *f,int x,int y){
    t_maillon* tmp= malloc(sizeof(t_maillon));
    tmp->x=x;
    tmp->y=y;
    tmp->suiv=NULL;

    if(f->tete==NULL){
        f->tete=tmp;
        f->fin=tmp;
    }
    else{
        f->fin->suiv=tmp;
        f->fin=tmp;
    }
}

void defiler(t_file *f,int tab[2]){

    t_maillon* tmp=f->tete;
    if(f->tete == f->fin){
        f->fin=NULL;
        f->tete=NULL;
    }
    else {
        f->tete = f->tete->suiv;
    }
    tab[0]=tmp->x;
    tab[1]=tmp->y;

    free(tmp);
}

int bfsEau(Case** matriceCases,Habitation* habEau[],int x,int y){
    t_file f;
    f.tete = f.fin = NULL;
    int XY[2];
    int nbCases=0;
    int numHabitation=0;

    for (int i = 0; i < NB_LIGNES; i++) {
        for (int j = 0; j < NB_COLONNES; j++) {
            matriceCases[i][j].distribEau=0;
            matriceCases[i][j].pHabitation->nbCaseEau=0;
        }
    }

    enfiler(&f,x,y);
    matriceCases[y][x].distribEau=1;
    nbCases++;

    while (f.tete != NULL) {
        defiler(&f,XY);

        //vérifiaction des habitations autour

        if(matriceCases[ XY[1]-1 ][ XY[0] ].type==2 ||
            matriceCases[ XY[1]-1 ][ XY[0] ].type==3 ||
            matriceCases[ XY[1]-1 ][ XY[0] ].type==4 ||
            matriceCases[ XY[1]-1 ][ XY[0] ].type==5 ||
            matriceCases[ XY[1]-1 ][ XY[0] ].type==6){

            habEau[numHabitation]= matriceCases[ XY[1]-1 ][ XY[0] ].pHabitation;
            habEau[numHabitation]->nbCaseEau=nbCases;
            numHabitation++;

        }
        //Case droite
        if(matriceCases[ XY[1]+1 ][ XY[0] ].type==2 ||
        matriceCases[ XY[1]+1 ][ XY[0] ].type ==3 ||
        matriceCases[ XY[1]+1 ][ XY[0] ].type ==4 ||
        matriceCases[ XY[1]+1 ][ XY[0] ].type ==5||
        matriceCases[ XY[1]+1 ][ XY[0] ].type ==6){

            habEau[numHabitation]= matriceCases[ XY[1]+1 ][ XY[0] ].pHabitation;
            habEau[numHabitation]->nbCaseEau=nbCases;
            numHabitation++;

        }
        //Case dessus
        if(matriceCases[ XY[1] ][ XY[0]-1 ].type==2
        || matriceCases[ XY[1] ][ XY[0]-1 ].type ==3
        || matriceCases[ XY[1] ][ XY[0]-1 ].type ==4
        || matriceCases[ XY[1] ][ XY[0]-1 ].type ==5
        || matriceCases[ XY[1] ][ XY[0]-1 ].type ==6){

            habEau[numHabitation]= matriceCases[ XY[1] ][ XY[0]-1 ].pHabitation;
            habEau[numHabitation]->nbCaseEau=nbCases;
            numHabitation++;

        }
        //Case dessous
        if(matriceCases[ XY[1] ][ XY[0]+1 ].type==2
        || matriceCases[ XY[1] ][ XY[0]+1 ].type==3
        || matriceCases[ XY[1] ][ XY[0]+1 ].type==4
        || matriceCases[ XY[1] ][ XY[0]+1 ].type==5
        || matriceCases[ XY[1] ][ XY[0]+1 ].type==6){

            habEau[numHabitation]= matriceCases[ XY[1] ][ XY[0]+1 ].pHabitation;
            habEau[numHabitation]->nbCaseEau=nbCases;
            numHabitation++;

        }

        //vérification des routes autour pour la file

        //Case gauche
        if(matriceCases[ XY[1]-1 ][ XY[0] ].type==0 && matriceCases[ XY[1]-1 ][ XY[0] ].distribEau==0){

            enfiler(&f,XY[0],XY[1]-1);
            matriceCases[ XY[1]-1 ][ XY[0] ].distribEau=1;

        }
        //Case droite
        if(matriceCases[ XY[1]+1 ][ XY[0] ].type==0 && matriceCases[ XY[1]+1 ][ XY[0] ].distribEau==0){

            enfiler(&f,XY[0],XY[1]-1);
            matriceCases[ XY[1]+1 ][ XY[0]].distribEau=1;

        }
        //Case dessus
        if(matriceCases[ XY[1] ][ XY[0]-1 ].type==0 && matriceCases[ XY[1] ][ XY[0]-1 ].distribEau==0){

            enfiler(&f,XY[0]-1,XY[1]);
            matriceCases[ XY[1] ][ XY[0]-1 ].distribEau=1;

        }
        //Case dessous
        if(matriceCases[ XY[1] ][ XY[0]+1 ].type==0 && matriceCases[ XY[1] ][ XY[0]+1 ].distribEau==0){

            enfiler(&f,XY[0]+1,XY[1]);
            matriceCases[ XY[1] ][ XY[0]+1 ].distribEau=1;

        }

        nbCases++;

    }
}

void distributionEau(Case** matriceCases,Global global) {
    int caseX1=0;
    int caseY1=0;
    int caseX2=0;
    int caseY2=0;

    int numHabitation =0; // habitation que l'on est en train de parcourir
    int comparateur=50000;

    int nbHabitation = global.nbHabitation; //nombre d'habitation total
    Habitation* habEau[nbHabitation];
    Habitation* habEauOrdre[nbHabitation];

    //récupération de la coordoonée X et Y du chateau
    for (int i = 0; i < NB_LIGNES; i++) {
        for (int j = 0; j < NB_COLONNES; j++) {
            if (matriceCases[i][j].pChateau != NULL && matriceCases[i][j].type == 7
                && matriceCases[i][j].pChateau->distribution == 0) {

                caseX1 = j;
                caseY1 = i;
                caseX2 = caseX1 + 3;
                caseY2 = caseX1 + 5;
                matriceCases[i][j].pChateau->distribution = 1;



                //vérification des routes autour pour début BFS
                for (int a = caseX1 - 1; a < caseX2 + 2; a += TAILLE_X_CHATEAU + 1) {
                    for (int b = caseY1; b < caseY2 + 1; b++) {
                        if (matriceCases[a][b].type == 0) {
                            bfsEau(matriceCases, habEau, b, a);
                        }
                    }
                }
                for (int b = caseY1 - 1; b < caseY2 + 2; b += TAILLE_Y_CHATEAU + 1) {
                    for (int a = caseX1; a < caseX2 + 1; a++) {
                        if (matriceCases[b][a].type == 0) {
                            bfsEau(matriceCases, habEau, b, a);
                        }
                    }
                }

                // mettre dans l'ordre les habitations par rapport  au nb de cases
                while (numHabitation != nbHabitation - 1) {
                    comparateur = 5000;
                    for (int a = 0; a < nbHabitation; a++) {
                        if (habEau[a]->nbCaseEau < comparateur && habEau[a]->marquage != 1) {
                            habEauOrdre[numHabitation] = habEau[a];
                            comparateur = habEau[a]->nbCaseEau;
                        }
                    }
                    habEauOrdre[numHabitation]->marquage = 1;
                    numHabitation++;
                }

                numHabitation = 0;

                // parcours du tableau et mise à jour de l'alimEauOuiNon

                while (matriceCases[caseY1][caseX1].pChateau->quantiteDistribuee <
                       matriceCases[caseY1][caseX1].pChateau->capacite
                       || numHabitation != nbHabitation) {

                    if (habEauOrdre[numHabitation]->nbHabitants <
                        matriceCases[caseY1][caseX1].pChateau->capacite -
                        matriceCases[caseY1][caseX1].pChateau->quantiteDistribuee &&
                        habEauOrdre[numHabitation]->alimEauOuiNon == 0) { // habitation pas alimentée et quantité d'eau dispo

                        habEauOrdre[numHabitation]->alimEau = habEauOrdre[numHabitation]->nbHabitants;
                        habEauOrdre[numHabitation]->alimEauOuiNon = 2;
                        matriceCases[caseY1][caseX1].pChateau->quantiteDistribuee += habEauOrdre[numHabitation]->alimEau;

                    }
                    else if (matriceCases[caseY1][caseX1].pChateau->quantiteDistribuee !=
                               matriceCases[caseY1][caseX1].pChateau->capacite &&
                               habEauOrdre[numHabitation]->alimEauOuiNon == 0) { //habitation pas alimentée et quantité d'eau partielement dispo

                        habEauOrdre[numHabitation]->alimEau =
                                matriceCases[caseY1][caseX1].pChateau->capacite -
                                matriceCases[caseY1][caseX1].pChateau->quantiteDistribuee;
                        habEauOrdre[numHabitation]->alimEauOuiNon = 1;
                        matriceCases[caseY1][caseX1].pChateau->quantiteDistribuee += habEauOrdre[numHabitation]->alimEau;

                    }
                    else if( habEauOrdre[numHabitation]->alimEau <
                             matriceCases[caseY1][caseX1].pChateau->capacite -
                             matriceCases[caseY1][caseX1].pChateau->quantiteDistribuee &&
                             habEauOrdre[numHabitation]->alimEauOuiNon == 1){ //habitation partielement alimentée et quantité d'eau dispo

                        matriceCases[caseY1][caseX1].pChateau->quantiteDistribuee +=
                                habEauOrdre[numHabitation]->nbHabitants-habEauOrdre[numHabitation]->alimEau;

                        habEauOrdre[numHabitation]->alimEau = habEauOrdre[numHabitation]->nbHabitants;
                        habEauOrdre[numHabitation]->alimEauOuiNon = 2;

                    }
                    else if (matriceCases[caseY1][caseX1].pChateau->quantiteDistribuee !=
                             matriceCases[caseY1][caseX1].pChateau->capacite &&
                             habEauOrdre[numHabitation]->alimEauOuiNon == 1){ // habitation partielement alimentée et quantité d'eau partielement dispo

                        matriceCases[caseY1][caseX1].pChateau->quantiteDistribuee +=
                                habEauOrdre[numHabitation]->nbHabitants-habEauOrdre[numHabitation]->alimEau;

                        habEauOrdre[numHabitation]->alimEau +=
                                matriceCases[caseY1][caseX1].pChateau->capacite -
                                matriceCases[caseY1][caseX1].pChateau->quantiteDistribuee;
                        habEauOrdre[numHabitation]->alimEauOuiNon = 1;

                    }

                    numHabitation++;
                }

            }
        }
    }
    // à la fin mettre distribution à 0 pour tous
    for (int i = 0; i < NB_LIGNES; i++) {
        for (int j = 0; j < NB_COLONNES; j++) {
            if (matriceCases[i][j].pChateau != NULL && matriceCases[i][j].type == 7
                && matriceCases[i][j].pChateau->distribution == 1) {
                  matriceCases[i][j].pChateau->distribution = 0;
            }
        }


    }
}



void distributionElec(Case** matriceCases,Global global){
    int caseX1=0;
    int caseY1=0;
    int caseX2=0;
    int caseY2=0;

    int numHabitation =0; // habitation que l'on est en train de parcourir

    int nbHabitation = global.nbHabitation; //nombre d'habitation total
    Habitation* habElec[nbHabitation];


    //récupération de la coordoonée X et Y du chateau
    for (int i = 0; i < NB_LIGNES; i++) {
        for (int j = 0; j < NB_COLONNES; j++) {
            if (matriceCases[i][j].pCentrale != NULL && matriceCases[i][j].type == 8
                && matriceCases[i][j].pCentrale->distribution == 0) {

                caseX1 = j;
                caseY1 = i;
                caseX2 = caseX1 + 3;
                caseY2 = caseX1 + 5;
                matriceCases[i][j].pCentrale->distribution = 1;



                //vérification des routes autour pour début BFS
                for (int a = caseX1 - 1; a < caseX2 + 2; a += TAILLE_X_CHATEAU + 1) {
                    for (int b = caseY1; b < caseY2 + 1; b++) {
                        if (matriceCases[a][b].type == 0) {
                            bfsEau(matriceCases, habElec, b, a);
                        }
                    }
                }
                for (int b = caseY1 - 1; b < caseY2 + 2; b += TAILLE_Y_CHATEAU + 1) {
                    for (int a = caseX1; a < caseX2 + 1; a++) {
                        if (matriceCases[b][a].type == 0) {
                            bfsEau(matriceCases, habElec, b, a);
                        }
                    }
                }

                numHabitation = 0;

                // parcours du tableau et mise à jour de l'alimElecOuiNon

                while (matriceCases[caseY1][caseX1].pCentrale->quantiteDistribuee <
                       matriceCases[caseY1][caseX1].pCentrale->capacite
                       || numHabitation != nbHabitation) {

                    if (habElec[numHabitation]->nbHabitants <
                        matriceCases[caseY1][caseX1].pCentrale->capacite -
                        matriceCases[caseY1][caseX1].pCentrale->quantiteDistribuee &&
                        habElec[numHabitation]->alimElecOuiNon == 0) { // habitation pas alimentée et quantité d'eau dispo

                        habElec[numHabitation]->alimElec = habElec[numHabitation]->nbHabitants;
                        habElec[numHabitation]->alimElecOuiNon = 1;
                        matriceCases[caseY1][caseX1].pCentrale->quantiteDistribuee += habElec[numHabitation]->alimElec;

                    }
                    numHabitation++;
                }
            }
        }
    }
    // à la fin mettre distribution à 0 pour tous
    for (int i = 0; i < NB_LIGNES; i++) {
        for (int j = 0; j < NB_COLONNES; j++) {
            if (matriceCases[i][j].pCentrale != NULL && matriceCases[i][j].type == 8
                && matriceCases[i][j].pCentrale->distribution == 1) {

                matriceCases[i][j].pCentrale->distribution = 0;
            }
        }
    }
}












int convertirEnCase(int x, int y,  int* ligne, int* colonne) {

    int colonneTemporaire = (int)((x-DECALAGE_GRILLE_X)/TAILLE_CASE);
    int ligneTemporaire = (int)((y-DECALAGE_GRILLE_Y)/TAILLE_CASE);

    if(ligneTemporaire >= NB_LIGNES || colonneTemporaire >= NB_COLONNES || colonneTemporaire < 0 || ligneTemporaire < 0) {//souris en dehors la zone de jeu
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

int afficherPlacerUneRoute(Case** matriceCase, Case caseAConstruire, int* constructionPossible){ // afficherPlacerUneRoute (matriceCase[ligneAConstruire][colonneAConstruire], &constructionPossible);

    if (caseAConstruire.type != 0){
        *constructionPossible = 0;
        return 1;
    }else{ //On affiche le surlignage en vert

        ALLEGRO_COLOR vert;
        vert = al_map_rgb(57, 255, 20);

        dessinerCarte(matriceCase);
        al_draw_filled_rectangle((float)caseAConstruire.x, (float)caseAConstruire.y, (float)caseAConstruire.x + TAILLE_CASE, (float)caseAConstruire.y + TAILLE_CASE, vert);
        al_flip_display();
        *constructionPossible = 1;
        return 0;
    }
}

int placerUneRoute(Case** matriceCase, Case caseAConstruire, int constructionPossible){ // placerUneRoute (matriceCase, matriceCase[ligneAConstruire][colonneAConstruire], constructionPossible);

    if (constructionPossible == 1){

        matriceCase[caseAConstruire.ligne][caseAConstruire.colonne].type = 1;

        dessinerCarte(matriceCase);
        al_flip_display();

        return 0;
    }else{
        return 1;
    }
}

int afficherPlacerUneConstruction(Case** matriceCase, Case caseAConstruire, int* constructionPossible, int typeDeContruction){ // afficherPlacerUneConstruction (matriceCase, matriceCase[ligneAConstruire][colonneAConstruire], &constructionPossible, typeDeConstruction);

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

        if(caseAConstruire.ligne < NB_LIGNES-2 && caseAConstruire.colonne < NB_COLONNES-2){
            dessinerCarte(matriceCase);
            al_draw_filled_rectangle((float)caseAConstruire.x, (float)caseAConstruire.y, (float)caseAConstruire.x + TAILLE_CASE*3, (float)caseAConstruire.y + TAILLE_CASE*3, vert);
            al_flip_display();
        }

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

        if(caseAConstruire.ligne < NB_LIGNES-5 && caseAConstruire.colonne < NB_COLONNES-3){
            dessinerCarte(matriceCase);
            al_draw_filled_rectangle((float)caseAConstruire.x, (float)caseAConstruire.y, (float)caseAConstruire.x + TAILLE_CASE*4, (float)caseAConstruire.y + TAILLE_CASE*6, vert);
            al_flip_display();
        }

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
        if(caseAConstruire.ligne < NB_LIGNES-2 && caseAConstruire.colonne < NB_COLONNES-2) {
            if (typeDeConstruction == 2) {

                //On met un terrain vague
                matriceCase[caseAConstruire.ligne][caseAConstruire.colonne].pHabitation = calloc(1, sizeof(Habitation));
                matriceCase[caseAConstruire.ligne][caseAConstruire.colonne].pHabitation->coordXHG = caseAConstruire.x;
                matriceCase[caseAConstruire.ligne][caseAConstruire.colonne].pHabitation->coordYHG = caseAConstruire.y;

                for (int i = caseAConstruire.ligne; i < caseAConstruire.ligne + 3; i++) {
                    for (int j = caseAConstruire.colonne; j < caseAConstruire.colonne + 3; j++) {

                        matriceCase[i][j].type = 2;
                        matriceCase[i][j].pHabitation = matriceCase[caseAConstruire.ligne][caseAConstruire.colonne].pHabitation;
                    }
                }

                dessinerCarte(matriceCase);
                al_flip_display();
                return 0;
            }
        }

        //On place un chateau
        if(caseAConstruire.ligne < NB_LIGNES-5 && caseAConstruire.colonne < NB_COLONNES-3) {
            if (typeDeConstruction == 7) {

                //On met un chateau
                matriceCase[caseAConstruire.ligne][caseAConstruire.colonne].pChateau = calloc(1, sizeof(Chateau));
                matriceCase[caseAConstruire.ligne][caseAConstruire.colonne].pChateau->coordXHG = caseAConstruire.x;
                matriceCase[caseAConstruire.ligne][caseAConstruire.colonne].pChateau->coordYHG = caseAConstruire.y;

                for (int i = caseAConstruire.ligne; i < caseAConstruire.ligne + 6; i++) {
                    for (int j = caseAConstruire.colonne; j < caseAConstruire.colonne + 4; j++) {

                        matriceCase[i][j].type = 7;
                        matriceCase[i][j].pChateau = matriceCase[caseAConstruire.ligne][caseAConstruire.colonne].pChateau;
                    }
                }
                dessinerCarte(matriceCase);
                al_flip_display();
                return 0;
            }

                //On place une centrale
            else if (typeDeConstruction == 8) {

                //On met une centrale
                matriceCase[caseAConstruire.ligne][caseAConstruire.colonne].pCentrale = calloc(1, sizeof(Centrale));
                matriceCase[caseAConstruire.ligne][caseAConstruire.colonne].pCentrale->coordXHG = caseAConstruire.x;
                matriceCase[caseAConstruire.ligne][caseAConstruire.colonne].pCentrale->coordYHG = caseAConstruire.y;

                for (int i = caseAConstruire.ligne; i < caseAConstruire.ligne + 6; i++) {
                    for (int j = caseAConstruire.colonne; j < caseAConstruire.colonne + 4; j++) {

                        matriceCase[i][j].type = 8;
                        matriceCase[i][j].pCentrale = matriceCase[caseAConstruire.ligne][caseAConstruire.colonne].pCentrale;
                    }
                }
                dessinerCarte(matriceCase);
                al_flip_display();
                return 0;
            } else {
                printf("Erreur placerUneConstruction : type inconnu");
                return -1;
            }
        }
    }else{
        return 1;
    }
}


int payer(Global* structureglobale, int cout){

    int argentTemporaire = structureglobale->argentBanque - cout;
    if (argentTemporaire < 0){
        return 1;

    }else{
        structureglobale->argentBanque = argentTemporaire;
        return 0;
    }
}


/*
 *
 *
 *                                    EVOLUTION
 *
 *
 */


void evolutionHabitation(Case** matriceCases,Global* global) {

    for (int i = 0; i < NB_LIGNES; i++) {
        for (int j = 0; j < NB_COLONNES; j++) {
            if (matriceCases[i][j].pHabitation != NULL && matriceCases[i][j].pCentrale->distribution == 0) {


            }
        }
    }
}

