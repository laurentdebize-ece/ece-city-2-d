#include "Initialisation.h"

void initCases(Case** matriceCases){

    for (int i = 0; i < NB_LIGNES; i++) {
        for (int j = 0; j  < NB_COLONNES; j++) {
            matriceCases[i][j].x = (62 + 20*j);
            matriceCases[i][j].y = 34 + 20*i;
            matriceCases[i][j].pHabitation = NULL;
            matriceCases[i][j].pChateau = NULL;
            matriceCases[i][j].pCentrale = NULL;
            matriceCases[i][j].type = -1;
        }
    }
}