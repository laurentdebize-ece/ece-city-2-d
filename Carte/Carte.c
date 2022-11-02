#include "Carte.h"

void lireFichierCarte(Case** matriceCases){

    FILE* fichierCarte = fopen("../Carte.txt","r");
    if (!fichierCarte)
    {
        printf("Erreur de lecture du fichier Carte.txt\n");
        exit(1);
    }

    int chiffreEnCours,
        xPremiereCase, yPremiereCase;


    for (int ligne = 0; ligne < NB_LIGNES; ligne++) {
        for (int colonne = 0; colonne  < NB_COLONNES; colonne++) {
            fscanf(fichierCarte,"%d",&chiffreEnCours);

            switch (chiffreEnCours)
            {
                case 0: //Route = canalisation = ligne electrique
                    matriceCases[ligne][colonne].type = 0;
                    matriceCases[ligne][colonne].pHabitation = NULL;
                    matriceCases[ligne][colonne].pChateau = NULL;
                    matriceCases[ligne][colonne].pCentrale = NULL;
                    break;
                case 1: //Herbe(rien)
                    matriceCases[ligne][colonne].type = 1;
                    matriceCases[ligne][colonne].pHabitation = NULL;
                    matriceCases[ligne][colonne].pChateau = NULL;
                    matriceCases[ligne][colonne].pCentrale = NULL;
                    break;
                case 2: //Terrain vague = Ruine
                    matriceCases[ligne][colonne].type = 2;
                    break;
                case 3: //Cabane
                    matriceCases[ligne][colonne].type = 3;
                    break;
                case 4: //Maison
                    matriceCases[ligne][colonne].type = 4;
                    break;
                case 5: //Immeuble
                    matriceCases[ligne][colonne].type = 5;
                    break;
                case 6: //Gratte-ciel
                    matriceCases[ligne][colonne].type = 6;
                    break;
                case 7: //Chateau
                    matriceCases[ligne][colonne].type = 7;
                    break;
                case 8: //Centrale
                    matriceCases[ligne][colonne].type = 8;
                    break;
                default:
                    printf("Erreur Carte.txt: Chiffre invalide ligne %d, colone %d", ligne, colonne);
                    break;
            }



            //Cas d'une habitation
            if (chiffreEnCours>=2 && chiffreEnCours<=6){
                matriceCases[ligne][colonne].pChateau = NULL;
                matriceCases[ligne][colonne].pCentrale = NULL;

                xPremiereCase = matriceCases[ligne][colonne].x;
                yPremiereCase = matriceCases[ligne][colonne].y;

                for (int i = ligne; i < ligne+3; i++) {
                    for (int j = colonne; j < colonne+3; j++) {
                        matriceCases[i][j].pHabitation->coordXHG = xPremiereCase;
                        matriceCases[i][j].pHabitation->coordYHG = yPremiereCase;
                    }
                }
            }
            //Cas d'un chateau
            if (chiffreEnCours==7){
                matriceCases[ligne][colonne].pHabitation = NULL;
                matriceCases[ligne][colonne].pCentrale = NULL;

                xPremiereCase = matriceCases[ligne][colonne].x;
                yPremiereCase = matriceCases[ligne][colonne].y;

                for (int i = ligne; i < ligne+4; i++) {
                    for (int j = colonne; j < colonne+6; j++) {
                        matriceCases[i][j].pChateau->coordXHG = xPremiereCase;
                        matriceCases[i][j].pChateau->coordYHG = yPremiereCase;
                    }
                }
            }
            //Cas d'une centrale
            if (chiffreEnCours==8){
                matriceCases[ligne][colonne].pHabitation = NULL;
                matriceCases[ligne][colonne].pChateau = NULL;

                xPremiereCase = matriceCases[ligne][colonne].x;
                yPremiereCase = matriceCases[ligne][colonne].y;

                for (int i = ligne; i < ligne+4; i++) {
                    for (int j = colonne; j < colonne+6; j++) {
                        matriceCases[i][j].pCentrale->coordXHG = xPremiereCase;
                        matriceCases[i][j].pCentrale->coordYHG = yPremiereCase;
                    }
                }
            }


        }
    }

    fclose(fichierCarte);
    fichierCarte = NULL;
}

void afficherCarte(Case** matriceCases){

    ALLEGRO_BITMAP* route;
    ALLEGRO_BITMAP* herbe;
    ALLEGRO_BITMAP* terrainVague;
    ALLEGRO_BITMAP* cabane;
    ALLEGRO_BITMAP* maison;
    ALLEGRO_BITMAP* immeuble;
    ALLEGRO_BITMAP* gratteCiel;
    ALLEGRO_BITMAP* chateau;
    ALLEGRO_BITMAP* centrale;

    route = al_load_bitmap("../images/route.jpg");
    if(!route) {
        printf("Erreur ouverture image route");
    }
    herbe = al_load_bitmap("../images/Herbe.jpg");
    if(!herbe) {
        printf("Erreur ouverture image Herbe");
    }
    terrainVague = al_load_bitmap("../images/terrainVague.jpg");
    if(!terrainVague) {
        printf("Erreur ouverture image terrainVague");
    }
    cabane = al_load_bitmap("../images/cabane.jpg");
    if(!cabane) {
        printf("Erreur ouverture image cabane");
    }
    maison = al_load_bitmap("../images/maison.jpg");
    if(!maison) {
        printf("Erreur ouverture image maison");
    }
    immeuble = al_load_bitmap("../images/immeuble.jpg");
    if(!immeuble) {
        printf("Erreur ouverture image immeuble");
    }
    gratteCiel = al_load_bitmap("../images/gratteCiel.jpg");
    if(!gratteCiel) {
        printf("Erreur ouverture image gratteCiel");
    }
    chateau = al_load_bitmap("../images/chateau.jpg");
    if(!chateau) {
        printf("Erreur ouverture image chateau");
    }
    centrale = al_load_bitmap("../images/centrale.jpg");
    if(!centrale) {
        printf("Erreur ouverture image centrale");
    }


    for (int i = 0; i < NB_LIGNES; i++) {
        for (int j = 0; j < NB_COLONNES; j++) {

            switch (matriceCases[i][j].type) {
                case 0:
                    al_draw_bitmap(route, (float)matriceCases[i][j].x, (float)matriceCases[i][j].y, 0);
                    break;
                case 1:
                    al_draw_bitmap(herbe, (float)matriceCases[i][j].x, (float)matriceCases[i][j].y, 0);
                    break;
                case 2:
                    al_draw_bitmap(terrainVague, (float)matriceCases[i][j].x, (float)matriceCases[i][j].y, 0);
                    break;
                case 3:
                    al_draw_bitmap(cabane, (float)matriceCases[i][j].x, (float)matriceCases[i][j].y, 0);
                    break;
                case 4:
                    al_draw_bitmap(maison, (float)matriceCases[i][j].x, (float)matriceCases[i][j].y, 0);
                    break;
                case 5:
                    al_draw_bitmap(immeuble, (float)matriceCases[i][j].x, (float)matriceCases[i][j].y, 0);
                    break;
                case 6:
                    al_draw_bitmap(gratteCiel, (float)matriceCases[i][j].x, (float)matriceCases[i][j].y, 0);
                    break;
                case 7:
                    al_draw_bitmap(chateau, (float)matriceCases[i][j].x, (float)matriceCases[i][j].y, 0);
                    break;
                case 8:
                    al_draw_bitmap(centrale, (float)matriceCases[i][j].x, (float)matriceCases[i][j].y, 0);
                    break;
            }
        }
    }

    al_destroy_bitmap(route);
    al_destroy_bitmap(herbe);
    al_destroy_bitmap(terrainVague);
    al_destroy_bitmap(cabane);
    al_destroy_bitmap(maison);
    al_destroy_bitmap(immeuble);
    al_destroy_bitmap(gratteCiel);
    al_destroy_bitmap(chateau);
    al_destroy_bitmap(centrale);

    route = NULL;
    herbe = NULL;
    terrainVague = NULL;
    cabane = NULL;
    maison = NULL;
    immeuble = NULL;
    gratteCiel = NULL;
    chateau = NULL;
    centrale = NULL;
}
