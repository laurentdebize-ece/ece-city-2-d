#include "Le Jeu.h"
#include "../Carte/Carte.h"


#define LARGEUR 1024
#define HAUTEUR 768

/* Déclarations
 * Initialisations et installations
 * Création
 * 1er affichage
 * Boucle d'événements
 * Libération
*/


//recuperer fenetre en paramètres

int leJeu (ALLEGRO_DISPLAY* fenetre) {

    // Déclarations
    ALLEGRO_TIMER *timer = NULL;
    ALLEGRO_BITMAP *sauvegarde = NULL;

    bool fin = false;


    al_init_font_addon();
    al_init_ttf_addon();
    ALLEGRO_EVENT_QUEUE *queue = NULL;
    ALLEGRO_EVENT event;


    //Création
    sauvegarde = al_load_bitmap("../Images/sauvegardePartie.jpg");
    if (!sauvegarde){
        printf("Erreur ouverture image sauvegarde\n");
    }


    timer = al_create_timer(1.0 / 40.0);
    al_start_timer(timer);

    queue = al_create_event_queue();
    al_register_event_source(queue, al_get_display_event_source(fenetre));
    al_register_event_source(queue, al_get_mouse_event_source());
    al_register_event_source(queue, al_get_keyboard_event_source());


    afficherInterface(fenetre);
    //dessinerCarte();
    al_flip_display();

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
                    if (event.mouse.x > 930 && event.mouse.x < 1012 &&
                        event.mouse.y > 335 && event.mouse.x < 410) {
                        //choix terrain vague
                    }
                    if (event.mouse.x > 930 && event.mouse.x < 1012 &&
                        event.mouse.y > 440 && event.mouse.x < 514) {
                        // choix centrale électricité
                    }
                    if (event.mouse.x > 930 && event.mouse.x < 1012 &&
                        event.mouse.y > 545 && event.mouse.x < 617) {
                        // choix chateau d'eau
                    }
                    if (event.mouse.x > 930 && event.mouse.x < 1012 &&
                        event.mouse.y > 650 && event.mouse.x < 734) {
                        // choix usine
                    }
                    //éléments à gauche
                    if (event.mouse.x > 6 && event.mouse.x < 60 &&
                        event.mouse.y > 85 && event.mouse.y < 140) {
                        //changer niveau de visualisation
                    }
                    if (event.mouse.x > 6 && event.mouse.x < 60 &&
                        event.mouse.y > 150 && event.mouse.y < 205) {
                        //PAUSE
                    }
                    if (event.mouse.x > 6 && event.mouse.x < 60 && event.mouse.y > 215 && event.mouse.y < 270) {
                        printf("%d, %d", event.mouse.x, event.mouse.y);
                        al_draw_bitmap(sauvegarde, 0, 0, 0);
                        al_flip_display();
                        if (event.mouse.x > 223 && event.mouse.x < 385 &&
                            event.mouse.y > 406 && event.mouse.y < 482) {
                            // fonction sauvegarder partie
                        } else if (event.mouse.x > 631 && event.mouse.x < 802 && event.mouse.y > 406 &&
                                   event.mouse.y < 482) {
                            fin = true;
                        }
                        // faire une autre fonction pour ça???
                        // affichage de l'écran sauvegarder puis fermeture fenêtre
                    }
                }
                break;
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


    fond = al_load_bitmap("../Images/eceCity.jpg");
    if (!fond){
        printf ("Erreur ouverture image fond\n");
    }


    police = al_load_font("../Images/adLib.ttf", 20, ALLEGRO_ALIGN_CENTER);
    al_draw_bitmap(fond, 0, 0, 0);
    //habitants
    al_draw_text(police, al_map_rgb(255, 255, 255),266, 20,ALLEGRO_ALIGN_CENTER, "texte");
    //argent
    al_draw_text(police, al_map_rgb(255, 255, 255),444, 20,ALLEGRO_ALIGN_CENTER, "texte");
    //eau
    al_draw_text(police, al_map_rgb(255, 255, 255), 625, 20, ALLEGRO_ALIGN_CENTER, "texte");
    //électricité
    al_draw_text(police, al_map_rgb(255, 255, 255),807, 20,ALLEGRO_ALIGN_CENTER, "texte");



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