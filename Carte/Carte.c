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
                case 0: //Route = canalisation = ligne electrique
                    matriceCases[i][j].type = 0;
                    break;
                case 1: //Herbe(rien)
                    matriceCases[i][j].type = 1;
                    break;
                case 2: //Terrain vague = Ruine
                    matriceCases[i][j].type = 2;
                    break;
                case 3: //Cabane
                    matriceCases[i][j].type = 3;
                    break;
                case 4: //Maison
                    matriceCases[i][j].type = 4;
                    break;
                case 5: //Immeuble
                    matriceCases[i][j].type = 5;
                    break;
                case 6: //Gratte-ciel
                    matriceCases[i][j].type = 6;
                    break;
                case 7: //Chateau
                    matriceCases[i][j].type = 7;
                    break;
                case 8: //Centrale
                    matriceCases[i][j].type = 8;
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
        for (int j = 0; j < NB_COLONES; j++) {

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
