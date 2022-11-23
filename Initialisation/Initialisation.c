#include "Initialisation.h"
#include "../Carte/Carte.h"

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
    structureGlobale->nbCentrale = 0;
    structureGlobale->nbChateau = 0;
    structureGlobale->nbHabitation=0;

}

//Sauvgarder le timer Habitation
void sauvegarde(Case** matriceCases, Global* structureGlobale){

    //Sauvegarde de la carte
    FILE* carte = fopen("../Carte.txt", "w");
    if(carte != NULL) {
        for (int i = 0; i < NB_LIGNES; i++) {
            for (int j = 0; j  < NB_COLONNES; j++) {
                fprintf(carte,"%d",matriceCases[i][j].type);
            }
            fprintf(carte,"\n");
        }
        fclose(carte);
        carte = NULL;
    }
    else {
        printf("Erreur lecture fichier sauvegarde carte\n");
    }

    //Sauvegarde du jeu
    FILE* fichier = fopen("../Données du jeu.txt", "w");
    if(fichier != NULL) {

        fprintf(fichier, "%d %d %d %d %d", structureGlobale->argentBanque, structureGlobale->nbHabitants, structureGlobale->timerPartieSec, structureGlobale->timerPartieMin, structureGlobale->modeDeJeu);

        fclose(fichier);
        fichier = NULL;
    }
    else {
        printf("Erreur lecture fichier sauvegarde\n");
    }
}

void chargement(Case** matriceCases, Global* structureGlobale){
    lireFichierCarte(matriceCases,structureGlobale);

    FILE * fichier = fopen("../Données du jeu.txt","r");
    if (!fichier)
    {
        printf("Erreur de lecture fichier Données du jeu.txt\n");
        exit(-1);
    }

    fscanf(fichier,"%d %d %d %d %d",&structureGlobale->argentBanque, &structureGlobale->nbHabitants, &structureGlobale->timerPartieSec, &structureGlobale->timerPartieMin, &structureGlobale->modeDeJeu);
}