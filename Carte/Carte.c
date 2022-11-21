#include "Carte.h"


void lireFichierCarte(Case** pMatriceCase){

    FILE * ifs = fopen("../Carte.txt","r");
    if (!ifs)
    {
        printf("Erreur de lecture fichier Carte\n");
        exit(-1);
    }

    int chiffreEnCours,
        xPremiereCase, yPremiereCase,numeroHabitation=0,numeroChateau=0;


    for (int ligne = 0; ligne < NB_LIGNES; ligne++) {
        for (int colonne = 0; colonne  < NB_COLONNES; colonne++) {
            fscanf(ifs,"%d",&chiffreEnCours);

            switch (chiffreEnCours)
            {
                case 0: //Herbe(rien)
                    pMatriceCase[ligne][colonne].type = 0;
                    pMatriceCase[ligne][colonne].pHabitation = NULL;
                    pMatriceCase[ligne][colonne].pChateau = NULL;
                    pMatriceCase[ligne][colonne].pCentrale = NULL;
                    break;
                case 1: //Route = canalisation = ligne electrique
                    pMatriceCase[ligne][colonne].type = 1;
                    pMatriceCase[ligne][colonne].pHabitation = NULL;
                    pMatriceCase[ligne][colonne].pChateau = NULL;
                    pMatriceCase[ligne][colonne].pCentrale = NULL;
                    break;
                case 2: //Terrain vague = Ruine
                    pMatriceCase[ligne][colonne].type = 2;
                    break;
                case 3: //Cabane
                    pMatriceCase[ligne][colonne].type = 3;
                    break;
                case 4: //Maison
                    pMatriceCase[ligne][colonne].type = 4;
                    break;
                case 5: //Immeuble
                    pMatriceCase[ligne][colonne].type = 5;
                    break;
                case 6: //Gratte-ciel
                    pMatriceCase[ligne][colonne].type = 6;
                    break;
                case 7: //Chateau
                    pMatriceCase[ligne][colonne].type = 7;
                    break;
                case 8: //Centrale
                    pMatriceCase[ligne][colonne].type = 8;
                    break;
                default:
                    printf("Erreur Carte.txt: Chiffre invalide ligne %d, colone %d", ligne, colonne);
                    break;
            }


            //Cas d'une habitation
            if (chiffreEnCours>=2 && chiffreEnCours<=6 && pMatriceCase[ligne][colonne].pHabitation == NULL){
                pMatriceCase[ligne][colonne].pChateau = NULL;
                pMatriceCase[ligne][colonne].pCentrale = NULL;
                pMatriceCase[ligne][colonne].pHabitation = calloc(1, sizeof (Habitation));
                pMatriceCase[ligne][colonne].pHabitation->estDessine = 0;
                pMatriceCase[ligne][colonne].pHabitation->numero =numeroHabitation;
                numeroHabitation++;
                pMatriceCase[ligne][colonne].pHabitation->nbCaseEau=0;
                for (int i=0;i<10;i++){
                    pMatriceCase[ligne][colonne].pHabitation->nbCasesParChateau[i].nbCases=0;
                    pMatriceCase[ligne][colonne].pHabitation->nbCasesParChateau[i].dejaAlim=0;
                    pMatriceCase[ligne][colonne].pHabitation->nbCasesParChateau[i].numChateau=0;
                }

                xPremiereCase = pMatriceCase[ligne][colonne].x;
                yPremiereCase = pMatriceCase[ligne][colonne].y;

                for (int i = ligne; i < ligne+3; i++) {
                    for (int j = colonne; j < colonne+3; j++) {
                        pMatriceCase[i][j].pHabitation = pMatriceCase[ligne][colonne].pHabitation;
                        pMatriceCase[i][j].pHabitation->coordXHG = xPremiereCase;
                        pMatriceCase[i][j].pHabitation->coordYHG = yPremiereCase;
                    }
                }
            }
            //Cas d'un chateau
            if (chiffreEnCours==7 && pMatriceCase[ligne][colonne].pChateau == NULL){
                pMatriceCase[ligne][colonne].pHabitation = NULL;
                pMatriceCase[ligne][colonne].pCentrale = NULL;
                pMatriceCase[ligne][colonne].pChateau = calloc(1, sizeof (Chateau));
                pMatriceCase[ligne][colonne].pChateau->estDessine = 0;
                pMatriceCase[ligne][colonne].pChateau->capacite = 5000;
                pMatriceCase[ligne][colonne].pChateau->numero = numeroChateau;
                pMatriceCase[ligne][colonne].pChateau->parcoursMatriceChateau = 0;
                numeroChateau++;

                xPremiereCase = pMatriceCase[ligne][colonne].x;
                yPremiereCase = pMatriceCase[ligne][colonne].y;

                for (int i = ligne; i < ligne+6; i++) {
                    for (int j = colonne; j < colonne+4; j++) {
                        pMatriceCase[i][j].pChateau = pMatriceCase[ligne][colonne].pChateau;
                        pMatriceCase[i][j].pChateau->coordXHG = xPremiereCase;
                        pMatriceCase[i][j].pChateau->coordYHG = yPremiereCase;
                    }
                }
            }
            //Cas d'une centrale
            if (chiffreEnCours==8 && pMatriceCase[ligne][colonne].pCentrale == NULL){
                pMatriceCase[ligne][colonne].pHabitation = NULL;
                pMatriceCase[ligne][colonne].pChateau = NULL;
                pMatriceCase[ligne][colonne].pCentrale = calloc(1, sizeof (Centrale));
                pMatriceCase[ligne][colonne].pCentrale->estDessine = 0;

                xPremiereCase = pMatriceCase[ligne][colonne].x;
                yPremiereCase = pMatriceCase[ligne][colonne].y;

                for (int i = ligne; i < ligne+6; i++) {
                    for (int j = colonne; j < colonne+4; j++) {
                        pMatriceCase[i][j].pCentrale = pMatriceCase[ligne][colonne].pCentrale;
                        pMatriceCase[i][j].pCentrale->coordXHG = xPremiereCase;
                        pMatriceCase[i][j].pCentrale->coordYHG = yPremiereCase;
                    }
                }
            }


        }
    }

    fclose(ifs);
    ifs = NULL;
}

void dessinerCarte(Case** pMatriceCase){

    ALLEGRO_BITMAP* herbe;
    ALLEGRO_BITMAP* route;
    ALLEGRO_BITMAP* terrainVague;
    ALLEGRO_BITMAP* cabane;
    ALLEGRO_BITMAP* maison;
    ALLEGRO_BITMAP* immeuble;
    ALLEGRO_BITMAP* gratteCiel;
    ALLEGRO_BITMAP* chateau;
    ALLEGRO_BITMAP* centrale;

    herbe = al_load_bitmap("../images/herbe.jpg");
    if(!herbe) {
        printf("Erreur ouverture image herbe\n");
    }
    route = al_load_bitmap("../images/route.jpg");
    if(!route) {
        printf("Erreur ouverture image route\n");
    }
    terrainVague = al_load_bitmap("../images/Terre.png");
    if(!terrainVague) {
        printf("Erreur ouverture image terrainVague\n");
    }
    cabane = al_load_bitmap("../images/Cabane.png");
    if(!cabane) {
        printf("Erreur ouverture image cabane\n");
    }
    maison = al_load_bitmap("../images/maison.jpg");
    if(!maison) {
        printf("Erreur ouverture image maison\n");
    }
    immeuble = al_load_bitmap("../images/Immeuble.png");
    if(!immeuble) {
        printf("Erreur ouverture image immeuble\n");
    }
    gratteCiel = al_load_bitmap("../images/gratteCiel.jpg");
    if(!gratteCiel) {
        printf("Erreur ouverture image gratteCiel\n");
    }
    chateau = al_load_bitmap("../images/chateau.png");
    if(!chateau) {
        printf("Erreur ouverture image chateau\n");
    }
    centrale = al_load_bitmap("../images/Centrale.png");
    if(!centrale) {
        printf("Erreur ouverture image centrale\n");
    }



    for (int i = 0; i < NB_LIGNES; i++) {
        for (int j = 0; j < NB_COLONNES; j++) {

            switch (pMatriceCase[i][j].type) {
                case 0:
                    al_draw_bitmap(herbe, (float)pMatriceCase[i][j].x, (float)pMatriceCase[i][j].y, 0);
                    break;
                case 1:
                    al_draw_bitmap(route, (float)pMatriceCase[i][j].x, (float)pMatriceCase[i][j].y, 0);
                    break;
                case 2:
                    if (pMatriceCase[i][j].pHabitation->estDessine == 0) {
                        pMatriceCase[i][j].pHabitation->estDessine = 1;
                        al_draw_bitmap(terrainVague, (float) pMatriceCase[i][j].x, (float) pMatriceCase[i][j].y, 0);
                    }
                    break;
                case 3:
                    if(pMatriceCase[i][j].pHabitation->estDessine == 0) {
                        pMatriceCase[i][j].pHabitation->estDessine = 1;
                        al_draw_bitmap(cabane, (float)pMatriceCase[i][j].x, (float)pMatriceCase[i][j].y, 0);
                    }
                    break;
                case 4:
                    if(pMatriceCase[i][j].pHabitation->estDessine == 0) {
                        pMatriceCase[i][j].pHabitation->estDessine = 1;
                        al_draw_bitmap(maison, (float)pMatriceCase[i][j].x, (float)pMatriceCase[i][j].y, 0);
                    }
                    break;
                case 5:
                    if(pMatriceCase[i][j].pHabitation->estDessine == 0) {
                        pMatriceCase[i][j].pHabitation->estDessine = 1;
                        al_draw_bitmap(immeuble, (float)pMatriceCase[i][j].x, (float)pMatriceCase[i][j].y, 0);
                    }
                    break;
                case 6:
                    if(pMatriceCase[i][j].pHabitation->estDessine == 0) {
                        pMatriceCase[i][j].pHabitation->estDessine = 1;
                        al_draw_bitmap(gratteCiel, (float)pMatriceCase[i][j].x, (float)pMatriceCase[i][j].y, 0);
                    }
                    break;
                case 7:
                    if(pMatriceCase[i][j].pChateau->estDessine == 0) {
                        pMatriceCase[i][j].pChateau->estDessine = 1;
                        al_draw_bitmap(chateau, (float)pMatriceCase[i][j].x, (float)pMatriceCase[i][j].y, 0);
                    }
                    break;
                case 8:
                    if(pMatriceCase[i][j].pCentrale->estDessine == 0) {
                        pMatriceCase[i][j].pCentrale->estDessine = 1;
                        al_draw_bitmap(centrale, (float)pMatriceCase[i][j].x, (float)pMatriceCase[i][j].y, 0);
                    }
                    break;
                default:
                    printf("Erreur dessinerCarte : Chiffre invalide ligne %d, colone %d\n", i, j);
                    break;
            }
        }
    }

    for (int i = 0; i < NB_LIGNES; i++) {
        for (int j = 0; j < NB_COLONNES; j++) {
            switch (pMatriceCase[i][j].type) {
                case 2:
                case 3:
                case 4:
                case 5:
                case 6:
                    pMatriceCase[i][j].pHabitation->estDessine = 0;
                    break;
                case 7:
                    pMatriceCase[i][j].pChateau->estDessine = 0;
                    break;
                case 8:
                    pMatriceCase[i][j].pCentrale->estDessine = 0;
                    break;
                default:
                    break;
            }
        }
    }

    al_destroy_bitmap(herbe);
    al_destroy_bitmap(route);
    al_destroy_bitmap(terrainVague);
    al_destroy_bitmap(cabane);
    al_destroy_bitmap(maison);
    al_destroy_bitmap(immeuble);
    al_destroy_bitmap(gratteCiel);
    al_destroy_bitmap(chateau);
    al_destroy_bitmap(centrale);

    herbe = NULL;
    route = NULL;
    terrainVague = NULL;
    cabane = NULL;
    maison = NULL;
    immeuble = NULL;
    gratteCiel = NULL;
    chateau = NULL;
    centrale = NULL;
}


// niveau -1 -> canalisations d'eau, routes + affichage chateaux et maisons alimentées avec taux d'approvisionnement
//Pour chaque construction: quel château l'approvisionne et à quel taux
//Pour chaque chateau leur qté distribuée vs leur capacité (4000/5000)


void niveau1 (Case** pMatriceCase) {

    ALLEGRO_BITMAP *herbe;
    ALLEGRO_BITMAP *route;
    ALLEGRO_BITMAP *cabane;
    ALLEGRO_BITMAP *maison;
    ALLEGRO_BITMAP *immeuble;
    ALLEGRO_BITMAP *gratteCiel;
    ALLEGRO_BITMAP *chateau;
    ALLEGRO_EVENT event;

    herbe = al_load_bitmap("../images/herbe.jpg");
    if (!herbe) {
        printf("Erreur ouverture image herbe");
    }
    route = al_load_bitmap("../images/Route.jpg");
    if (!route) {
        printf("Erreur ouverture image route");
    }
    cabane = al_load_bitmap("../images/Cabane.png");
    if(!cabane) {
        printf("Erreur ouverture image cabane");
    }
    maison = al_load_bitmap("../images/maison.jpg");
    if(!maison) {
        printf("Erreur ouverture image maison");
    }
    immeuble = al_load_bitmap("../images/immeuble.png");
    if(!immeuble) {
        printf("Erreur ouverture image immeuble");
    }
    gratteCiel = al_load_bitmap("../images/gratteCiel.jpg");
    if(!gratteCiel) {
        printf("Erreur ouverture image gratteCiel");
    }
    chateau = al_load_bitmap("../images/chateau.png");
    if (!chateau) {
        printf("Erreur ouverture image chateau");
    }

    for (int i = 0; i < NB_LIGNES; i++) {
        for (int j = 0; j < NB_COLONNES; j++) {

            switch (pMatriceCase[i][j].type) {
                case 0:
                case 8:
                    al_draw_bitmap(herbe, (float) pMatriceCase[i][j].x, (float) pMatriceCase[i][j].y, 0);
                    break;
                case 1:
                    al_draw_bitmap(route, (float) pMatriceCase[i][j].x, (float) pMatriceCase[i][j].y, 0);
                    break;

                case 3:
                    if (pMatriceCase[i][j].pHabitation->estDessine == 0) {
                        pMatriceCase[i][j].pHabitation->estDessine = 1;
                        if (pMatriceCase[i][j].pHabitation->nbHabitants == pMatriceCase[i][j].pHabitation->alimEau) {
                            al_draw_bitmap(cabane, (float) pMatriceCase[i][j].x,(float) pMatriceCase[i][j].y, 0);
                        }
                    }
                    break;
                case 4:
                    if (pMatriceCase[i][j].pHabitation->estDessine == 0) {
                        pMatriceCase[i][j].pHabitation->estDessine = 1;
                        if (pMatriceCase[i][j].pHabitation->nbHabitants == pMatriceCase[i][j].pHabitation->alimEau) {
                            al_draw_bitmap(maison, (float) pMatriceCase[i][j].x,(float) pMatriceCase[i][j].y, 0);
                        }
                    }
                    break;
                case 5:
                    if (pMatriceCase[i][j].pHabitation->estDessine == 0) {
                        pMatriceCase[i][j].pHabitation->estDessine = 1;
                        if (pMatriceCase[i][j].pHabitation->nbHabitants == pMatriceCase[i][j].pHabitation->alimEau) {
                            al_draw_bitmap(immeuble, (float) pMatriceCase[i][j].x,(float) pMatriceCase[i][j].y, 0);
                        }
                    }
                    break;
                case 6:
                    if (pMatriceCase[i][j].pHabitation->estDessine == 0) {
                        pMatriceCase[i][j].pHabitation->estDessine = 1;
                        if (pMatriceCase[i][j].pHabitation->nbHabitants == pMatriceCase[i][j].pHabitation->alimEau) {
                            al_draw_bitmap(gratteCiel, (float) pMatriceCase[i][j].x,(float) pMatriceCase[i][j].y, 0);
                        }
                    }
                    break;
                case 7:
                    if (pMatriceCase[i][j].pChateau->estDessine == 0) {
                        pMatriceCase[i][j].pChateau->estDessine = 1;
                        al_draw_bitmap(chateau, (float) pMatriceCase[i][j].x,(float) pMatriceCase[i][j].y, 0);
                    }
                    break;
                default:
                    break;
            }
        }
    }

    for (int i = 0; i < NB_LIGNES; i++) {
        for (int j = 0; j < NB_COLONNES; j++) {
            switch (pMatriceCase[i][j].type) {
                case 2:
                case 3:
                case 4:
                case 5:
                    pMatriceCase[i][j].pHabitation->estDessine = 0;
                    break;
                case 7:
                    pMatriceCase[i][j].pChateau->estDessine = 0;
                    break;
                default:
                    break;
            }
        }
    }

    al_destroy_bitmap(herbe);
    al_destroy_bitmap(route);
    al_destroy_bitmap(cabane);
    al_destroy_bitmap(maison);
    al_destroy_bitmap(immeuble);
    al_destroy_bitmap(gratteCiel);
    al_destroy_bitmap(chateau);

    herbe = NULL;
    route = NULL;
    cabane = NULL;
    maison = NULL;
    immeuble = NULL;
    gratteCiel = NULL;
    chateau = NULL;
}


// niveau -2 -> réseau élec, routes, centrales, constructions alimentées
// ??highlight les constructions en carence??
//Pour chaque centrale on affiche 2000/5000



void niveau2(Case** pMatriceCase) {

    ALLEGRO_BITMAP *herbe;
    ALLEGRO_BITMAP *route;
    ALLEGRO_BITMAP *cabane;
    ALLEGRO_BITMAP *maison;
    ALLEGRO_BITMAP *immeuble;
    ALLEGRO_BITMAP *gratteCiel;
    ALLEGRO_BITMAP *centrale;
    ALLEGRO_EVENT event;

    herbe = al_load_bitmap("../images/herbe.jpg");
    if (!herbe) {
        printf("Erreur ouverture image herbe");
    }
    route = al_load_bitmap("../images/Route.jpg");
    if (!route) {
        printf("Erreur ouverture image route");
    }
    cabane = al_load_bitmap("../images/Cabane.png");
    if(!cabane) {
        printf("Erreur ouverture image cabane");
    }
    maison = al_load_bitmap("../images/maison.jpg");
    if(!maison) {
        printf("Erreur ouverture image maison");
    }
    immeuble = al_load_bitmap("../images/immeuble.png");
    if(!immeuble) {
        printf("Erreur ouverture image immeuble");
    }
    gratteCiel = al_load_bitmap("../images/gratteCiel.jpg");
    if(!gratteCiel) {
        printf("Erreur ouverture image gratteCiel");
    }
    centrale = al_load_bitmap("../images/Centrale.png");
    if (!centrale) {
        printf("Erreur ouverture image centrale");
    }

    for (int i = 0; i < NB_LIGNES; i++) {
        for (int j = 0; j < NB_COLONNES; j++) {

            switch (pMatriceCase[i][j].type) {
                case 0:
                case 7:
                    al_draw_bitmap(herbe, (float) pMatriceCase[i][j].x, (float) pMatriceCase[i][j].y,0);
                    break;
                case 1:
                    al_draw_bitmap(route, (float) pMatriceCase[i][j].x, (float) pMatriceCase[i][j].y,0);
                    break;
                case 3:
                    if (pMatriceCase[i][j].pHabitation->estDessine == 0) {
                        pMatriceCase[i][j].pHabitation->estDessine = 1;
                        if (pMatriceCase[i][j].pHabitation->nbHabitants == pMatriceCase[i][j].pHabitation->alimElec) {
                            al_draw_bitmap(cabane, (float) pMatriceCase[i][j].x,(float) pMatriceCase[i][j].y, 0);
                        }
                        else if (pMatriceCase[i][j].pHabitation->nbHabitants > pMatriceCase[i][j].pHabitation->alimElec){
                            printf("carence");
                        }
                    }
                    break;
                case 4:
                    if (pMatriceCase[i][j].pHabitation->estDessine == 0) {
                        pMatriceCase[i][j].pHabitation->estDessine = 1;
                        if (pMatriceCase[i][j].pHabitation->nbHabitants == pMatriceCase[i][j].pHabitation->alimElec) {
                            al_draw_bitmap(maison, (float) pMatriceCase[i][j].x,(float) pMatriceCase[i][j].y, 0);
                        }
                        else if (pMatriceCase[i][j].pHabitation->nbHabitants > pMatriceCase[i][j].pHabitation->alimElec){
                            printf("carence");
                        }
                    }
                    break;
                case 5:
                    if (pMatriceCase[i][j].pHabitation->estDessine == 0) {
                        pMatriceCase[i][j].pHabitation->estDessine = 1;
                        if (pMatriceCase[i][j].pHabitation->nbHabitants == pMatriceCase[i][j].pHabitation->alimElec) {
                            al_draw_bitmap(immeuble, (float) pMatriceCase[i][j].x,(float) pMatriceCase[i][j].y, 0);
                        }
                        else if (pMatriceCase[i][j].pHabitation->nbHabitants > pMatriceCase[i][j].pHabitation->alimElec){
                            printf("carence");
                        }
                    }
                    break;
                case 6:
                    if (pMatriceCase[i][j].pHabitation->estDessine == 0) {
                        pMatriceCase[i][j].pHabitation->estDessine = 1;
                        if (pMatriceCase[i][j].pHabitation->nbHabitants == pMatriceCase[i][j].pHabitation->alimElec) {
                            al_draw_bitmap(gratteCiel, (float) pMatriceCase[i][j].x,(float) pMatriceCase[i][j].y, 0);
                        }
                        else if (pMatriceCase[i][j].pHabitation->nbHabitants > pMatriceCase[i][j].pHabitation->alimElec){
                            printf("carence");
                        }
                    }
                    break;
                case 8:
                    if (pMatriceCase[i][j].pCentrale->estDessine == 0) {
                        pMatriceCase[i][j].pCentrale->estDessine = 1;
                        al_draw_bitmap(centrale, (float) pMatriceCase[i][j].x,(float) pMatriceCase[i][j].y, 0);
                    }
                    break;
                default:
                    break;
            }
        }
    }

    for (int i = 0; i < NB_LIGNES; i++) {
        for (int j = 0; j < NB_COLONNES; j++) {
            switch (pMatriceCase[i][j].type) {
                case 2:
                case 3:
                case 4:
                case 5:
                    pMatriceCase[i][j].pHabitation->estDessine = 0;
                    break;
                case 8:
                    pMatriceCase[i][j].pCentrale->estDessine = 0;
                    break;
                default:
                    break;
            }
        }
    }

    al_destroy_bitmap(herbe);
    al_destroy_bitmap(route);
    al_destroy_bitmap(cabane);
    al_destroy_bitmap(maison);
    al_destroy_bitmap(immeuble);
    al_destroy_bitmap(gratteCiel);
    al_destroy_bitmap(centrale);

    herbe = NULL;
    route = NULL;
    cabane = NULL;
    maison = NULL;
    immeuble = NULL;
    gratteCiel = NULL;
    centrale = NULL;
}

//au survol de la souris capacité chateau et centrale

void capaciteChateau(ALLEGRO_DISPLAY* fenetre){
    ALLEGRO_TIMER *timer = NULL;
    bool fin = false;

    al_init_font_addon();
    al_init_ttf_addon();
    ALLEGRO_EVENT_QUEUE *queue = NULL;
    ALLEGRO_EVENT event;

    timer = al_create_timer(0.5);


    queue = al_create_event_queue();
    al_register_event_source(queue, al_get_display_event_source(fenetre));
    al_register_event_source(queue, al_get_mouse_event_source());
    al_register_event_source(queue, al_get_timer_event_source(timer));

    al_start_timer(timer);

    while (!fin){
        al_wait_for_event(queue, &event);
        switch (event.type){
            case ALLEGRO_EVENT_MOUSE_BUTTON_DOWN:{
                if (event.mouse.button & 1) {
                }
            }
        }
    }
}