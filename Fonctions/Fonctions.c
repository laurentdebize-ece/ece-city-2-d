#include "Fonctions.h"
#include "../Carte/Carte.h"



#define TAILLE_X_CHATEAU 4
#define TAILLE_Y_CHATEAU 6
#define TAILLE_X_HABITATION 3
#define TAILLE_Y_HABITATION 3


//boucle for nbchateau faire distribution

/************************************** DISTRIBUTION DE L'EAU *************************************************/

void enfiler(t_file *f,int x,int y,int numeroRouteEnCours){
    t_maillon* tmp= malloc(sizeof(t_maillon));
    tmp->x=x;
    tmp->y=y;
    tmp->numRoute=numeroRouteEnCours;
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

int defiler(t_file *f,int tab[2]){
    int numeroRoute=0;
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
    numeroRoute=tmp->numRoute;

    free(tmp);
    return numeroRoute;
}

int bfsEau(Case** matriceCases,Habitation* habEau[],int x,int y,int numHabitation,int nbHabitation,int numeroChateau){
    t_file f;
    f.tete = f.fin = NULL;
    int XY[2];
    int nbCases[40]={0};
    int numeroRouteEnCours=0;
    int totalRoute=0;
    int nbRouteAutour=0;


    enfiler(&f,x,y,numeroRouteEnCours);
    matriceCases[y][x].distribEau=1;
    nbCases[numeroRouteEnCours]++;

    int dejaDansTab=0;

    while (f.tete != NULL) {
        numeroRouteEnCours = defiler(&f,XY);
        dejaDansTab = 0;
        //vérifiaction des habitations autour

        //Case dessus
        if(matriceCases[ XY[1]-1 ][ XY[0] ].type==2 ||
            matriceCases[ XY[1]-1 ][ XY[0] ].type==3 ||
            matriceCases[ XY[1]-1 ][ XY[0] ].type==4 ||
            matriceCases[ XY[1]-1 ][ XY[0] ].type==5 ||
            matriceCases[ XY[1]-1 ][ XY[0] ].type==6){
                // checker si l'habitation est deja dans le tableau et si'l existe un chemin plus court
            if(numHabitation !=0) {
                for (int i = 0; i < numHabitation; i++) {
                    if (habEau[i]->numero == matriceCases[XY[1] - 1][XY[0]].pHabitation->numero) {
                        habEau[i]->nbCasesParChateau[numeroChateau].nbCases=nbCases[numeroRouteEnCours];
                        habEau[i]->nbCasesParChateau[numeroChateau].numChateau=numeroChateau;
                        dejaDansTab = 1;
                    }
                }

                if (dejaDansTab != 1) {
                    habEau[numHabitation] = matriceCases[XY[1] - 1][XY[0]].pHabitation;
                    habEau[numHabitation]->nbCasesParChateau[numeroChateau].nbCases = nbCases[numeroRouteEnCours];
                    habEau[numHabitation]->nbCasesParChateau[numeroChateau].numChateau = numeroChateau;
                    numHabitation++;
                }

                dejaDansTab = 0;
            }
            else{
                habEau[numHabitation] = matriceCases[XY[1] - 1][XY[0]].pHabitation;
                habEau[numHabitation]->nbCasesParChateau[numeroChateau].nbCases = nbCases[numeroRouteEnCours];
                habEau[numHabitation]->nbCasesParChateau[numeroChateau].numChateau = numeroChateau;
                numHabitation++;
            }
        }
        //Case dessous
        if(matriceCases[ XY[1]+1 ][ XY[0] ].type==2 ||
        matriceCases[ XY[1]+1 ][ XY[0] ].type ==3 ||
        matriceCases[ XY[1]+1 ][ XY[0] ].type ==4 ||
        matriceCases[ XY[1]+1 ][ XY[0] ].type ==5||
        matriceCases[ XY[1]+1 ][ XY[0] ].type ==6){

            if(numHabitation !=0) {
                for (int i = 0; i < numHabitation; i++) {
                    if (habEau[i]->numero == matriceCases[XY[1] + 1][ XY[0] ].pHabitation->numero) {
                        habEau[i]->nbCasesParChateau[numeroChateau].nbCases=nbCases[numeroRouteEnCours];
                        habEau[i]->nbCasesParChateau[numeroChateau].numChateau=numeroChateau;
                        dejaDansTab = 1;
                    }
                }

                if (dejaDansTab != 1) {
                    habEau[numHabitation] = matriceCases[XY[1] + 1][XY[0]].pHabitation;
                    habEau[numHabitation]->nbCasesParChateau[numeroChateau].nbCases = nbCases[numeroRouteEnCours];
                    habEau[numHabitation]->nbCasesParChateau[numeroChateau].numChateau = numeroChateau;
                    numHabitation++;
                }

                dejaDansTab = 0;
            }
            else{
                habEau[numHabitation] = matriceCases[XY[1] + 1][XY[0]].pHabitation;
                habEau[numHabitation]->nbCasesParChateau[numeroChateau].nbCases = nbCases[numeroRouteEnCours];
                habEau[numHabitation]->nbCasesParChateau[numeroChateau].numChateau = numeroChateau;
                numHabitation++;
            }
        }
        //Case gauche
        if(matriceCases[ XY[1] ][ XY[0]-1 ].type==2
        || matriceCases[ XY[1] ][ XY[0]-1 ].type ==3
        || matriceCases[ XY[1] ][ XY[0]-1 ].type ==4
        || matriceCases[ XY[1] ][ XY[0]-1 ].type ==5
        || matriceCases[ XY[1] ][ XY[0]-1 ].type ==6){

            if(numHabitation !=0) {
                for (int i = 0; i < numHabitation; i++) {
                    if (habEau[i]->numero == matriceCases[XY[1]][XY[0] - 1].pHabitation->numero) {
                        habEau[i]->nbCasesParChateau[numeroChateau].nbCases=nbCases[numeroRouteEnCours];
                        habEau[i]->nbCasesParChateau[numeroChateau].numChateau=numeroChateau;
                        dejaDansTab = 1;
                    }
                }

                if (dejaDansTab != 1) {
                    habEau[numHabitation] = matriceCases[XY[1]][XY[0] - 1].pHabitation;
                    habEau[numHabitation]->nbCasesParChateau[numeroChateau].nbCases = nbCases[numeroRouteEnCours];
                    habEau[numHabitation]->nbCasesParChateau[numeroChateau].numChateau = numeroChateau;
                    numHabitation++;
                }

                dejaDansTab = 0;
            }
            else{
                habEau[numHabitation] = matriceCases[XY[1]][XY[0] - 1].pHabitation;
                habEau[numHabitation]->nbCasesParChateau[numeroChateau].nbCases = nbCases[numeroRouteEnCours];
                habEau[numHabitation]->nbCasesParChateau[numeroChateau].numChateau = numeroChateau;
                numHabitation++;
            }
        }
        //Case droite
        if(matriceCases[ XY[1] ][ XY[0]+1 ].type==2
        || matriceCases[ XY[1] ][ XY[0]+1 ].type==3
        || matriceCases[ XY[1] ][ XY[0]+1 ].type==4
        || matriceCases[ XY[1] ][ XY[0]+1 ].type==5
        || matriceCases[ XY[1] ][ XY[0]+1 ].type==6){

            if(numHabitation !=0) {
                for (int i = 0; i < numHabitation; i++) {
                    if (habEau[i]->numero == matriceCases[XY[1]][XY[0] + 1].pHabitation->numero) {
                        habEau[i]->nbCasesParChateau[numeroChateau].nbCases=nbCases[numeroRouteEnCours];
                        habEau[i]->nbCasesParChateau[numeroChateau].numChateau=numeroChateau;
                        dejaDansTab = 1;
                    }
                }

                if (dejaDansTab != 1) {
                    habEau[numHabitation] = matriceCases[XY[1]][XY[0] + 1].pHabitation;
                    habEau[numHabitation]->nbCasesParChateau[numeroChateau].nbCases = nbCases[numeroRouteEnCours];
                    habEau[numHabitation]->nbCasesParChateau[numeroChateau].numChateau = numeroChateau;
                    numHabitation++;
                }

                dejaDansTab = 0;
            }
            else{
                habEau[numHabitation] = matriceCases[XY[1]][XY[0] + 1].pHabitation;
                habEau[numHabitation]->nbCasesParChateau[numeroChateau].nbCases = nbCases[numeroRouteEnCours];
                habEau[numHabitation]->nbCasesParChateau[numeroChateau].numChateau = numeroChateau;
                numHabitation++;
            }
        }

        //vérification des routes autour pour la file
        nbRouteAutour=0;

        //Case gauche
        if(matriceCases[ XY[1] ][ XY[0]-1 ].type==1 && matriceCases[ XY[1] ][ XY[0]-1 ].distribEau==0){

            if(nbRouteAutour>0){
                totalRoute++;
                nbCases[totalRoute]=nbCases[numeroRouteEnCours];
                numeroRouteEnCours=totalRoute;
            }

            nbCases[numeroRouteEnCours]++;

            enfiler(&f,XY[0]-1,XY[1],numeroRouteEnCours);
            matriceCases[ XY[1] ][ XY[0]-1 ].distribEau=1;

            nbRouteAutour++;
        }
        //Case droite
        if(matriceCases[ XY[1] ][ XY[0]+1 ].type==1 && matriceCases[ XY[1] ][ XY[0]+1 ].distribEau==0){

            if(nbRouteAutour>0){
                totalRoute++;
                nbCases[totalRoute]=nbCases[numeroRouteEnCours];
                numeroRouteEnCours=totalRoute;

            }
            nbCases[numeroRouteEnCours]++;

            enfiler(&f,XY[0]+1,XY[1],numeroRouteEnCours);
            matriceCases[ XY[1] ][ XY[0]+1 ].distribEau=1;

            nbRouteAutour++;
        }
        //Case dessus
        if(matriceCases[ XY[1]-1 ][ XY[0] ].type==1 && matriceCases[ XY[1]-1 ][ XY[0] ].distribEau==0){

            if(nbRouteAutour>0){
                totalRoute++;
                nbCases[totalRoute]=nbCases[numeroRouteEnCours];
                numeroRouteEnCours=totalRoute;
            }

            nbCases[numeroRouteEnCours]++;

            enfiler(&f,XY[0],XY[1]-1,numeroRouteEnCours);
            matriceCases[ XY[1]-1 ][ XY[0] ].distribEau=1;

            nbRouteAutour++;

        }
        //Case dessous
        if(matriceCases[ XY[1]+1 ][ XY[0] ].type==1 && matriceCases[ XY[1]+1 ][ XY[0] ].distribEau==0){

            if(nbRouteAutour>0){
                totalRoute++;
                nbCases[totalRoute]=nbCases[numeroRouteEnCours];
                numeroRouteEnCours=totalRoute;
            }
            nbCases[numeroRouteEnCours]++;

            enfiler(&f,XY[0],XY[1]+1,numeroRouteEnCours);
            matriceCases[ XY[1]+1 ][ XY[0]].distribEau=1;

            nbRouteAutour++;
        }

    }
    for (int i = 0; i < NB_LIGNES; i++) {
        for (int j = 0; j < NB_COLONNES; j++) {
            matriceCases[i][j].distribEau=0;
        }
    }
    return numHabitation;
}

Chateau* choixChateau(Case** matriceCases,Global* global,int numeroChateau){
    for (int i = 0; i < NB_LIGNES; i++) {
        for (int j = 0; j < NB_COLONNES; j++) {
            if (matriceCases[i][j].pChateau != NULL ) {
                if(matriceCases[i][j].pChateau->numero == numeroChateau){
                 return matriceCases[i][j].pChateau;
                }
            }
        }
    }
}

void enfilerHabitation(t_file *f,Habitation* hab){
    Habitation * tmp= malloc(sizeof(Habitation));
    tmp=hab;
    tmp->suiv=NULL;

    if(f->avant==NULL){
        f->avant=tmp;
        f->apres=tmp;
    }
    else{
        f->apres->suiv=tmp;
        f->apres=tmp;
    }
}

Habitation* defilerHabitation(t_file *f){
    Habitation * tmp=f->avant;
    if(f->avant == f->apres){
        f->apres=NULL;
        f->avant=NULL;
    }
    else {
        f->avant = f->avant->suiv;
    }

    return tmp;

}

void distributionEau(Case** matriceCases,Global* global){
    int caseX1 = 0;
    int caseY1 = 0;
    int caseX2 = 0;
    int caseY2 = 0;

    int numHabitation = 0;// habitation que l'on est en train de parcourir
    int comparateur = 50000;
    int numHabitationBFS = 0;
    int nbHabitation = 0;

    for (int i = 0; i < NB_LIGNES; i++) {
        for (int j = 0; j < NB_COLONNES; j++) {
            if (matriceCases[i][j].pHabitation != NULL &&
                matriceCases[i][j].pHabitation->parcoureMatriceHabitation == 0) {
                matriceCases[i][j].pHabitation->numero = nbHabitation;
                nbHabitation += 1;
                matriceCases[i][j].pHabitation->parcoureMatriceHabitation = 1;
            }
        }
    }
    for (int i = 0; i < NB_LIGNES; i++) {
        for (int j = 0; j < NB_COLONNES; j++) {
            if (matriceCases[i][j].pHabitation != NULL &&
                matriceCases[i][j].pHabitation->parcoureMatriceHabitation == 1) {
                matriceCases[i][j].pHabitation->parcoureMatriceHabitation = 0;
            }
        }
    }

    global->nbHabitation = nbHabitation;
    Habitation *habEau[nbHabitation];
    //Habitation *habEauOrdre[nbHabitation];

    //récupération de la coordoonée X et Y du chateau
    for (int i = 0; i < NB_LIGNES; i++) {
        for (int j = 0; j < NB_COLONNES; j++) {
            if (matriceCases[i][j].pChateau != NULL && matriceCases[i][j].type == 7
                && matriceCases[i][j].pChateau->distribution == 0) {

                caseX1 = j;
                caseY1 = i;
                caseX2 = caseX1 + 3;
                caseY2 = caseY1 + 5;
                matriceCases[i][j].pChateau->distribution = 1;
                int numeroChateau = matriceCases[i][j].pChateau->numero;

                //vérification des routes autour pour début BFS
                for (int a = caseX1 - 1; a < caseX2 + 2; a += TAILLE_X_CHATEAU + 1) {
                    for (int b = caseY1; b < caseY2 + 1; b++) {
                        if (a > 0 && b > 0) {
                            if (matriceCases[b][a].type == 1) {
                                numHabitationBFS = bfsEau(matriceCases, habEau, a, b, numHabitationBFS, nbHabitation,numeroChateau);
                            }
                        }
                    }
                }
                for (int b = caseY1 - 1; b < caseY2 + 2; b += TAILLE_Y_CHATEAU + 1) {
                    for (int a = caseX1; a < caseX2 + 1; a++) {
                        if (a > 0 && b > 0) {
                            if (matriceCases[b][a].type == 1) {
                                numHabitationBFS = bfsEau(matriceCases, habEau, a, b, numHabitationBFS, nbHabitation,numeroChateau);
                            }
                        }
                    }
                }

            }
        }
    }
    for (int i = 0; i < NB_LIGNES; i++) {
        for (int j = 0;j < NB_COLONNES; j++) {
            if (matriceCases[i][j].pChateau != NULL && matriceCases[i][j].type == 7
                && matriceCases[i][j].pChateau->distribution == 1) {

                matriceCases[i][j].pChateau->distribution = 0;
                matriceCases[i][j].pChateau->quantiteDistribuee = 0;
            }
            if (matriceCases[i][j].pHabitation != NULL
                && matriceCases[i][j].pHabitation->parcoureMatriceHabitation == 1) {

                matriceCases[i][j].pHabitation->parcoureMatriceHabitation = 0;
                matriceCases[i][j].pHabitation->alimEau=0;
            }
        }
    }
    int habitationProche = 0;
    for (int k = 0; k < NB_LIGNES; k++) {
        for (int l = 0; l < NB_COLONNES; l++) {
            if (matriceCases[k][l].pHabitation != NULL){
                matriceCases[k][l].pHabitation->parcoureMatriceHabitation = 0;
            }
        }
    }
    for (int k = 0; k < NB_LIGNES; k++) {
        for (int l = 0; l < NB_COLONNES; l++) {
            if(matriceCases[k][l].pHabitation != NULL ){
                matriceCases[k][l].pHabitation->alimEauOuiNon=0;
            }
        }
    }

    for (int i = 0; i < NB_LIGNES; i++) {
        for (int j = 0; j < NB_COLONNES; j++) {
            if (matriceCases[i][j].pChateau != NULL && matriceCases[i][j].type == 7
                && matriceCases[i][j].pChateau->distribution == 0) {
                caseX1 = j;
                caseY1 = i;
                caseX2 = caseX1 + 3;
                caseY2 = caseY1 + 5;
                matriceCases[i][j].pChateau->distribution = 1;
                int numeroChateau = matriceCases[i][j].pChateau->numero;
                numHabitation = 0;
                t_file f;
                f.avant = f.apres = NULL;

                while (numHabitation < numHabitationBFS) {
                    comparateur = 5000;

                    for (int a = 0; a < numHabitationBFS; a++) {
                        if (habEau[a]->nbCasesParChateau[numeroChateau].nbCases < comparateur &&
                            habEau[a]->parcoureMatriceHabitation != 1) {

                            comparateur = habEau[a]->nbCasesParChateau[numeroChateau].nbCases;
                            habitationProche = a;
                        }
                    }

                    enfilerHabitation(&f, habEau[habitationProche]);
                    habEau[habitationProche]->parcoureMatriceHabitation = 1;

                    numHabitation++;
                }
                numHabitation = 0;
                Habitation *habitationEnCours = NULL;
                while (matriceCases[caseY1][caseX1].pChateau->quantiteDistribuee <
                       matriceCases[caseY1][caseX1].pChateau->capacite
                       && numHabitation < numHabitationBFS) {

                    habitationEnCours = defilerHabitation(&f);
                    if (habitationEnCours != NULL) {
                        if (habitationEnCours->nbHabitants <=
                            matriceCases[caseY1][caseX1].pChateau->capacite -
                            matriceCases[caseY1][caseX1].pChateau->quantiteDistribuee &&
                            habitationEnCours->alimEauOuiNon == 0) { // habitation pas alimentée et quantité d'eau dispo

                            habitationEnCours->alimEau = habitationEnCours->nbHabitants;
                            habitationEnCours->alimEauOuiNon = 2;
                            matriceCases[caseY1][caseX1].pChateau->quantiteDistribuee += habitationEnCours->alimEau;

                        } else if (matriceCases[caseY1][caseX1].pChateau->quantiteDistribuee !=
                                   matriceCases[caseY1][caseX1].pChateau->capacite &&
                                   habitationEnCours->alimEauOuiNon ==
                                   0) { //habitation pas alimentée et quantité d'eau partielement dispo

                            habitationEnCours->alimEau =
                                    matriceCases[caseY1][caseX1].pChateau->capacite -
                                    matriceCases[caseY1][caseX1].pChateau->quantiteDistribuee;
                            habitationEnCours->alimEauOuiNon = 1;
                            matriceCases[caseY1][caseX1].pChateau->quantiteDistribuee += habitationEnCours->alimEau;

                        } else if (habitationEnCours->alimEau <
                                   matriceCases[caseY1][caseX1].pChateau->capacite -
                                   matriceCases[caseY1][caseX1].pChateau->quantiteDistribuee &&
                                   habitationEnCours->alimEauOuiNon ==
                                   1) { //habitation partielement alimentée et quantité d'eau dispo

                            matriceCases[caseY1][caseX1].pChateau->quantiteDistribuee +=
                                    habitationEnCours->nbHabitants - habitationEnCours->alimEau;
                            habitationEnCours->alimEau = habitationEnCours->nbHabitants;
                            habitationEnCours->alimEauOuiNon = 2;

                        } else if (matriceCases[caseY1][caseX1].pChateau->quantiteDistribuee !=
                                   matriceCases[caseY1][caseX1].pChateau->capacite &&
                                   habitationEnCours->alimEauOuiNon ==
                                   1) { // habitation partielement alimentée et quantité d'eau partielement dispo

                            matriceCases[caseY1][caseX1].pChateau->quantiteDistribuee +=
                                    habitationEnCours->nbHabitants - habitationEnCours->alimEau;

                            habitationEnCours->alimEau +=
                                    matriceCases[caseY1][caseX1].pChateau->capacite -
                                    matriceCases[caseY1][caseX1].pChateau->quantiteDistribuee;
                            habitationEnCours->alimEauOuiNon = 1;

                        }
                    }
                    numHabitation++;
                }
            }
        }
    }
    for (int i = 0; i < NB_LIGNES; i++) {
        for (
                int j = 0;
                j < NB_COLONNES; j++) {
            if (matriceCases[i][j].pChateau != NULL && matriceCases[i][j].type == 7
                && matriceCases[i][j].pChateau->distribution == 1) {

                matriceCases[i][j].pChateau->
                        distribution = 0;
            }
            if (matriceCases[i][j].pHabitation != NULL
                && matriceCases[i][j].pHabitation->parcoureMatriceHabitation == 1) {

                matriceCases[i][j].pHabitation->
                        parcoureMatriceHabitation = 0;
            }
        }
    }
}

/************************************** DISTRIBUTION DE L'ELEC *************************************************/

int bfsElec(Case** matriceCases,Habitation* habElec[],int x,int y,int numHabitation,int nbHabitation,int numeroCentrale,int xRoute, int yRoute){
    t_file f;
    f.tete = f.fin = NULL;
    int XY[2];
    int nbCases[40]={0};
    int numeroRouteEnCours=0;
    int totalRoute=0;
    int nbRouteAutour=0;


    enfiler(&f,xRoute,yRoute,numeroRouteEnCours);
    matriceCases[yRoute][xRoute].distribEau=1;
    nbCases[numeroRouteEnCours]++;

    int dejaDansTab=0;

    while (f.tete != NULL) {
        numeroRouteEnCours = defiler(&f,XY);
        dejaDansTab = 0;

        //vérifiaction des habitations autour

        //Case dessus
        if( XY[1]-1>0 && XY[0]>0 && XY[1]-1<35 &&  XY[0]<45) {
            if (matriceCases[XY[1] - 1][XY[0]].type == 2 ||
                matriceCases[XY[1] - 1][XY[0]].type == 3 ||
                matriceCases[XY[1] - 1][XY[0]].type == 4 ||
                matriceCases[XY[1] - 1][XY[0]].type == 5 ||
                matriceCases[XY[1] - 1][XY[0]].type == 6) {
                // checker si l'habitation est deja dans le tableau
                if (numHabitation != 0) {
                    for (int i = 0; i < numHabitation; i++) {
                        if (matriceCases[y][x].pCentrale->tab[i] == matriceCases[XY[1] - 1][XY[0]].pHabitation) {
                            dejaDansTab = 1;
                        }
                    }
                    if (dejaDansTab != 1) {
                        matriceCases[y][x].pCentrale->tab[numHabitation] = matriceCases[XY[1] - 1][XY[0]].pHabitation;
                        numHabitation++;
                    }
                    dejaDansTab = 0;
                } else {
                    matriceCases[y][x].pCentrale->tab[numHabitation] = matriceCases[XY[1] - 1][XY[0]].pHabitation;
                    numHabitation++;
                }

            }
        }
        //Case dessous
        if( XY[1]+1>0 && XY[0]>0 && XY[1]+1<35 &&  XY[0]<45) {
            if (matriceCases[XY[1] + 1][XY[0]].type == 2 ||
                matriceCases[XY[1] + 1][XY[0]].type == 3 ||
                matriceCases[XY[1] + 1][XY[0]].type == 4 ||
                matriceCases[XY[1] + 1][XY[0]].type == 5 ||
                matriceCases[XY[1] + 1][XY[0]].type == 6) {

                if (numHabitation != 0) {
                    for (int i = 0; i < numHabitation; i++) {
                        if (matriceCases[y][x].pCentrale->tab[i] == matriceCases[XY[1] + 1][XY[0]].pHabitation) {
                            dejaDansTab = 1;
                        }
                    }
                    if (dejaDansTab != 1) {
                        matriceCases[y][x].pCentrale->tab[numHabitation] = matriceCases[XY[1] + 1][XY[0]].pHabitation;
                        numHabitation++;
                    }
                    dejaDansTab = 0;
                } else {
                    matriceCases[y][x].pCentrale->tab[numHabitation] = matriceCases[XY[1] + 1][XY[0]].pHabitation;
                    numHabitation++;
                }
            }
        }
        //Case gauche
        if( XY[1]>0 && XY[0]-1>0 && XY[1]<35 &&  XY[0]-1<45) {
            if (matriceCases[XY[1]][XY[0] - 1].type == 2
                || matriceCases[XY[1]][XY[0] - 1].type == 3
                || matriceCases[XY[1]][XY[0] - 1].type == 4
                || matriceCases[XY[1]][XY[0] - 1].type == 5
                || matriceCases[XY[1]][XY[0] - 1].type == 6) {

                if (numHabitation != 0) {
                    for (int i = 0; i < numHabitation; i++) {
                        if (matriceCases[y][x].pCentrale->tab[i] == matriceCases[XY[1]][XY[0] - 1].pHabitation) {
                            dejaDansTab = 1;
                        }
                    }
                    if (dejaDansTab != 1) {
                        matriceCases[y][x].pCentrale->tab[numHabitation] = matriceCases[XY[1]][XY[0] - 1].pHabitation;
                        numHabitation++;
                    }
                    dejaDansTab = 0;
                } else {
                    matriceCases[y][x].pCentrale->tab[numHabitation] = matriceCases[XY[1]][XY[0] - 1].pHabitation;
                    numHabitation++;
                }
            }
        }
        //Case droite
        if( XY[1]>0 && XY[0]+1>0 && XY[1]<35 &&  XY[0]+1<45) {
            if (matriceCases[XY[1]][XY[0] + 1].type == 2
                || matriceCases[XY[1]][XY[0] + 1].type == 3
                || matriceCases[XY[1]][XY[0] + 1].type == 4
                || matriceCases[XY[1]][XY[0] + 1].type == 5
                || matriceCases[XY[1]][XY[0] + 1].type == 6) {

                if (numHabitation != 0) {
                    for (int i = 0; i < numHabitation; i++) {
                        if (matriceCases[y][x].pCentrale->tab[i] == matriceCases[XY[1]][XY[0] + 1].pHabitation) {
                            dejaDansTab = 1;
                        }
                    }
                    if (dejaDansTab != 1) {
                        matriceCases[y][x].pCentrale->tab[numHabitation] = matriceCases[XY[1]][XY[0] + 1].pHabitation;
                        numHabitation++;
                    }
                    dejaDansTab = 0;
                } else {
                    matriceCases[y][x].pCentrale->tab[numHabitation] = matriceCases[XY[1]][XY[0] + 1].pHabitation;
                    numHabitation++;
                }
            }
        }

        //vérification des routes autour pour la file
        nbRouteAutour=0;

        //Case gauche
        if( XY[1]>0 && XY[0]-1>0 && XY[1]<35 &&  XY[0]-1<45) {
            if (matriceCases[XY[1]][XY[0] - 1].type == 1 && matriceCases[XY[1]][XY[0] - 1].distribEau == 0) {

                if (nbRouteAutour > 0) {
                    totalRoute++;
                    nbCases[totalRoute] = nbCases[numeroRouteEnCours];
                    numeroRouteEnCours = totalRoute;
                }

                nbCases[numeroRouteEnCours]++;

                enfiler(&f, XY[0] - 1, XY[1], numeroRouteEnCours);
                matriceCases[XY[1]][XY[0] - 1].distribEau = 1;

                nbRouteAutour++;
            }
        }
        //Case droite
        if( XY[1]>0 && XY[0]+1>0 && XY[1]<35 &&  XY[0]+1<45) {
            if (matriceCases[XY[1]][XY[0] + 1].type == 1 && matriceCases[XY[1]][XY[0] + 1].distribEau == 0) {

                if (nbRouteAutour > 0) {
                    totalRoute++;
                    nbCases[totalRoute] = nbCases[numeroRouteEnCours];
                    numeroRouteEnCours = totalRoute;

                }
                nbCases[numeroRouteEnCours]++;

                enfiler(&f, XY[0] + 1, XY[1], numeroRouteEnCours);
                matriceCases[XY[1]][XY[0] + 1].distribEau = 1;

                nbRouteAutour++;
            }
        }
        //Case dessus
        if( XY[1]-1>0 && XY[0]>0 && XY[1]-1<35 &&  XY[0]<45) {
            if (matriceCases[XY[1] - 1][XY[0]].type == 1 && matriceCases[XY[1] - 1][XY[0]].distribEau == 0) {

                if (nbRouteAutour > 0) {
                    totalRoute++;
                    nbCases[totalRoute] = nbCases[numeroRouteEnCours];
                    numeroRouteEnCours = totalRoute;
                }

                nbCases[numeroRouteEnCours]++;

                enfiler(&f, XY[0], XY[1] - 1, numeroRouteEnCours);
                matriceCases[XY[1] - 1][XY[0]].distribEau = 1;

                nbRouteAutour++;

            }
        }
        //Case dessous
        if( XY[1]+1>0 && XY[0]>0 && XY[1]+1<35 &&  XY[0]<45) {
            if (matriceCases[XY[1] + 1][XY[0]].type == 1 && matriceCases[XY[1] + 1][XY[0]].distribEau == 0) {

                if (nbRouteAutour > 0) {
                    totalRoute++;
                    nbCases[totalRoute] = nbCases[numeroRouteEnCours];
                    numeroRouteEnCours = totalRoute;
                }
                nbCases[numeroRouteEnCours]++;

                enfiler(&f, XY[0], XY[1] + 1, numeroRouteEnCours);
                matriceCases[XY[1] + 1][XY[0]].distribEau = 1;

                nbRouteAutour++;
            }
        }

    }
    for (int i = 0; i < NB_LIGNES; i++) {
        for (int j = 0; j < NB_COLONNES; j++) {
            matriceCases[i][j].distribEau=0;
        }
    }
    return numHabitation;
}

void distributionElec(Case** matriceCases,Global* global){
    int caseX1 = 0;
    int caseY1 = 0;
    int caseX2 = 0;
    int caseY2 = 0;

    int numHabitation = 0;// habitation que l'on est en train de parcourir
    int comparateur = 50000;
    int numHabitationBFS = 0;
    int nbHabitation = 0;

    for (int i = 0; i < NB_LIGNES; i++) {
        for (int j = 0; j < NB_COLONNES; j++) {
            if (matriceCases[i][j].pHabitation != NULL &&
                matriceCases[i][j].pHabitation->parcoureMatriceHabitation == 0) {
                matriceCases[i][j].pHabitation->numero = nbHabitation;
                nbHabitation += 1;
                matriceCases[i][j].pHabitation->parcoureMatriceHabitation = 1;
            }
        }
    }
    for (int i = 0; i < NB_LIGNES; i++) {
        for (int j = 0; j < NB_COLONNES; j++) {
            if (matriceCases[i][j].pHabitation != NULL &&
                matriceCases[i][j].pHabitation->parcoureMatriceHabitation == 1) {
                matriceCases[i][j].pHabitation->parcoureMatriceHabitation = 0;
            }
        }
    }

    global->nbHabitation = nbHabitation;
    Habitation *habElec[nbHabitation];
    //Habitation *habEauOrdre[nbHabitation];

    //récupération de la coordoonée X et Y du chateau
    for (int i = 0; i < NB_LIGNES; i++) {
        for (int j = 0; j < NB_COLONNES; j++) {
            if (matriceCases[i][j].pCentrale != NULL && matriceCases[i][j].type == 8
                && matriceCases[i][j].pCentrale ->distribution == 0) {

                caseX1 = j;
                caseY1 = i;
                caseX2 = caseX1 + 3;
                caseY2 = caseY1 + 5;
                matriceCases[i][j].pCentrale->distribution = 1;
                int numeroCentrale = matriceCases[i][j].pCentrale ->numero;

                //vérification des routes autour pour début BFS
                for (int a = caseX1 - 1; a < caseX2 + 2; a += TAILLE_X_CHATEAU + 1) {
                    for (int b = caseY1; b < caseY2 + 1; b++) {
                        if (a > 0 && b > 0) {
                            if (matriceCases[b][a].type == 1) {
                                numHabitationBFS = bfsElec(matriceCases, habElec, caseX1, caseY1, numHabitationBFS, nbHabitation, numeroCentrale,a,b);
                            }
                        }
                    }
                }
                for (int b = caseY1 - 1; b < caseY2 + 2; b += TAILLE_Y_CHATEAU + 1) {
                    for (int a = caseX1; a < caseX2 + 1; a++) {
                        if (a > 0 && b > 0) {
                            if (matriceCases[b][a].type == 1) {
                                numHabitationBFS = bfsElec(matriceCases, habElec, caseX1, caseY1, numHabitationBFS, nbHabitation, numeroCentrale,a,b);
                            }
                        }
                    }
                }
            }
        }
    }
    for (int i = 0; i < NB_LIGNES; i++) {
        for (int j = 0;j < NB_COLONNES; j++) {
            if (matriceCases[i][j].pCentrale!= NULL && matriceCases[i][j].type == 8
                && matriceCases[i][j].pCentrale->distribution == 1) {

                matriceCases[i][j].pCentrale->distribution = 0;
                matriceCases[i][j].pCentrale->quantiteDistribuee=0;
            }
            if (matriceCases[i][j].pHabitation != NULL
                && matriceCases[i][j].pHabitation->parcoureMatriceHabitation == 1) {

                matriceCases[i][j].pHabitation->parcoureMatriceHabitation = 0;
                matriceCases[i][j].pHabitation->alimElec=0;
            }
        }
    }
    int habitationProche = 0;
    for (int k = 0; k < NB_LIGNES; k++) {
        for (int l = 0; l < NB_COLONNES; l++) {
            if (matriceCases[k][l].pHabitation != NULL &&
                matriceCases[k][l].pHabitation->parcoureMatriceHabitation == 1) {
                matriceCases[k][l].pHabitation->parcoureMatriceHabitation = 0;
            }
        }
    }


    for (int i = 0; i < NB_LIGNES; i++) {
        for (int j = 0; j < NB_COLONNES; j++) {
            if (matriceCases[i][j].pCentrale != NULL && matriceCases[i][j].type == 8
                && matriceCases[i][j].pCentrale->distribution == 0) {

                matriceCases[i][j].pCentrale->distribution = 1;
                numHabitation=0;

                Centrale* centrale= matriceCases[i][j].pCentrale;

                for(int k=0;k<numHabitationBFS;k++){
                    if (centrale->tab[k] !=NULL ){
                        if(centrale->tab[k]->nbHabitants <= (centrale->capacite - centrale->quantiteDistribuee)){
                            centrale->tab[k]->alimElec=centrale->tab[k]->nbHabitants;
                            centrale->quantiteDistribuee+=centrale->tab[k]->nbHabitants;
                        }
                    }
                }

            }
        }
    }

    for (int i = 0; i < NB_LIGNES; i++) {
        for (int j = 0;j < NB_COLONNES; j++) {
            if (matriceCases[i][j].pCentrale != NULL && matriceCases[i][j].type == 8
                && matriceCases[i][j].pCentrale->distribution == 1) {

                matriceCases[i][j].pCentrale->distribution = 0;
            }
            if (matriceCases[i][j].pHabitation != NULL
                && matriceCases[i][j].pHabitation->parcoureMatriceHabitation == 1) {

                matriceCases[i][j].pHabitation->
                        parcoureMatriceHabitation = 0;
            }
        }
    }
}

/*********************************** VERIFICATION DE L'EAU POUR DISTRIBUTION ********************************/

int bfsEvolutionVerificationEAU(Case** matriceCases, int tabChateauRelie[10], int x, int y, int nbChateau){
    t_file f;
    f.tete = f.fin = NULL;
    int XY[2];
    int nbCases[40]={0};
    int numeroRouteEnCours=0;
    int totalRoute=0;
    int nbRouteAutour=0;



    enfiler(&f,x,y,numeroRouteEnCours);
    matriceCases[y][x].distribEau=1;
    nbCases[numeroRouteEnCours]++;

    int dejaDansTab=0;

    while (f.tete != NULL) {
        numeroRouteEnCours = defiler(&f,XY);

        //vérifiaction des habitations autour

        //Case dessus
        if( XY[1]-1>0 && XY[0]>0 && XY[1]-1<35 &&  XY[0]<45){
            if (matriceCases[XY[1] - 1][XY[0]].type == 7) {
                for (int i = 0; i < nbChateau; i++) {
                    if (matriceCases[XY[1] - 1][XY[0]].pChateau->numero == tabChateauRelie[i]) {
                        dejaDansTab = 1;
                    }
                }
                if (dejaDansTab != 1) {
                    tabChateauRelie[nbChateau] = matriceCases[XY[1] - 1][XY[0]].pChateau->numero;
                    nbChateau++;
                }

            }
        }
        //Case dessous
        if( XY[1]+1>0 && XY[0]>0 && XY[1]+1<35 &&  XY[0]<45 ) {
            if (matriceCases[XY[1] + 1][XY[0]].type == 7) {

                for (int i = 0; i < nbChateau; i++) {
                    if (matriceCases[XY[1] + 1][XY[0]].pChateau->numero == tabChateauRelie[i]) {
                        dejaDansTab = 1;
                    }
                }
                if (dejaDansTab != 1) {
                    tabChateauRelie[nbChateau] = matriceCases[XY[1] + 1][XY[0]].pChateau->numero;
                    nbChateau++;
                }
            }
        }
        //Case gauche
        if( XY[1]>0 && XY[0]-1>0 && XY[1]<35 &&  XY[0]-1<45) {
            if (matriceCases[XY[1]][XY[0] - 1].type == 7) {

                for (int i = 0; i < nbChateau; i++) {
                    if (matriceCases[XY[1]][XY[0] - 1].pChateau->numero == tabChateauRelie[i]) {
                        dejaDansTab = 1;
                    }
                }
                if (dejaDansTab != 1) {
                    tabChateauRelie[nbChateau] = matriceCases[XY[1]][XY[0] - 1].pChateau->numero;
                    nbChateau++;
                }

            }
        }
        //Case droite
        if( XY[1]>0 && XY[0]+1>0 && XY[1]<35 &&  XY[0]+1<45) {
            if (matriceCases[XY[1]][XY[0] + 1].type == 7) {

                for (int i = 0; i < nbChateau; i++) {
                    if (matriceCases[XY[1]][XY[0] + 1].pChateau->numero == tabChateauRelie[i]) {
                        dejaDansTab = 1;
                    }
                }
                if (dejaDansTab != 1) {
                    tabChateauRelie[nbChateau] = matriceCases[XY[1]][XY[0] + 1].pChateau->numero;
                    nbChateau++;
                }
            }
        }
        //vérification des routes autour pour la file

        //Case gauche
        if( XY[1]>0 && XY[0]-1>0 && XY[1]<35 &&  XY[0]-1<45) {
            if (matriceCases[XY[1]][XY[0] - 1].type == 1 && matriceCases[XY[1]][XY[0] - 1].distribEau == 0) {
                if (nbRouteAutour > 0) {
                    totalRoute++;
                    nbCases[totalRoute] = nbCases[numeroRouteEnCours];
                    numeroRouteEnCours = totalRoute;
                }
                nbRouteAutour++;
                enfiler(&f, XY[0] - 1, XY[1], numeroRouteEnCours);
                matriceCases[XY[1]][XY[0] - 1].distribEau = 1;

            }
        }
        //Case droite
        if( XY[1]>0 && XY[0]+1>0 && XY[1]<35 &&  XY[0]+1<45) {
            if (matriceCases[XY[1]][XY[0] + 1].type == 1 && matriceCases[XY[1]][XY[0] + 1].distribEau == 0) {
                if (nbRouteAutour > 0) {
                    totalRoute++;
                    nbCases[totalRoute] = nbCases[numeroRouteEnCours];
                    numeroRouteEnCours = totalRoute;
                }
                nbRouteAutour++;
                enfiler(&f, XY[0] + 1, XY[1], numeroRouteEnCours);
                matriceCases[XY[1]][XY[0] + 1].distribEau = 1;

            }
        }
        //Case dessus
        if( XY[1]-1>0 && XY[0]>0 && XY[1]-1<35 &&  XY[0]<45) {
            if (matriceCases[XY[1] - 1][XY[0]].type == 1 && matriceCases[XY[1] - 1][XY[0]].distribEau == 0) {
                if (nbRouteAutour > 0) {
                    totalRoute++;
                    nbCases[totalRoute] = nbCases[numeroRouteEnCours];
                    numeroRouteEnCours = totalRoute;
                }
                nbRouteAutour++;
                enfiler(&f, XY[0], XY[1] - 1, numeroRouteEnCours);
                matriceCases[XY[1] - 1][XY[0]].distribEau = 1;

            }
        }
        //Case dessous
        if( XY[1]+1>0 && XY[0]>0 && XY[1]+1<35 &&  XY[0]<45) {
            if (matriceCases[XY[1] + 1][XY[0]].type == 1 && matriceCases[XY[1] + 1][XY[0]].distribEau == 0) {
                if (nbRouteAutour > 0) {
                    totalRoute++;
                    nbCases[totalRoute] = nbCases[numeroRouteEnCours];
                    numeroRouteEnCours = totalRoute;
                }
                nbRouteAutour++;
                enfiler(&f, XY[0], XY[1] + 1, numeroRouteEnCours);
                matriceCases[XY[1] + 1][XY[0]].distribEau = 1;

            }
        }

    }
    for (int i = 0; i < NB_LIGNES; i++) {
        for (int j = 0; j < NB_COLONNES; j++) {
            matriceCases[i][j].distribEau=0;
        }
    }
    return nbChateau;
}

int distributionEvolutionEAU(Case** matriceCases,Global* global,Habitation* habitation) {
    int caseX1 = 0;
    int caseY1 = 0;
    int caseX2 = 0;
    int caseY2 = 0;
    int nbChateauRelie = 0;
    int tabChateauRelie[10] = {-1};
    for(int i=0;i<10;i++){
        tabChateauRelie[i]=-1;
    }
    int quantiteRestante = 0;
    for (int i = 0; i < NB_LIGNES; i++) {
        for (int j = 0; j < NB_COLONNES; j++) {
            if (matriceCases[i][j].pHabitation != NULL &&
                matriceCases[i][j].pHabitation->parcoureMatriceHabitation != 0) {
                matriceCases[i][j].pHabitation->parcoureMatriceHabitation = 0;
            }
        }
    }

    if (habitation->alimEau == habitation->nbHabitants) {
        for (int i = 0; i < NB_LIGNES; i++) {
            for (int j = 0; j < NB_COLONNES; j++) {
                if (matriceCases[i][j].pHabitation != NULL &&
                    matriceCases[i][j].pHabitation == habitation &&
                    matriceCases[i][j].pHabitation->parcoureMatriceHabitation == 0) {
                    caseX1 = j;
                    caseY1 = i;
                    caseX2 = caseX1 + 2;
                    caseY2 = caseY1 + 2;
                    matriceCases[i][j].pHabitation->parcoureMatriceHabitation = 1;
                }
            }
        }
        matriceCases[caseY1][caseX1].pHabitation->parcoureMatriceHabitation = 0;

        for (int a = caseX1 - 1; a < caseX2 + 2; a += TAILLE_X_HABITATION + 1) {
            for (int b = caseY1; b < caseY2 + 1; b++) {
                if (a > 0 && b > 0) {
                    if (matriceCases[b][a].type == 1) {
                        nbChateauRelie = bfsEvolutionVerificationEAU(matriceCases, tabChateauRelie, a, b,
                                                                     nbChateauRelie);
                    }
                }
            }
        }
        for (int b = caseY1 - 1; b < caseY2 + 2; b += TAILLE_Y_HABITATION + 1) {
            for (int a = caseX1; a < caseX2 + 1; a++) {
                if (a > 0 && b > 0) {
                    if (matriceCases[b][a].type == 1) {
                        nbChateauRelie = bfsEvolutionVerificationEAU(matriceCases, tabChateauRelie, a, b,
                                                                     nbChateauRelie);
                    }
                }
            }
        }
        for (int i = 0; i < NB_LIGNES; i++) {
            for (
                    int j = 0;
                    j < NB_COLONNES; j++) {
                if (matriceCases[i][j].pChateau != NULL && matriceCases[i][j].type == 7
                    && matriceCases[i][j].pChateau->distribution == 1) {

                    matriceCases[i][j].pChateau->
                            distribution = 0;
                }
                if (matriceCases[i][j].pHabitation != NULL
                    && matriceCases[i][j].pHabitation->parcoureMatriceHabitation == 1) {

                    matriceCases[i][j].pHabitation->
                            parcoureMatriceHabitation = 0;
                }
            }
        }
        int habitationProche = 0;
        for (int k = 0; k < NB_LIGNES; k++) {
            for (int l = 0; l < NB_COLONNES; l++) {
                if (matriceCases[k][l].pHabitation != NULL &&
                    matriceCases[k][l].pHabitation->parcoureMatriceHabitation == 1) {
                    matriceCases[k][l].pHabitation->parcoureMatriceHabitation = 0;
                }
            }
        }
        for (int i = 0; i < nbChateauRelie; i++) {
            for (int k = 0; k < NB_LIGNES; k++) {
                for (int l = 0; l < NB_COLONNES; l++) {
                    if (matriceCases[k][l].pChateau != NULL &&
                        matriceCases[k][l].pChateau->numero == tabChateauRelie[i] && matriceCases[k][l].pChateau->parcoursMatriceChateau ==0 ) {
                        matriceCases[k][l].pChateau->parcoursMatriceChateau =1;
                        quantiteRestante +=matriceCases[k][l].pChateau->capacite - matriceCases[k][l].pChateau->quantiteDistribuee;
                    }
                }
            }
        }

        for (int k = 0; k < NB_LIGNES; k++) {
            for (int l = 0; l < NB_COLONNES; l++) {
                if (matriceCases[k][l].pChateau != NULL &&
                    matriceCases[k][l].pChateau->parcoursMatriceChateau == 1) {
                    matriceCases[k][l].pChateau->parcoursMatriceChateau = 0;
                }
            }
        }
        int quantiteUtile = 0;
        int aEvoluer = habitation->niveau + 1;
        switch (aEvoluer) {

            case 1:
                quantiteUtile = CABANE;
                break;
            case 2:
                quantiteUtile = MAISON;
                break;
            case 3:
                quantiteUtile = IMMEUBLE;
                break;
            case 4:
                quantiteUtile = GRATTE_CIEL;
                break;
            default:

                break;
        }
        if (quantiteRestante >= quantiteUtile) {
            return 1;
        } else {
            return 0;
        }
    }
    else{
        return -1;
    }
}

int bfsEvolutionVerificationELEC(Case** matriceCases, int tabCentraleRelie[10], int x, int y, int nbCentrale){
    t_file f;
    f.tete = f.fin = NULL;
    int XY[2];
    int nbCases[40]={0};
    int numeroRouteEnCours=0;
    int totalRoute=0;
    int nbRouteAutour=0;



    enfiler(&f,x,y,numeroRouteEnCours);
    matriceCases[y][x].distribEau=1;
    nbCases[numeroRouteEnCours]++;

    int dejaDansTab=0;

    while (f.tete != NULL) {
        numeroRouteEnCours = defiler(&f,XY);

        //vérifiaction des habitations autour

        //Case dessus
        if( XY[1]-1>0 && XY[0]>0 && XY[1]-1<35 &&  XY[0]<45) {
            if (matriceCases[XY[1] - 1][XY[0]].type == 8) {
                for (int i = 0; i < nbCentrale; i++) {
                    if (matriceCases[XY[1] - 1][XY[0]].pCentrale->numero == tabCentraleRelie[i]) {
                        dejaDansTab = 1;
                    }
                }
                if (dejaDansTab != 1) {
                    tabCentraleRelie[nbCentrale] = matriceCases[XY[1] - 1][XY[0]].pCentrale->numero;
                    nbCentrale++;
                }

            }
        }
        //Case dessous
        if( XY[1]+1>0 && XY[0]>0 && XY[1]+1<35 &&  XY[0]<45) {
            if (matriceCases[XY[1] + 1][XY[0]].type == 8) {

                for (int i = 0; i < nbCentrale; i++) {
                    if (matriceCases[XY[1] + 1][XY[0]].pCentrale->numero == tabCentraleRelie[i]) {
                        dejaDansTab = 1;
                    }
                }
                if (dejaDansTab != 1) {
                    tabCentraleRelie[nbCentrale] = matriceCases[XY[1] + 1][XY[0]].pCentrale->numero;
                    nbCentrale++;
                }
            }
        }
        //Case gauche
        if( XY[1]>0 && XY[0]-1>0 && XY[1]<35 &&  XY[0]-1<45) {
            if (matriceCases[XY[1]][XY[0] - 1].type == 8) {

                for (int i = 0; i < nbCentrale; i++) {
                    if (matriceCases[XY[1]][XY[0] - 1].pCentrale->numero == tabCentraleRelie[i]) {
                        dejaDansTab = 1;
                    }
                }
                if (dejaDansTab != 1) {
                    tabCentraleRelie[nbCentrale] = matriceCases[XY[1]][XY[0] - 1].pCentrale->numero;
                    nbCentrale++;
                }

            }
        }
        //Case droite
        if( XY[1]>0 && XY[0]+1>0 && XY[1]<35 &&  XY[0]+1<45) {
            if (matriceCases[XY[1]][XY[0] + 1].type == 8) {

                for (int i = 0; i < nbCentrale; i++) {
                    if (matriceCases[XY[1]][XY[0] + 1].pCentrale->numero == tabCentraleRelie[i]) {
                        dejaDansTab = 1;
                    }
                }
                if (dejaDansTab != 1) {
                    tabCentraleRelie[nbCentrale] = matriceCases[XY[1]][XY[0] + 1].pCentrale->numero;
                    nbCentrale++;
                }
            }
        }

        //vérification des routes autour pour la file

        //Case gauche
        if( XY[1]>0 && XY[0]-1>0 && XY[1]<35 &&  XY[0]-1<45) {
            if (matriceCases[XY[1]][XY[0] - 1].type == 1 && matriceCases[XY[1]][XY[0] - 1].distribEau == 0) {
                if (nbRouteAutour > 0) {
                    totalRoute++;
                    nbCases[totalRoute] = nbCases[numeroRouteEnCours];
                    numeroRouteEnCours = totalRoute;
                }
                nbRouteAutour++;
                enfiler(&f, XY[0] - 1, XY[1], numeroRouteEnCours);
                matriceCases[XY[1]][XY[0] - 1].distribEau = 1;

            }
        }
        //Case droite
        if( XY[1]>0 && XY[0]+1>0 && XY[1]<35 &&  XY[0]+1<45) {
            if (matriceCases[XY[1]][XY[0] + 1].type == 1 && matriceCases[XY[1]][XY[0] + 1].distribEau == 0) {
                if (nbRouteAutour > 0) {
                    totalRoute++;
                    nbCases[totalRoute] = nbCases[numeroRouteEnCours];
                    numeroRouteEnCours = totalRoute;
                }
                nbRouteAutour++;
                enfiler(&f, XY[0] + 1, XY[1], numeroRouteEnCours);
                matriceCases[XY[1]][XY[0] + 1].distribEau = 1;

            }
        }
        //Case dessus
        if( XY[1]-1>0 && XY[0]>0 && XY[1]-1<35 &&  XY[0]<45) {
            if (matriceCases[XY[1] - 1][XY[0]].type == 1 && matriceCases[XY[1] - 1][XY[0]].distribEau == 0) {
                if (nbRouteAutour > 0) {
                    totalRoute++;
                    nbCases[totalRoute] = nbCases[numeroRouteEnCours];
                    numeroRouteEnCours = totalRoute;
                }
                nbRouteAutour++;
                enfiler(&f, XY[0], XY[1] - 1, numeroRouteEnCours);
                matriceCases[XY[1] - 1][XY[0]].distribEau = 1;

            }
        }

        //Case dessous
        if( XY[1]+1>0 && XY[0]>0 && XY[1]+1<35 &&  XY[0]<45) {
            if (matriceCases[XY[1] + 1][XY[0]].type == 1 && matriceCases[XY[1] + 1][XY[0]].distribEau == 0) {
                if (nbRouteAutour > 0) {
                    totalRoute++;
                    nbCases[totalRoute] = nbCases[numeroRouteEnCours];
                    numeroRouteEnCours = totalRoute;
                }
                nbRouteAutour++;
                enfiler(&f, XY[0], XY[1] + 1, numeroRouteEnCours);
                matriceCases[XY[1] + 1][XY[0]].distribEau = 1;

            }
        }

    }
    for (int i = 0; i < NB_LIGNES; i++) {
        for (int j = 0; j < NB_COLONNES; j++) {
            matriceCases[i][j].distribEau=0;
        }
    }
    return nbCentrale;
}

int distributionEvolutionELEC(Case** matriceCases,Global* global,Habitation* habitation){
    int caseX1 = 0;
    int caseY1 = 0;
    int caseX2 = 0;
    int caseY2 = 0;
    int nbCentraleRelie = 0;
    int tabCentraleRelie[10] = {-1};
    for(int i=0;i<10;i++){
        tabCentraleRelie[i]=-1;
    }
    int quantiteRestante = 0;
    for (int i = 0; i < NB_LIGNES; i++) {
        for (int j = 0; j < NB_COLONNES; j++) {
            if (matriceCases[i][j].pHabitation != NULL &&
                matriceCases[i][j].pHabitation->parcoureMatriceHabitation != 0) {
                matriceCases[i][j].pHabitation->parcoureMatriceHabitation = 0;
            }
        }
    }
    if (habitation->alimElec == habitation->nbHabitants) {
        for (int i = 0; i < NB_LIGNES; i++) {
            for (int j = 0; j < NB_COLONNES; j++) {
                if (matriceCases[i][j].pHabitation != NULL &&
                    matriceCases[i][j].pHabitation == habitation &&
                    matriceCases[i][j].pHabitation->parcoureMatriceHabitation == 0) {
                    caseX1 = j;
                    caseY1 = i;
                    caseX2 = caseX1 + 2;
                    caseY2 = caseY1 + 2;
                    matriceCases[i][j].pHabitation->parcoureMatriceHabitation = 1;
                }
            }
        }
        matriceCases[caseY1][caseX1].pHabitation->parcoureMatriceHabitation = 0;

        for (int a = caseX1 - 1; a < caseX2 + 2; a += TAILLE_X_HABITATION + 1) {
            for (int b = caseY1; b < caseY2 + 1; b++) {
                if (a > 0 && b > 0) {
                    if (matriceCases[b][a].type == 1) {
                        nbCentraleRelie = bfsEvolutionVerificationELEC(matriceCases, tabCentraleRelie, a, b,
                                                                      nbCentraleRelie);
                    }
                }
            }
        }
        for (int b = caseY1 - 1; b < caseY2 + 2; b += TAILLE_Y_HABITATION + 1) {
            for (int a = caseX1; a < caseX2 + 1; a++) {
                if (a > 0 && b > 0) {
                    if (matriceCases[b][a].type == 1) {
                        nbCentraleRelie = bfsEvolutionVerificationELEC(matriceCases, tabCentraleRelie, a, b,
                                                                      nbCentraleRelie);
                    }
                }
            }
        }
        for (int i = 0; i < NB_LIGNES; i++) {
            for (
                    int j = 0;
                    j < NB_COLONNES; j++) {
                if (matriceCases[i][j].pCentrale != NULL && matriceCases[i][j].type == 8
                    && matriceCases[i][j].pCentrale->distribution == 1) {

                    matriceCases[i][j].pCentrale->
                            distribution = 0;
                }
                if (matriceCases[i][j].pHabitation != NULL
                    && matriceCases[i][j].pHabitation->parcoureMatriceHabitation == 1) {

                    matriceCases[i][j].pHabitation->
                            parcoureMatriceHabitation = 0;
                }
            }
        }
        int habitationProche = 0;
        for (int k = 0; k < NB_LIGNES; k++) {
            for (int l = 0; l < NB_COLONNES; l++) {
                if (matriceCases[k][l].pHabitation != NULL &&
                    matriceCases[k][l].pHabitation->parcoureMatriceHabitation == 1) {
                    matriceCases[k][l].pHabitation->parcoureMatriceHabitation = 0;
                }
            }
        }

        for (int i = 0; i < nbCentraleRelie; i++) {
            for (int k = 0; k < NB_LIGNES; k++) {
                for (int l = 0; l < NB_COLONNES; l++) {
                    if (matriceCases[k][l].pCentrale != NULL &&
                        matriceCases[k][l].pCentrale->numero == tabCentraleRelie[i] && matriceCases[k][l].pCentrale->parcoursMatriceChateau==0) {
                        matriceCases[k][l].pCentrale->parcoursMatriceChateau=1;
                        quantiteRestante +=matriceCases[k][l].pCentrale->capacite - matriceCases[k][l].pCentrale->quantiteDistribuee;
                    }
                }
            }
        }
        for (int k = 0; k < NB_LIGNES; k++) {
            for (int l = 0; l < NB_COLONNES; l++) {
                if (matriceCases[k][l].pCentrale != NULL &&
                    matriceCases[k][l].pCentrale->parcoursMatriceChateau == 1) {
                    matriceCases[k][l].pCentrale->parcoursMatriceChateau= 0;
                }
            }
        }

        int quantiteUtile = 0;
        int aEvoluer = habitation->niveau + 1;
        switch (aEvoluer) {

            case 1:
                quantiteUtile = CABANE;
                break;
            case 2:
                quantiteUtile = MAISON;
                break;
            case 3:
                quantiteUtile = IMMEUBLE;
                break;
            case 4:
                quantiteUtile = GRATTE_CIEL;
                break;
            default:

                break;
        }
        if (quantiteRestante >= quantiteUtile) {
            return 1;
        } else {
            return 0;
        }
    }
    else{
        return -1;
    }
}

int ouiNonEvolution(Case** matriceCases,Global* global,Habitation* habitation){
    int eau=0;
    int elec=0;
    eau= distributionEvolutionEAU(matriceCases,global,habitation);
    elec= distributionEvolutionELEC(matriceCases,global,habitation);

    if(eau ==1 && elec==1){
        return 1;
    }
    else{
        return 0;
    }
}





// à la fin mettre distribution à 0 pour tous



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

int placerUneConstruction(Case** matriceCase, Case caseAConstruire, int constructionPossible, int typeDeConstruction, Global* structureGlobale){ // placerUneConstruction (matriceCase, matriceCase[ligneAConstruire][colonneAConstruire], constructionPossible, typeDeConstruction);


    if (constructionPossible == 1){

        //On place une habitation
        if(caseAConstruire.ligne < NB_LIGNES-2 && caseAConstruire.colonne < NB_COLONNES-2) {
            if (typeDeConstruction == 2) {

                //On met un terrain vague
                matriceCase[caseAConstruire.ligne][caseAConstruire.colonne].pHabitation = calloc(1, sizeof(Habitation));
                matriceCase[caseAConstruire.ligne][caseAConstruire.colonne].pHabitation->coordXHG = caseAConstruire.x;
                matriceCase[caseAConstruire.ligne][caseAConstruire.colonne].pHabitation->coordYHG = caseAConstruire.y;
                matriceCase[caseAConstruire.ligne][caseAConstruire.colonne].pHabitation->numero = structureGlobale->nbHabitation+1;
                matriceCase[caseAConstruire.ligne][caseAConstruire.colonne].pHabitation->parcoureMatriceHabitation=0;
                structureGlobale->nbHabitation+=1;
                for (int i=0;i<10;i++){
                    matriceCase[caseAConstruire.ligne][caseAConstruire.colonne].pHabitation->nbCasesParChateau[i].nbCases=0;
                    matriceCase[caseAConstruire.ligne][caseAConstruire.colonne].pHabitation->nbCasesParChateau[i].dejaAlim=0;
                    matriceCase[caseAConstruire.ligne][caseAConstruire.colonne].pHabitation->nbCasesParChateau[i].numChateau=0;
                }

                for (int i = caseAConstruire.ligne; i < caseAConstruire.ligne + 3; i++) {
                    for (int j = caseAConstruire.colonne; j < caseAConstruire.colonne + 3; j++) {

                        matriceCase[i][j].type = 2;
                        matriceCase[i][j].pHabitation = matriceCase[caseAConstruire.ligne][caseAConstruire.colonne].pHabitation;
                    }
                }

                dessinerCarte(matriceCase);
                al_draw_filled_rectangle(417, 10, 535, 35, al_map_rgb(37,92,149));


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
                matriceCase[caseAConstruire.ligne][caseAConstruire.colonne].pChateau->capacite = 5000;


                for (int i = caseAConstruire.ligne; i < caseAConstruire.ligne + 6; i++) {
                    for (int j = caseAConstruire.colonne; j < caseAConstruire.colonne + 4; j++) {

                        matriceCase[i][j].type = 7;
                        matriceCase[i][j].pChateau = matriceCase[caseAConstruire.ligne][caseAConstruire.colonne].pChateau;
                    }
                }
                dessinerCarte(matriceCase);
                al_draw_filled_rectangle(617, 10, 735, 35, al_map_rgb(37,92,149));
                al_draw_filled_rectangle(417, 10, 535, 35, al_map_rgb(37,92,149));

                al_flip_display();
                structureGlobale->nbChateau ++;

                return 0;
            }

                //On place une centrale
            else if (typeDeConstruction == 8) {

                //On met une centrale
                matriceCase[caseAConstruire.ligne][caseAConstruire.colonne].pCentrale = calloc(1, sizeof(Centrale));
                matriceCase[caseAConstruire.ligne][caseAConstruire.colonne].pCentrale->coordXHG = caseAConstruire.x;
                matriceCase[caseAConstruire.ligne][caseAConstruire.colonne].pCentrale->coordYHG = caseAConstruire.y;
                matriceCase[caseAConstruire.ligne][caseAConstruire.colonne].pCentrale->capacite=5000;
                for (int i = caseAConstruire.ligne; i < caseAConstruire.ligne + 6; i++) {
                    for (int j = caseAConstruire.colonne; j < caseAConstruire.colonne + 4; j++) {

                        matriceCase[i][j].type = 8;
                        matriceCase[i][j].pCentrale = matriceCase[caseAConstruire.ligne][caseAConstruire.colonne].pCentrale;
                    }
                }
                dessinerCarte(matriceCase);
                al_draw_filled_rectangle(817, 10, 935, 35, al_map_rgb(37,92,149));
                al_draw_filled_rectangle(417, 10, 535, 35, al_map_rgb(37,92,149));

                al_flip_display();
                structureGlobale->nbCentrale ++;
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

bool func_bouton(bool clic_mouse, int x_mouse, int y_mouse, int x1, int x2, int y1, int y2){
    if (clic_mouse == true && x_mouse < x2 && x_mouse > x1 && y_mouse < y2 && y_mouse > y1) {
        al_draw_filled_rectangle(x1, y1, x2, y2, al_map_rgba(0, 0, 0, 120));
        return true;
    }
    else{return false;}
}


int calculerNbHabitants(Case** matriceCase){

    int nbHabitants = 0;

    for (int i = 0; i < NB_LIGNES; i++) {
        for (int j = 0; j < NB_COLONNES; j++) {
            if (matriceCase[i][j].pHabitation != NULL && matriceCase[i][j].pHabitation->estDessine == 0) {

                nbHabitants += matriceCase[i][j].pHabitation->nbHabitants;
                matriceCase[i][j].pHabitation->estDessine = 1;
            }
        }
    }
    for (int i = 0; i < NB_LIGNES; i++) {
        for (int j = 0; j < NB_COLONNES; j++) {
            if (matriceCase[i][j].pHabitation != NULL) {
                matriceCase[i][j].pHabitation->estDessine = 0;
            }
        }
    }
    al_draw_filled_rectangle(217, 10, 335, 35, al_map_rgb(37,92,149));
    al_flip_display();
    return nbHabitants;
}



void evolutionHabitation(Case** matriceCase, Global* structureGlobale, Habitation* habitationAEvoluer, int ligneAEvoluer, int colonneAEvoluer, int onPeutEvoluer){

    //Mode communiste
    if (structureGlobale->modeDeJeu == 1) {

        if (onPeutEvoluer == 1){ //Les flux sont-ils suffisants ?
            //Evolution max
            if (habitationAEvoluer->niveau == 4) {}
            else if (habitationAEvoluer->niveau < 4) { //On evolue

                habitationAEvoluer->niveau += 1;
                switch (habitationAEvoluer->niveau) {
                    case 0://TERRAIN_VAGUE
                        matriceCase[ligneAEvoluer][colonneAEvoluer].type = 2;

                        habitationAEvoluer->nbHabitants = TERRAIN_VAGUE;
                        break;
                    case 1://CABANE
                        matriceCase[ligneAEvoluer][colonneAEvoluer].type = 3;

                        habitationAEvoluer->nbHabitants = CABANE;
                        break;
                    case 2://MAISON
                        matriceCase[ligneAEvoluer][colonneAEvoluer].type = 4;

                        habitationAEvoluer->nbHabitants = MAISON;
                        break;
                    case 3://IMMEUBLE
                        matriceCase[ligneAEvoluer][colonneAEvoluer].type = 5;

                        habitationAEvoluer->nbHabitants = IMMEUBLE;
                        break;
                    case 4://GRATTE_CIEL
                        matriceCase[ligneAEvoluer][colonneAEvoluer].type = 6;

                        habitationAEvoluer->nbHabitants = GRATTE_CIEL;
                        break;
                }
                structureGlobale->nbHabitants = calculerNbHabitants(matriceCase);

            }else{
                printf("Erreur evolutionHabitation: niveau %d ne peut evoluer\n", habitationAEvoluer->niveau);
            }
        }

        else if (onPeutEvoluer == 0){
        }

        else if(onPeutEvoluer == -1){ //On regresse
            if (habitationAEvoluer->niveau == 0) {}
            else if (habitationAEvoluer->niveau > 0) { //On regresse

                habitationAEvoluer->niveau -= 1;
                switch (habitationAEvoluer->niveau) {
                    case 0://TERRAIN_VAGUE
                        matriceCase[ligneAEvoluer][colonneAEvoluer].type = 2;
                        habitationAEvoluer->nbHabitants = TERRAIN_VAGUE;
                        break;
                    case 1://CABANE
                        matriceCase[ligneAEvoluer][colonneAEvoluer].type = 3;
                        habitationAEvoluer->nbHabitants = CABANE;
                        break;
                    case 2://MAISON
                        matriceCase[ligneAEvoluer][colonneAEvoluer].type = 4;
                        habitationAEvoluer->nbHabitants = MAISON;
                        break;
                    case 3://IMMEUBLE
                        matriceCase[ligneAEvoluer][colonneAEvoluer].type = 5;
                        habitationAEvoluer->nbHabitants = IMMEUBLE;
                        break;
                    case 4://GRATTE_CIEL
                        matriceCase[ligneAEvoluer][colonneAEvoluer].type = 6;
                        habitationAEvoluer->nbHabitants = GRATTE_CIEL;
                        break;
                }
                structureGlobale->nbHabitants = calculerNbHabitants(matriceCase);
            }
        }
    }

    //Mode capitaliste
    else if (structureGlobale->modeDeJeu == 2){

        //Evolution max
        if (habitationAEvoluer->niveau == 4){

        }else if (habitationAEvoluer->niveau < 4 ){ //On evolue

            habitationAEvoluer->niveau += 1;

            switch (habitationAEvoluer->niveau) {
                case 0://TERRAIN_VAGUE
                    matriceCase[ligneAEvoluer][colonneAEvoluer].type = 2;

                    habitationAEvoluer->nbHabitants = TERRAIN_VAGUE;
                    break;
                case 1://CABANE
                    matriceCase[ligneAEvoluer][colonneAEvoluer].type = 3;

                    habitationAEvoluer->nbHabitants = CABANE;
                    break;
                case 2://MAISON
                    matriceCase[ligneAEvoluer][colonneAEvoluer].type = 4;

                    habitationAEvoluer->nbHabitants = MAISON;
                    break;
                case 3://IMMEUBLE
                    matriceCase[ligneAEvoluer][colonneAEvoluer].type = 5;
                    habitationAEvoluer->nbHabitants = IMMEUBLE;
                    break;
                case 4://GRATTE_CIEL
                    matriceCase[ligneAEvoluer][colonneAEvoluer].type = 6;

                    habitationAEvoluer->nbHabitants = GRATTE_CIEL;
                    break;
            }
            structureGlobale->nbHabitants = calculerNbHabitants(matriceCase);

        }else{
            printf("Erreur evolutionHabitation: niveau %d ne peut evoluer\n", habitationAEvoluer->niveau);
        }
    }
    al_draw_filled_rectangle(417, 10, 535, 35, al_map_rgb(37,92,149));
    structureGlobale->argentBanque += 10;
    al_flip_display();
}

void fonctionPause(ALLEGRO_DISPLAY* fenetre,  ALLEGRO_EVENT_QUEUE* queue, ALLEGRO_EVENT event, ALLEGRO_TIMER* timer, Case** matriceCase, int y1, int y2, int cas){

    bool finPause = false;
    ALLEGRO_FONT *police = NULL;
    police = al_load_font("../Images/adLib.ttf", 20, ALLEGRO_ALIGN_CENTER);

    al_stop_timer(timer);
    al_draw_text(police, al_map_rgb(255,255,255),135, 15, ALLEGRO_ALIGN_CENTER, "PAUSE");

    if (cas == 1){
        niveau1(matriceCase);
    }else if(cas == 2){
        niveau2(matriceCase);
    }
    al_flip_display();

    while (!finPause) {
        al_wait_for_event(queue, &event);
        switch (event.type) {
            case ALLEGRO_EVENT_MOUSE_BUTTON_DOWN:
                if (event.mouse.x > 19 && event.mouse.x < 62 && event.mouse.y > y1 && event.mouse.y < y2) {
                    finPause = true;
                    al_start_timer(timer);
                    al_draw_filled_rectangle(98,5,171,40, al_map_rgb(60,149,253));
                    al_flip_display();

                }
                break;
        }
    }
}