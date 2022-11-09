#include "Initialisation.h"

void initCases(Case** matriceCases){

    for (int i = 0; i < NB_LIGNES; i++) {
        for (int j = 0; j  < NB_COLONNES; j++) {
			matriceCases[i][j].x = (62 + 20*j);
            matriceCases[i][j].y = 34 + 20*i;

            matriceCases[i][j].distribEau=0;

            matriceCases[i][j].pHabitation = NULL;
            matriceCases[i][j].pChateau = NULL;
            matriceCases[i][j].pCentrale = NULL;
            matriceCases[i][j].type = -1;
            matriceCases[i][j].ligne = i;
            matriceCases[i][j].colonne = j;

        }
    }
}

void sauvegarde(Case** matriceCases){
    FILE* pf = fopen("../Carte.txt", "w");
    if(pf != NULL) {
        for (int i = 0; i < NB_LIGNES; i++) {
            for (int j = 0; j  < NB_COLONNES; j++) {
                fprintf(pf,"%d",matriceCases[i][j].type);
            }
            fprintf(pf,"\n");
        }
        fclose(pf);
        pf = NULL;
    }
    else {
        printf("Erreur.");
    }
}

void charger(Case** matriceCases){


}