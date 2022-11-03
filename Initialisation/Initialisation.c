#include "Initialisation.h"

void initCases(Case** matriceCases){

    for (int i = 0; i < NB_LIGNES; i++) {
        for (int j = 0; j  < NB_COLONES; j++) {
            matriceCases[i][j].x = 62 + 20*j;
            matriceCases[i][j].y = 34 + 20*i;
        }
    }
}