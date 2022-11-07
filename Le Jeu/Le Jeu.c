#include "Le Jeu.h"


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

int afficherInterface () {

    // Déclarations
    ALLEGRO_DISPLAY *display = NULL;
    ALLEGRO_BITMAP *fond = NULL;
    ALLEGRO_BITMAP *sauvegarde = NULL;
    ALLEGRO_TIMER *timer = NULL;
    ALLEGRO_FONT *police = NULL;

    bool fin = false;

    //Initialisations
    assert(al_init());
    assert(al_init_primitives_addon());
    assert(al_install_mouse());
    assert(al_install_keyboard());
    assert (al_init_image_addon());

    al_init_font_addon();
    al_init_ttf_addon();
    ALLEGRO_EVENT_QUEUE *queue = NULL;
    ALLEGRO_EVENT event;
    fond = al_load_bitmap("../Images/eceCity.jpg");
    if (!fond){
        printf ("Erreur ouverture image fond\n")
    }
    sauvegarde = al_load_bitmap("../Images/sauvegardePartie.jpg");
    if (!sauvegarde){
        printf("Erreur ouverture image sauvegarde\n");
    }

    //Création
    display = al_create_display(LARGEUR, HAUTEUR);
    assert(al_init_ttf_addon());

    assert(display != NULL);
    al_set_window_position(display, 200, 15);
    al_clear_to_color(al_map_rgb(200, 206, 200));
    police = al_load_font("../Images/adLib.ttf", taille, ALLEGRO_ALIGN_CENTER);
    al_draw_bitmap(fond, 0, 0, 0);
    timer = al_create_timer(1.0 / 40.0);

    if (timer == NULL) {
        al_destroy_display(display);
        exit(EXIT_FAILURE);
    }
    al_start_timer(timer);
    queue = al_create_event_queue();
    if (queue == NULL) {
        al_destroy_display(display);
        al_destroy_timer(timer);
        exit(EXIT_FAILURE);
    }

    al_register_event_source(queue, al_get_display_event_source(display));

    //habitants
    al_draw_text(police, al_map_rgb(255, 255, 255),266, 20,ALLEGRO_ALIGN_CENTER, "texte");
    //argent
    al_draw_text(police, al_map_rgb(255, 255, 255),444, 20,ALLEGRO_ALIGN_CENTER, "texte");
    //eau
    al_draw_text(police, al_map_rgb(255, 255, 255), 625, 20, ALLEGRO_ALIGN_CENTER, "texte");
    //électricité
    al_draw_text(police, al_map_rgb(255, 255, 255),807, 20,ALLEGRO_ALIGN_CENTER, "texte");

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
                //éléments à droite -> choix construction
                if (event.mouse.x > 930 && event.mouse.x < 1012 &&
                    event.mouse.y > 335 && event.mouse.x < 410){
                    //choix terrain vague
                }
                if (event.mouse.x > 930 && event.mouse.x < 1012 &&
                    event.mouse.y > 440 && event.mouse.x < 514) {
                    // choix centrale électricité
                }
                if (event.mouse.x > 930 && event.mouse.x < 1012 &&
                    event.mouse.y > 545 && event.mouse.x < 617){
                    // choix chateau d'eau
                }
                if (event.mouse.x > 930 && event.mouse.x < 1012 &&
                    event.mouse.y > 650 && event.mouse.x < 734){
                    // choix usine
                }
                //éléments à gauche
                if (event.mouse.x > 6 && event.mouse.x < 60 &&
                    event.mouse.y > 85 && event.mouse.y < 140){
                    //changer niveau de visualisation
                }
                if (event.mouse.x > 6 && event.mouse.x < 60 &&
                    event.mouse.y > 150 && event.mouse.y < 205){
                    //PAUSE
                }
                if (event.mouse.x > 6 && event.mouse.x < 60 &&
                    event.mouse.y > 215 && event.mouse.y < 270){
                    al_draw_bitmap(sauvegarde, 0, 0, 0);
                    if (event.mouse.x>223 && event.mouse.x<385 &&
                        event.mouse.y > 406 && event.mouse.y < 482){
                        // fonction sauvegarder partie
                    }
                    else (event.mouse.x>631 && event.mouse.x<802 &&
                        event.mouse.y > 406 && event.mouse.y < 482){
                        fin = true;
                    }
                    // faire une autre fonction pour ça???
                    // affichage de l'écran sauvegarder puis fermeture fenêtre
                }
                break;
            }

        }
    }
    al_destroy_display(display);
    al_destroy_event_queue(queue);
    al_destroy_bitmap(fond);
    al_destroy_bitmap (sauvegarde);
    al_destroy_timer(timer);
    al_destroy_font (police);

    queue = NULL;
    fond = NULL;
    sauvegarde = NULL;
    timer = NULL;
    police = NULL;

    return 0;
}



/*
void ecranQuitter(ALLEGRO_EVENT_QUEUE *queue){
    al_draw_bitmap(sauvegarde, 0, 0, 0);
    fin = true;
}*/