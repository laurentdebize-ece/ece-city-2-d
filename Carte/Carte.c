#include "Carte.h"

void lireFichierCarte(Case** matriceCases){

    FILE* fichierCarte = fopen("../Carte.txt","r");
    if (!fichierCarte)
    {
        printf("Erreur de lecture du fichier Carte.txt\n");
        exit(1);
    }

    int chiffreEnCours;
    for (int i = 0; i < NB_LIGNES; i++) {
        for (int j = 0; j  < NB_COLONES; j++) {
            fscanf(fichierCarte,"%d",&chiffreEnCours);

            switch (chiffreEnCours)
            {
                case 0: //Herbe(rien)
                    matriceCases[i][j].type = 0;
                    break;
                case 1: //Terrain vague = Ruine
                    matriceCases[i][j].type = 1;
                    break;
                case 2: //Cabane
                    matriceCases[i][j].type = 2;
                    break;
                case 3: //Maison
                    matriceCases[i][j].type = 3;
                    break;
                case 4: //Immeuble
                    matriceCases[i][j].type = 4;
                    break;
                case 5: //Gratte-ciel
                    matriceCases[i][j].type = 5;
                    break;
                case 6: //Chateau
                    matriceCases[i][j].type = 6;
                    break;
                case 7: //Centrale
                    matriceCases[i][j].type = 7;
                    break;
                default:
                    printf("Erreur Carte.txt: Chiffre invalide ligne %d, colone %d", i, j);
                    break;
            }
        }
    }

    fclose(fichierCarte);
    fichierCarte = NULL;
}

void afficherCarte(Case** matriceCases){

    ALLEGRO_BITMAP* herbe;
    ALLEGRO_BITMAP* terrainVague;

    herbe = al_load_bitmap("../images/Herbe.jpg");
    if(!herbe) {
        printf("Erreur ouverture image Herbe");
    }
    terrainVague = al_load_bitmap("../images/terrainVague.jpg");
    if(!terrainVague) {
        printf("Erreur ouverture image terrainVague");
    }


    for (int i = 0; i < NB_LIGNES; i++) {
        for (int j = 0; j < NB_COLONES; j++) {

            switch (matriceCases[i][j].type) {
                case 0:
                    al_draw_bitmap(herbe, (float)matriceCases[i][j].x, (float)matriceCases[i][j].x, 0);
                    break;
                case 1:
                    al_draw_bitmap(terrainVague, (float)matriceCases[i][j].x, (float)matriceCases[i][j].x, 0);
                    break;
            }
        }
    }

    al_destroy_bitmap(herbe);
    al_destroy_bitmap(terrainVague);

    herbe = NULL;
    terrainVague = NULL;
}
