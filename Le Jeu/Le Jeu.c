#include "Le Jeu.h"
#include "../Carte/Carte.h"
#include "../Fonctions/Fonctions.h"
#include "../Initialisation/Initialisation.h"


int leJeu (ALLEGRO_DISPLAY* fenetre, int modeDeJeu) {

    // Déclarations
    ALLEGRO_TIMER *timer = NULL;
    ALLEGRO_BITMAP *sauvegarde = NULL;
    ALLEGRO_FONT *police = NULL;



    bool fin = false;
    bool pause = false;
    int chrono = 0;


    al_init_font_addon();
    al_init_ttf_addon();
    ALLEGRO_EVENT_QUEUE *queue = NULL;
    ALLEGRO_EVENT event;

    //Création
    sauvegarde = al_load_bitmap("../Images/sauvegardePartie.jpg");
    police = al_load_font("../Images/adLib.ttf", 20, ALLEGRO_ALIGN_CENTER);

    if (!sauvegarde){
        printf("Erreur ouverture image sauvegarde\n");
    }

    timer = al_create_timer(0.5);


    queue = al_create_event_queue();
    al_register_event_source(queue, al_get_display_event_source(fenetre));
    al_register_event_source(queue, al_get_mouse_event_source());
    al_register_event_source(queue, al_get_keyboard_event_source());
    al_register_event_source(queue, al_get_timer_event_source(timer));


    //***************Initialisation du lancement du jeu***************//

    Case** matriceCase = (Case**) calloc(NB_LIGNES, sizeof(Case));
    for(int i = 0; i < NB_COLONNES; i++) {
        matriceCase[i] = (Case*) calloc(NB_COLONNES, sizeof(Case));
    }
    initCases(matriceCase);
    lireFichierCarte(matriceCase);


    Global* structureGlobale = calloc(1, sizeof (Global));;
    initGlobal(structureGlobale);
    structureGlobale->modeDeJeu = modeDeJeu;



    //*************************Premier affichage*************************//

    afficherInterface(fenetre);
    dessinerCarte(matriceCase);
    al_flip_display();


    //*************************Boucle du jeu*************************//

    al_start_timer(timer);

    int ligne = -1, colonne = -1, constructionPossible = -1,
            saveColonne, saveLigne;

    //************************ TEST EAU ******************************//

    int habitant=2000;
    for (int i = 0; i < NB_LIGNES; i++) {
        for (int j = 0; j < NB_COLONNES; j++) {
            if (matriceCase[i][j].pHabitation != NULL && matriceCase[i][j].pHabitation->parcoureMatriceHabitation!=1) {
                matriceCase[i][j].pHabitation->nbHabitants=habitant;
                habitant+=1000;
                matriceCase[i][j].pHabitation->parcoureMatriceHabitation=1;
            }
        }
    }
    for (int i = 0; i < NB_LIGNES; i++) {
        for (int j = 0; j < NB_COLONNES; j++) {
            if (matriceCase[i][j].pHabitation != NULL && matriceCase[i][j].pHabitation->parcoureMatriceHabitation!=0) {
                matriceCase[i][j].pHabitation->parcoureMatriceHabitation=0;
            }
        }
    }

    distributionEau3(matriceCase,structureGlobale);

    for (int i = 0; i < NB_LIGNES; i++) {
        for (int j = 0; j < NB_COLONNES; j++) {
            if (matriceCase[i][j].pHabitation != NULL && matriceCase[i][j].pHabitation->parcoureMatriceHabitation!=1 ) {
                printf("(%d numero maison)=>  ",matriceCase[i][j].pHabitation->numero);
                printf("(%d nb habitant)=>   ",matriceCase[i][j].pHabitation->nbHabitants);
                printf("(%d alim eau via %d cases du %d chateau)\n\n",matriceCase[i][j].pHabitation->alimEau,matriceCase[i][j].pHabitation->nbCaseEau,matriceCase[i][j].pHabitation->numChateauAlim);
                matriceCase[i][j].pHabitation->parcoureMatriceHabitation=1;
            }
        }
    }
    printf("\nfin\n");
    for (int i = 0; i < NB_LIGNES; i++) {
        for (int j = 0; j < NB_COLONNES; j++) {
            if (matriceCase[i][j].pHabitation != NULL && matriceCase[i][j].pHabitation->parcoureMatriceHabitation!=0) {
                matriceCase[i][j].pHabitation->parcoureMatriceHabitation=0;
            }
        }
    }





    while (!fin) {
        al_wait_for_event(queue, &event);
        switch (event.type) {
            case ALLEGRO_EVENT_KEY_UP: {
                switch (event.keyboard.keycode) {
                    case ALLEGRO_KEY_ESCAPE: {
                        fin = true;
                        break;
                    }
                }
                break;
            }
            case ALLEGRO_EVENT_DISPLAY_CLOSE: {
                fin = true;
                break;
            }
            case ALLEGRO_EVENT_MOUSE_BUTTON_DOWN:{
                if (event.mouse.button & 1) {
                    //éléments à droite -> choix construction

                    // choix terrain vague
                    if (event.mouse.x > 1042 && event.mouse.x < 1126 && event.mouse.y > 362 && event.mouse.y < 440) {
                    
                        int paiementPossible = payer(structureGlobale, structureGlobale->coutTerrainVague);
                        if (paiementPossible == 0) {
                            bool finTerrainVague = 0;
                            while (!finTerrainVague) {

                                al_wait_for_event(queue, &event);
                                switch (event.type) {
                                    case ALLEGRO_EVENT_MOUSE_AXES: {
                                        int sourisSurLeJeu;
                                        sourisSurLeJeu = convertirEnCase(event.mouse.x, event.mouse.y, &ligne, &colonne);


                                        if (sourisSurLeJeu == 0) { // La souris est sur la carte
                                            //détection du changement de case
                                            if (saveColonne != colonne || saveLigne != ligne) {

                                                afficherPlacerUneConstruction(matriceCase, matriceCase[ligne][colonne],
                                                                              &constructionPossible, 2);
                                                saveLigne = ligne;
                                                saveColonne = colonne;
                                            }
                                        }else {printf("Souris en dehors du jeu\n");}
                                    }

                              
                                    case ALLEGRO_EVENT_MOUSE_BUTTON_DOWN: {
                                        if ((event.mouse.button & 1) == 1) {

                                            int sourisSurLeJeu;
                                            sourisSurLeJeu = convertirEnCase(event.mouse.x, event.mouse.y, &ligne, &colonne);

                                            if (sourisSurLeJeu == 0) {

                                                int retour = placerUneConstruction(matriceCase, matriceCase[ligne][colonne], constructionPossible, 2,structureGlobale);
                                                if (retour == 0) {
                                                    finTerrainVague = 1;
                                                    structureGlobale->nbHabitation += 1;
                                                } else if (retour == -1) {
                                                    printf("Type inconnu\n");
                                                } else if (retour == 1) {
                                                    printf("Construction impossible\n");
                                                }

                                            } else {
                                                printf("Click en dehors du jeu\n");
                                            }
                                        }
                                    }
                                }
                            }
                        }else{printf("Pas assez d'argent\n");}
                    }

                    // choix centrale électricité
                    if (event.mouse.x > 1042 && event.mouse.x < 1126 && event.mouse.y > 472 && event.mouse.y < 540) {
                        int paiementPossible = payer(structureGlobale, structureGlobale->coutCentrale);
                        if (paiementPossible == 0) {
                            bool finCentrale = 0;
                            while (!finCentrale) {

                                al_wait_for_event(queue, &event);
                                switch (event.type) {
                                    case ALLEGRO_EVENT_MOUSE_AXES: {
                                        int sourisSurLeJeu;
                                        sourisSurLeJeu = convertirEnCase(event.mouse.x, event.mouse.y, &ligne,
                                                                         &colonne);

                                        if (sourisSurLeJeu == 0) { // La souris est sur la carte
                                            //détection du changement de case
                                            if (saveColonne != colonne || saveLigne != ligne) {

                                                afficherPlacerUneConstruction(matriceCase, matriceCase[ligne][colonne],
                                                                              &constructionPossible, 8);
                                                saveLigne = ligne;
                                                saveColonne = colonne;
                                            }
                                        } else {
                                            printf("Souris en dehors du jeu\n");
                                        }
                                    }
                                    case ALLEGRO_EVENT_MOUSE_BUTTON_DOWN: {
                                        if ((event.mouse.button & 1) == 1) {

                                            int sourisSurLeJeu;
                                            sourisSurLeJeu = convertirEnCase(event.mouse.x, event.mouse.y, &ligne,
                                                                             &colonne);
                                            printf("Clique ligne %d, colonne %d\n", ligne, colonne);

                                            if (sourisSurLeJeu == 0) {

                                                int retour = placerUneConstruction(matriceCase, matriceCase[ligne][colonne], constructionPossible, 8,structureGlobale);
                                                if (retour == 0) {
                                                    finCentrale = 1;
                                                } else if (retour == -1) {
                                                    printf("Type inconnu\n");
                                                } else if (retour == 1) {
                                                    printf("Construction impossible\n");
                                                }

                                            } else {
                                                printf("Click en dehors du jeu\n");
                                            }
                                        }
                                    }
                                }
                            }
                        }else{printf("Pas assez d'argent\n");}
                    }

                    // choix chateau d'eau
                    if (event.mouse.x > 1042 && event.mouse.x < 1126 && event.mouse.y > 581 && event.mouse.y < 655) {
                        int paiementPossible = payer(structureGlobale, structureGlobale->coutChateau);
                        if (paiementPossible == 0) {
                            bool finChateau = 0;
                            while (!finChateau) {

                                al_wait_for_event(queue, &event);
                                switch (event.type) {
                                    case ALLEGRO_EVENT_MOUSE_AXES: {
                                        int sourisSurLeJeu;
                                        sourisSurLeJeu = convertirEnCase(event.mouse.x, event.mouse.y, &ligne,
                                                                         &colonne);

                                        if (sourisSurLeJeu == 0) { // La souris est sur la carte
                                            //détection du changement de case
                                            if (saveColonne != colonne || saveLigne != ligne) {

                                                afficherPlacerUneConstruction(matriceCase, matriceCase[ligne][colonne],
                                                                              &constructionPossible, 7);
                                                saveLigne = ligne;
                                                saveColonne = colonne;
                                            }
                                        } else {
                                            printf("Souris en dehors du jeu\n");
                                        }
                                    }
                                    case ALLEGRO_EVENT_MOUSE_BUTTON_DOWN: {
                                        if ((event.mouse.button & 1) == 1) {

                                            int sourisSurLeJeu;
                                            sourisSurLeJeu = convertirEnCase(event.mouse.x, event.mouse.y, &ligne, &colonne);
                                            printf("Clique ligne %d, colonne %d\n", ligne, colonne);

                                            if (sourisSurLeJeu == 0) {

                                                int retour = placerUneConstruction(matriceCase, matriceCase[ligne][colonne], constructionPossible, 7,structureGlobale);
                                                if (retour == 0) {
                                                    finChateau = 1;
                                                } else if (retour == -1) {
                                                    printf("Type inconnu\n");
                                                } else if (retour == 1) {
                                                    printf("Construction impossible\n");
                                                }
                                            } else {
                                                printf("Click en dehors du jeu\n");
                                            }
                                        }
                                    }
                                }
                            }
                        }else{printf("Pas assez d'argent\n");}
                    }

                    // choix ROUTE
                    if (event.mouse.x > 1042 && event.mouse.x < 1126 && event.mouse.y > 692 && event.mouse.y < 757) {
                        int paiementPossible = payer(structureGlobale, structureGlobale->coutRoute);
                        if (paiementPossible == 0) {
                            bool finRoute = 0;
                            while (!finRoute) {

                                al_wait_for_event(queue, &event);
                                switch (event.type) {
                                    case ALLEGRO_EVENT_MOUSE_AXES: {
                                        int sourisSurLeJeu;
                                        sourisSurLeJeu = convertirEnCase(event.mouse.x, event.mouse.y, &ligne,
                                                                         &colonne);

                                        if (sourisSurLeJeu == 0) { // La souris est sur la carte
                                            //détection du changement de case
                                            if (saveColonne != colonne || saveLigne != ligne) {

                                                afficherPlacerUneRoute(matriceCase, matriceCase[ligne][colonne],
                                                                       &constructionPossible);
                                                saveLigne = ligne;
                                                saveColonne = colonne;
                                            }
                                        } else {
                                            printf("Souris en dehors du jeu\n");
                                        }
                                    }
                                    case ALLEGRO_EVENT_MOUSE_BUTTON_DOWN: {
                                        if ((event.mouse.button & 1) == 1) {



                                            int sourisSurLeJeu;
                                            sourisSurLeJeu = convertirEnCase(event.mouse.x, event.mouse.y, &ligne, &colonne);
                                            printf("Clique ligne %d, colonne %d\n", ligne, colonne);

                                            if (sourisSurLeJeu == 0) {

                                                int retour = placerUneRoute(matriceCase, matriceCase[ligne][colonne], constructionPossible);
                                                if (retour == 0) {
                                                    finRoute = 1;
                                                } else if (retour == -1) {
                                                    printf("Type inconnu\n");
                                                } else if (retour == 1) {
                                                    printf("Construction impossible\n");
                                                }
                                            } else {
                                                printf("Click en dehors du jeu\n");
                                            }
                                        }
                                    }
                                }
                            }
                        }else{printf("Pas assez d'argent\n");}

                    }


                    //éléments à gauche
                    //changer niveau de visualisation
                    if (event.mouse.x > 19 && event.mouse.x < 62 && event.mouse.y > 102 && event.mouse.y < 139) {
                    }

                    if (event.mouse.x > 19 && event.mouse.x < 62 &&
                        event.mouse.y > 167 && event.mouse.y < 210 && pause) {
                        pause = false;
                        printf("pause\n");

                    }
                    if (event.mouse.x > 19 && event.mouse.x < 62 &&
                        event.mouse.y > 167 && event.mouse.y < 210 && !pause) {
                        pause = true;
                        printf("marche\n");

                    }
                    if (event.mouse.x > 19 && event.mouse.x < 62 && event.mouse.y > 238 && event.mouse.y < 272) {
                        printf("%d, %d", event.mouse.x, event.mouse.y);
                        al_draw_bitmap(sauvegarde, 0, 0, 0);
                        al_flip_display();
                        if (event.mouse.x > 301 && event.mouse.x < 450 &&
                            event.mouse.y > 402 && event.mouse.y < 470) {
                            // fonction sauvegarder partie
                        } else if (event.mouse.x > 715 && event.mouse.x < 867 && event.mouse.y > 402 &&
                                   event.mouse.y < 470) {
                            fin = true;
                        }
                        // faire une autre fonction pour ça???
                        // affichage de l'écran sauvegarder puis fermeture fenêtre
                    }
                }
                break;
            }
            case ALLEGRO_EVENT_TIMER:{
                if(event.timer.source == timer) {

                    if (chrono == 14) {
                        chrono = 0;
                    }
                    else if(!pause) {
                        chrono +=1;
                        printf("%d\n", chrono);
                    }

                    if(chrono == 0){
                            al_draw_filled_circle(48, 42, 40, al_map_rgb(249, 158, 25));
                            al_draw_text(police, al_map_rgb(255, 255, 255),48, 33,ALLEGRO_ALIGN_CENTER, "0");
                            al_flip_display();
                        }
                    if (chrono == 1) {
                            al_draw_filled_circle(48, 42, 40, al_map_rgb(249, 158, 25));
                            al_draw_text(police, al_map_rgb(255, 255, 255),48, 33,ALLEGRO_ALIGN_CENTER, "1");
                            al_flip_display();
                        }
                    if (chrono == 2) {
                            al_draw_filled_circle(48, 42, 40, al_map_rgb(249, 158, 25));
                            al_draw_text(police, al_map_rgb(255, 255, 255),48, 33,ALLEGRO_ALIGN_CENTER, "2");
                            al_flip_display();
                        }
                    if (chrono == 3) {
                            al_draw_filled_circle(48, 42, 40, al_map_rgb(249, 158, 25));
                            al_draw_text(police, al_map_rgb(255, 255, 255),48, 33,ALLEGRO_ALIGN_CENTER, "3");
                            al_flip_display();
                        }
                    if (chrono == 4) {
                            al_draw_filled_circle(48, 42, 40, al_map_rgb(249, 158, 25));
                            al_draw_text(police, al_map_rgb(255, 255, 255),48, 33,ALLEGRO_ALIGN_CENTER, "4");
                            al_flip_display();
                        }
                    if (chrono == 5) {
                            al_draw_filled_circle(48, 42, 40, al_map_rgb(249, 158, 25));
                            al_draw_text(police, al_map_rgb(255, 255, 255),48, 33,ALLEGRO_ALIGN_CENTER, "5");
                            al_flip_display();
                        }
                    if (chrono == 6) {
                            al_draw_filled_circle(48, 42, 40, al_map_rgb(249, 158, 25));
                            al_draw_text(police, al_map_rgb(255, 255, 255),48, 33,ALLEGRO_ALIGN_CENTER, "6");
                            al_flip_display();
                        }
                    if (chrono == 7){
                            al_draw_filled_circle(48, 42, 40, al_map_rgb(249, 158, 25));
                            al_draw_text(police, al_map_rgb(255, 255, 255),48, 33,ALLEGRO_ALIGN_CENTER, "7");
                            al_flip_display();
                        }
                    if (chrono == 8) {
                            al_draw_filled_circle(48, 42, 40, al_map_rgb(249, 158, 25));
                            al_draw_text(police, al_map_rgb(255, 255, 255),48, 33,ALLEGRO_ALIGN_CENTER, "8");
                            al_flip_display();
                        }
                    if (chrono == 9) {
                            al_draw_filled_circle(48, 42, 40, al_map_rgb(249, 158, 25));
                            al_flip_display();
                            al_draw_text(police, al_map_rgb(255, 255, 255),48, 33,ALLEGRO_ALIGN_CENTER, "9");
                            al_flip_display();
                        }
                    if (chrono == 10){
                            al_draw_filled_circle(48, 42, 40, al_map_rgb(249, 158, 25));
                            al_draw_text(police, al_map_rgb(255, 255, 255),48, 33,ALLEGRO_ALIGN_CENTER, "10");
                            al_flip_display();
                        }
                    if (chrono == 11) {
                            al_draw_filled_circle(48, 42, 40, al_map_rgb(249, 158, 25));
                            al_draw_text(police, al_map_rgb(255, 255, 255),48, 33,ALLEGRO_ALIGN_CENTER, "11");
                            al_flip_display();
                        }
                    if (chrono == 12) {
                            al_draw_filled_circle(48, 42, 40, al_map_rgb(249, 158, 25));
                            al_draw_text(police, al_map_rgb(255, 255, 255),48, 33,ALLEGRO_ALIGN_CENTER, "12");
                            al_flip_display();
                        }

                    if (chrono == 13) {
                            al_draw_filled_circle(48, 42, 40, al_map_rgb(249, 158, 25));
                            al_draw_text(police, al_map_rgb(255, 255, 255),48, 33,ALLEGRO_ALIGN_CENTER, "13");
                            al_flip_display();
                        }
                    if (chrono == 14) {
                            al_draw_filled_circle(48, 42, 40, al_map_rgb(249, 158, 25));
                            al_draw_text(police, al_map_rgb(255, 255, 255),48, 33,ALLEGRO_ALIGN_CENTER, "14");
                            al_flip_display();
                        }


                    for (int i = 0; i < NB_LIGNES; i++) {
                        for (int j = 0; j < NB_COLONNES; j++) {
                            if (matriceCase[i][j].pHabitation != NULL && matriceCase[i][j].pHabitation->parcoureMatriceHabitation == 0) {
                                matriceCase[i][j].pHabitation->parcoureMatriceHabitation = 1;

                                if (matriceCase[i][j].pHabitation->timerHabitation == 14) {

                                    evolutionHabitation(matriceCase, structureGlobale, matriceCase[i][j].pHabitation, i, j);

                                    matriceCase[i][j].pHabitation->timerHabitation = 0;
                                } else {
                                    matriceCase[i][j].pHabitation->timerHabitation += 1;
                                    //printf("%d\n a", matriceCase[i][j].pHabitation->timerHabitation);
                                }

                            }
                        }
                    }
                    for (int i = 0; i < NB_LIGNES; i++) {
                        for (int j = 0; j < NB_COLONNES; j++) {
                            if (matriceCase[i][j].pHabitation != NULL) {
                                matriceCase[i][j].pHabitation->parcoureMatriceHabitation = 0;
                            }
                        }
                    }
                    structureGlobale->timerPartie += 1;
                }
            }
        }
    }

    al_destroy_event_queue(queue);
    al_destroy_bitmap (sauvegarde);
    al_destroy_timer(timer);

    queue = NULL;
    timer = NULL;
    sauvegarde = NULL;
    return 0;
}

void afficherInterface(ALLEGRO_DISPLAY* fenetre){
    ALLEGRO_BITMAP *fond = NULL;
    ALLEGRO_FONT *police = NULL;


    fond = al_load_bitmap("../Images/eceCity2.jpg");
    if (!fond){
        printf ("Erreur ouverture image fond\n");
    }


    police = al_load_font("../Images/adLib.ttf", 20, ALLEGRO_ALIGN_CENTER);
    al_draw_bitmap(fond, 0, 0, 0);
    //habitants
    al_draw_text(police, al_map_rgb(255, 255, 255),276, 18,ALLEGRO_ALIGN_CENTER, "texte");
    //argent
    al_draw_text(police, al_map_rgb(255, 255, 255),471, 18,ALLEGRO_ALIGN_CENTER, "texte");
    //eau
    al_draw_text(police, al_map_rgb(255, 255, 255), 661, 18, ALLEGRO_ALIGN_CENTER, "texte");
    //électricité
    al_draw_text(police, al_map_rgb(255, 255, 255),861, 18,ALLEGRO_ALIGN_CENTER, "texte");

    al_draw_filled_circle(48, 42, 40, al_map_rgb(249, 158, 25));






    al_destroy_bitmap(fond);
    al_destroy_font (police);

    fond = NULL;
    police = NULL;
}

/*
void ecranQuitter(ALLEGRO_EVENT_QUEUE *queue){
    al_draw_bitmap(sauvegarde, 0, 0, 0);
    fin = true;
}*/

