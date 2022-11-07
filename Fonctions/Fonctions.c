#include "Fonctions.h"


#define TAILLE_X_CHATEAU 4
#define TAILLE_Y_CHATEAU 6

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
        }
    }

    enfiler(&f,x,y);
    matriceCases[y][x].distribEau=1;
    nbCases++;

    while (f.tete != NULL) {
        defiler(&f,XY);

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

    int nbHabitation = global.nbHabitation;
    Habitation* habEau[nbHabitation];


    //récupération de la coordoonée X et Y du chateau
    for (int i = 0; i < NB_LIGNES; i++) {
        for (int j = 0; j < NB_COLONNES; j++) {
            if(matriceCases[i][j].pChateau != NULL && matriceCases[i][j].type == 7
            && matriceCases[i][j].pChateau->distribution==0){

                caseX1=j;
                caseY1=i;
                caseX2=caseX1+3;
                caseY2=caseX1+5;
                matriceCases[i][j].pChateau->distribution=1;
            }
        }
    }

    //vérification des routes autour pour début BFS
    for (int j = caseX1-1; j < caseX2+2; j+= TAILLE_X_CHATEAU+1) {
        for (int i = caseY1; j < caseY2+1; j++) {
            if(matriceCases[i][j].type == 0){
                bfsEau(matriceCases,habEau,j,i);
            }
        }
    }
    for (int i = caseY1-1; i < caseY2+2; i+= TAILLE_Y_CHATEAU+1) {
        for (int j = caseX1; j < caseX2+1; j++) {
            if(matriceCases[i][j].type == 0){
                bfsEau(matriceCases,habEau,j,i);
            }
        }
    }


    for (int i=0;i<nbHabitation;i++){


    }



}



// à la fin mettre distribution à 0 pour tous