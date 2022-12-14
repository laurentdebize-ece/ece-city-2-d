#include "Le Jeu.h"
#include "../Carte/Carte.h"
#include "../Initialisation/Initialisation.h"


int leJeu (ALLEGRO_DISPLAY* fenetre, int modeDeJeu, bool nouvellePartie) {

    // Déclarations
    ALLEGRO_TIMER *timer = NULL;
    ALLEGRO_BITMAP *sauvegarde = NULL;
    ALLEGRO_FONT *police = NULL;

    bool fin = false;
    bool pause = false;
    int chrono = 0, mois = 1, annee = 2022;
    int capaciteEau, capaciteElec, nbHabitant;

    al_init_font_addon();
    al_init_ttf_addon();
    ALLEGRO_EVENT_QUEUE *queue = NULL;
    ALLEGRO_EVENT event;

    sauvegarde = al_load_bitmap("../Images/sauvegardePartie.jpg");
    police = al_load_font("../Images/adLib.ttf", 20, ALLEGRO_ALIGN_CENTER);

    if (!sauvegarde || !police) {
        printf("Erreur ouverture image Le Jeu\n");
    }

    timer = al_create_timer(1);

    queue = al_create_event_queue();
    al_register_event_source(queue, al_get_display_event_source(fenetre));
    al_register_event_source(queue, al_get_mouse_event_source());
    al_register_event_source(queue, al_get_keyboard_event_source());
    al_register_event_source(queue, al_get_timer_event_source(timer));


    //***************Initialisation du lancement du jeu***************//

    Case **matriceCase = (Case **) calloc(NB_LIGNES, sizeof(Case));
    for (int i = 0; i < NB_COLONNES; i++) {
        matriceCase[i] = (Case *) calloc(NB_COLONNES, sizeof(Case));
    }
    initCases(matriceCase, nouvellePartie);



    Global *structureGlobale = calloc(1, sizeof(Global));;
    initGlobal(structureGlobale, nouvellePartie);
    if(nouvellePartie) {
        fonctionNouvellePartie();
        structureGlobale->modeDeJeu = modeDeJeu;
        lireFichierCarte(matriceCase);
    }
    else {
        chargement(matriceCase, structureGlobale);
    }


    //*************************Premier affichage*************************//

    afficherInterface();
    dessinerCarte(matriceCase);
    al_flip_display();


    //*************************Boucle du jeu*************************//

    al_start_timer(timer);

    int ligne = -1, colonne = -1, constructionPossible = -1,
            saveColonne, saveLigne;

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

                                                afficherPlacerUneConstruction(matriceCase, matriceCase[ligne][colonne],&constructionPossible, 2);
                                                saveLigne = ligne;
                                                saveColonne = colonne;
                                            }
                                        }
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
                                            }
                                        }
                                    }
                                }
                            }
                        }else{
                            al_draw_textf(police, al_map_rgb(255, 0, 0),20, 750,ALLEGRO_ALIGN_LEFT, "Pas assez d'argent");
                            al_flip_display();
                        }
                    }

                    // choix route
                    if (event.mouse.x > 1042 && event.mouse.x < 1126 && event.mouse.y > 472 && event.mouse.y < 540) {
                        int paiementPossible = payer(structureGlobale, structureGlobale->coutRoute);
                        if (paiementPossible == 0) {
                            bool finRoute = 0;
                            while (!finRoute) {

                                al_wait_for_event(queue, &event);
                                switch (event.type) {
                                    case ALLEGRO_EVENT_MOUSE_AXES: {
                                        int sourisSurLeJeu;
                                        sourisSurLeJeu = convertirEnCase(event.mouse.x, event.mouse.y, &ligne,&colonne);

                                        if (sourisSurLeJeu == 0) { // La souris est sur la carte
                                            //détection du changement de case
                                            if (saveColonne != colonne || saveLigne != ligne) {

                                                afficherPlacerUneRoute(matriceCase, matriceCase[ligne][colonne],&constructionPossible);
                                                saveLigne = ligne;
                                                saveColonne = colonne;
                                            }
                                        }
                                    }
                                    case ALLEGRO_EVENT_MOUSE_BUTTON_DOWN: {
                                        if ((event.mouse.button & 1) == 1) {

                                            int sourisSurLeJeu;
                                            sourisSurLeJeu = convertirEnCase(event.mouse.x, event.mouse.y, &ligne, &colonne);

                                            if (sourisSurLeJeu == 0) {

                                                int retour = placerUneRoute(matriceCase, matriceCase[ligne][colonne], constructionPossible);
                                                if (retour == 0) {
                                                    finRoute = 1;
                                                } else if (retour == -1) {
                                                    printf("Type inconnu\n");
                                                } else if (retour == 1) {
                                                    printf("Construction impossible\n");
                                                }
                                            }
                                        }
                                    }
                                }
                            }
                        }else{
                            al_draw_textf(police, al_map_rgb(255, 0, 0),20, 750,ALLEGRO_ALIGN_LEFT, "Pas assez d'argent");
                            al_flip_display();
                        }
                        distributionElec(matriceCase, structureGlobale);
                        distributionEau(matriceCase, structureGlobale);
                    }

                    // choix centrale électricité
                    if (event.mouse.x > 1042 && event.mouse.x < 1126 && event.mouse.y > 692 && event.mouse.y < 757) {
                        int paiementPossible = payer(structureGlobale, structureGlobale->coutCentrale);
                        if (paiementPossible == 0) {
                            bool finCentrale = 0;
                            while (!finCentrale) {

                                al_wait_for_event(queue, &event);
                                switch (event.type) {
                                    case ALLEGRO_EVENT_MOUSE_AXES: {
                                        int sourisSurLeJeu;
                                        sourisSurLeJeu = convertirEnCase(event.mouse.x, event.mouse.y, &ligne,&colonne);

                                        if (sourisSurLeJeu == 0) { // La souris est sur la carte
                                            //détection du changement de case
                                            if (saveColonne != colonne || saveLigne != ligne) {

                                                afficherPlacerUneConstruction(matriceCase, matriceCase[ligne][colonne],&constructionPossible, 8);
                                                saveLigne = ligne;
                                                saveColonne = colonne;
                                            }
                                        }
                                    }
                                    case ALLEGRO_EVENT_MOUSE_BUTTON_DOWN: {
                                        if ((event.mouse.button & 1) == 1) {

                                            int sourisSurLeJeu;
                                            sourisSurLeJeu = convertirEnCase(event.mouse.x, event.mouse.y, &ligne,&colonne);

                                            if (sourisSurLeJeu == 0) {

                                                int retour = placerUneConstruction(matriceCase, matriceCase[ligne][colonne], constructionPossible, 8,structureGlobale);
                                                if (retour == 0) {
                                                    finCentrale = 1;
                                                } else if (retour == -1) {
                                                    printf("Type inconnu\n");
                                                } else if (retour == 1) {
                                                    printf("Construction impossible\n");
                                                }

                                            }
                                        }
                                    }
                                }
                            }
                        }else{
                            al_draw_textf(police, al_map_rgb(255, 0, 0),20, 750,ALLEGRO_ALIGN_LEFT, "Pas assez d'argent");
                            al_flip_display();
                        }
                        distributionEau(matriceCase, structureGlobale);
                        distributionElec(matriceCase, structureGlobale);
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
                                        sourisSurLeJeu = convertirEnCase(event.mouse.x, event.mouse.y, &ligne,&colonne);

                                        if (sourisSurLeJeu == 0) { // La souris est sur la carte
                                            //détection du changement de case
                                            if (saveColonne != colonne || saveLigne != ligne) {

                                                afficherPlacerUneConstruction(matriceCase, matriceCase[ligne][colonne],&constructionPossible, 7);
                                                saveLigne = ligne;
                                                saveColonne = colonne;
                                            }
                                        }
                                    }
                                    case ALLEGRO_EVENT_MOUSE_BUTTON_DOWN: {
                                        if ((event.mouse.button & 1) == 1) {

                                            int sourisSurLeJeu;
                                            sourisSurLeJeu = convertirEnCase(event.mouse.x, event.mouse.y, &ligne, &colonne);

                                            if (sourisSurLeJeu == 0) {

                                                int retour = placerUneConstruction(matriceCase, matriceCase[ligne][colonne], constructionPossible, 7,structureGlobale);
                                                if (retour == 0) {
                                                    finChateau = 1;
                                                } else if (retour == -1) {
                                                    printf("Type inconnu\n");
                                                } else if (retour == 1) {
                                                    printf("Construction impossible\n");
                                                }
                                            }
                                        }
                                    }
                                }
                            }
                        }else{
                            al_draw_textf(police, al_map_rgb(255, 0, 0),20, 750,ALLEGRO_ALIGN_LEFT, "Pas assez d'argent");
                            al_flip_display();
                        }
                        distributionEau(matriceCase, structureGlobale);
                        distributionElec(matriceCase, structureGlobale);

                    }


                    //éléments à gauche
                    //changer niveau de visualisation

                    // Nvx -1
                    if (event.mouse.x > 19 && event.mouse.x < 62 && event.mouse.y > 200 && event.mouse.y < 257) {
                        fonctionPause(fenetre, queue, event, timer, matriceCase, 121, 174, 1);
                    }
                    // Nvx -2
                    if (event.mouse.x > 19 && event.mouse.x < 62 && event.mouse.y > 280 && event.mouse.y < 328) {
                        fonctionPause(fenetre, queue, event, timer, matriceCase, 121, 174, 2);
                    }

                    //Quitter
                    if (event.mouse.x > 19 && event.mouse.x < 62 && event.mouse.y > 444 && event.mouse.y < 488) {
                        fin = ecranQuitter(queue, event, matriceCase, structureGlobale);
                    }
                    //Pause
                    if (event.mouse.x > 19 && event.mouse.x < 62 && event.mouse.y > 359 && event.mouse.y < 403) {
                        fonctionPause(fenetre, queue, event, timer, matriceCase, 359, 403, 3);
                    }
                }
                break;
            }

            case ALLEGRO_EVENT_TIMER:{
                if(event.timer.source == timer) {


                    afficherInterface();
                    dessinerCarte(matriceCase);

                    //****************Pause****************//
                    if (chrono == 14) {
                        chrono = 1;
                        structureGlobale->timerPartieMois ++;
                    }
                    else {
                        chrono +=1;
                    }
                    if (structureGlobale->timerPartieMois == 13) {
                        structureGlobale->timerPartieMois = 1;
                        structureGlobale->timerPartieAnnee++;
                    }
                    if (!pause) {
                        al_draw_filled_circle(48, 42, 45, al_map_rgb(249, 158, 25));
                        al_draw_textf(police, al_map_rgb(255, 255, 255),25, 33,ALLEGRO_ALIGN_CENTER, "%d/",structureGlobale->timerPartieMois);
                        al_draw_textf(police, al_map_rgb(255, 255, 255),65, 33,ALLEGRO_ALIGN_CENTER, "%d",structureGlobale->timerPartieAnnee);
                        al_flip_display();
                    }

                    //****************Evolution timer maison****************//
                    for (int i = 0; i < NB_LIGNES; i++) {
                        for (int j = 0; j < NB_COLONNES; j++) {
                            if (matriceCase[i][j].pHabitation != NULL && matriceCase[i][j].pHabitation->parcoureMatriceHabitation == 0) {
                                matriceCase[i][j].pHabitation->parcoureMatriceHabitation = 1;

                                if (matriceCase[i][j].pHabitation->timerHabitation == 14) {

                                    int onPeutEvoluer= ouiNonEvolution(matriceCase,structureGlobale,matriceCase[i][j].pHabitation);
                                    evolutionHabitation(matriceCase, structureGlobale, matriceCase[i][j].pHabitation, i, j, onPeutEvoluer);
                                    distributionEau(matriceCase, structureGlobale);
                                    distributionElec(matriceCase, structureGlobale);

                                    matriceCase[i][j].pHabitation->timerHabitation = 0;
                                } else {
                                    matriceCase[i][j].pHabitation->timerHabitation += 1;
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
                    structureGlobale->timerPartieSec += 1;

                    if(structureGlobale->timerPartieSec == 60){
                        structureGlobale->timerPartieSec = 0;
                        structureGlobale->timerPartieMin += 1;
                    }
                    al_draw_textf(police, al_map_rgb(255, 255, 255),1100, 20,ALLEGRO_ALIGN_CENTER, "%d : %d",structureGlobale->timerPartieMin, structureGlobale->timerPartieSec);

                    al_draw_filled_circle(48, 42, 45, al_map_rgb(249, 158, 25));
                    al_draw_textf(police, al_map_rgb(255, 255, 255),25, 33,ALLEGRO_ALIGN_CENTER, "%d/",structureGlobale->timerPartieMois);
                    al_draw_textf(police, al_map_rgb(255, 255, 255),65, 33,ALLEGRO_ALIGN_CENTER, "%d",structureGlobale->timerPartieAnnee);

                    capaciteEau = structureGlobale->nbChateau * 5000;
                    capaciteElec = structureGlobale->nbCentrale * 5000;
                    nbHabitant = structureGlobale->nbHabitants;

                    al_draw_filled_rectangle(417, 10, 535, 35, al_map_rgb(37,92,149));
                    //habitants
                    al_draw_textf(police, al_map_rgb(255, 255, 255),276, 18,ALLEGRO_ALIGN_CENTER, "%d", nbHabitant);
                    //argent
                    al_draw_textf(police, al_map_rgb(255, 255, 255),471, 18,ALLEGRO_ALIGN_CENTER, "%d",structureGlobale->argentBanque);
                    //eau
                    al_draw_textf(police, al_map_rgb(255, 255, 255), 661, 18, ALLEGRO_ALIGN_CENTER, "%d", capaciteEau);
                    //électricité
                    al_draw_textf(police, al_map_rgb(255, 255, 255),861, 18,ALLEGRO_ALIGN_CENTER, "%d", capaciteElec);
                    al_flip_display();
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

void afficherInterface(){
    ALLEGRO_BITMAP *fond = NULL;

    fond = al_load_bitmap("../Images/eceCity2.jpg");
    al_draw_bitmap(fond, 0, 0, 0);

    if (!fond){
        printf ("Erreur ouverture image fond\n");
    }

    al_draw_filled_circle(48, 42, 40, al_map_rgb(249, 158, 25));

    al_destroy_bitmap(fond);
    fond = NULL;
}

int ecranQuitter(ALLEGRO_EVENT_QUEUE *queue, ALLEGRO_EVENT event, Case** matriceCase, Global* structureGlobale) {
    bool finQuitter = 0;
    ALLEGRO_BITMAP* image;
    image = al_load_bitmap("../Images/sauvegardePartie.jpg");
    al_draw_bitmap(image, 0, 0, 0);
    al_flip_display();
    al_destroy_bitmap(image);
    image = NULL;
    while (!finQuitter) {
        al_wait_for_event(queue, &event);
        switch (event.type) {
            case ALLEGRO_EVENT_MOUSE_BUTTON_DOWN:
                if (event.mouse.x > 301 && event.mouse.x < 450 && event.mouse.y > 402 && event.mouse.y < 470) {
                    sauvegardeJeu(matriceCase, structureGlobale);
                    printf("on sauvegarde\n");
                    finQuitter = true;
                    return 1;
                }
                if (event.mouse.x > 715 && event.mouse.x < 867 && event.mouse.y > 402 && event.mouse.y < 470) {
                    finQuitter = true;
                    return 1;
                }
                break;
        }
    }
}