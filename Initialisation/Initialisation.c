#include "Initialisation.h"

void initCases(Case** matriceCases){

    for (int i = 0; i < NB_LIGNES; i++) {
        for (int j = 0; j  < NB_COLONNES; j++) {
			matriceCases[i][j].x = DECALAGE_GRILLE_X + 20*j;
            matriceCases[i][j].y = DECALAGE_GRILLE_Y + 20*i;

            matriceCases[i][j].distribEau = 0;

            matriceCases[i][j].pHabitation = NULL;
            matriceCases[i][j].pChateau = NULL;
            matriceCases[i][j].pCentrale = NULL;
            matriceCases[i][j].type = -1;
            matriceCases[i][j].ligne = i;
            matriceCases[i][j].colonne = j;
        }
    }
}

void initGlobal(Global* structureGlobale){

    structureGlobale->argentBanque = 500000;
    structureGlobale->coutRoute = 10;
    structureGlobale->coutChateau = 100000;
    structureGlobale->coutCentrale = 100000;
    structureGlobale->coutTerrainVague = 1000;
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