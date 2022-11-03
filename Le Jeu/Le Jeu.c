#include "Le Jeu.h"

#include <stdio.h>

#define LARGEUR 1024
#define HAUTEUR 768

/* Déclarations
 * Initialisations et installations
 * Création
 * 1er affichage
 * Boucle d'événements
 * Libération
*/

int jeu () {

    // Déclarations
    ALLEGRO_DISPLAY *display = NULL;
    ALLEGRO_BITMAP *fond = NULL;
    ALLEGRO_BITMAP *regles = NULL;
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
    fond = al_load_bitmap("../imagefont/fondppal.jpg");

    //Création
    display = al_create_display(LARGEUR, HAUTEUR);
    //assert(al_init_ttf_addon());

    assert(display != NULL);
    al_set_window_position(display, 200, 15);
    al_clear_to_color(al_map_rgb(200, 206, 200));
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
        }
    }
    al_destroy_display(display);
    al_destroy_event_queue(queue);
    al_destroy_bitmap(fond);
    al_destroy_timer(timer);
    return 0;
}