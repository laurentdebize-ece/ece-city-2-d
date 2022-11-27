#include "Ecrans accueil.h"
#include "../Le Jeu/Le Jeu.h"

void ecranAccueil(ALLEGRO_DISPLAY* fenetre){
    //Affichage de l'ecran d'accueill
    srand(time(NULL));
    bool end = false;
    bool end_menu = false;
    bool end_ecran_choix = true;
    bool nouvellePartie = false;

    int x_mouse = 0;
    int y_mouse = 0;

    bool clic_mouse = false;

    // Déclarations
    ALLEGRO_DISPLAY *display = NULL;
    ALLEGRO_EVENT_QUEUE *queue = NULL;
    ALLEGRO_TIMER *timer = NULL;
    ALLEGRO_EVENT event;
    ALLEGRO_KEYBOARD_STATE keyboard_state;
    //BITMAP
    ALLEGRO_BITMAP* menu;
    ALLEGRO_BITMAP* choix;


    timer = al_create_timer(1.0/60.0);
    al_start_timer(timer);
    queue = al_create_event_queue();
    assert(queue!=NULL);

    al_register_event_source(queue, al_get_display_event_source(fenetre));
    al_register_event_source(queue, al_get_timer_event_source(timer));
    al_register_event_source(queue, al_get_mouse_event_source());
    al_register_event_source(queue, al_get_keyboard_event_source());
    al_get_keyboard_state(&keyboard_state);

    //BITMAP
    //FONDS
    menu = al_load_bitmap("../Images/Menu_jouer.png");
    choix = al_load_bitmap("../Images/Menu_choix.png");

    // Boucle d'événements
    while (!end) {

        //*******************************************************************//
        // ECRAN DE MENU
        //*******************************************************************//

        while (end_menu == false) {
            al_draw_bitmap(menu, 0, 0, 0);




            al_flip_display();
            al_wait_for_event(queue, &event);
            switch (event.type) {
                case ALLEGRO_EVENT_DISPLAY_CLOSE: {
                    end_menu = true;
                    end = true;
                    break;
                }
                case ALLEGRO_EVENT_KEY_UP: {
                    switch (event.keyboard.keycode) {
                        case ALLEGRO_KEY_ESCAPE: {
                            end_menu = true;
                            end = true;
                            break;
                        }
                    }
                    break;
                }
                case ALLEGRO_EVENT_MOUSE_BUTTON_DOWN: {
                    x_mouse = event.mouse.x;
                    y_mouse = event.mouse.y;
                    printf("clic bouton %d en %dx%d\n", event.mouse.button, event.mouse.x, event.mouse.y);
                    if (event.mouse.button & 1) {
                        clic_mouse = true;
                    } else { clic_mouse = false; }

                    if (func_bouton(clic_mouse, x_mouse, y_mouse, 112, 452, 432, 682)) {
                        nouvellePartie = true;
                        al_draw_bitmap(choix, 0, 0, 0);
                        al_flip_display();
                        end_menu = true;
                        end_ecran_choix = false;
                    }
                    else if (func_bouton(clic_mouse, x_mouse, y_mouse, 13, 51, 16, 63)) {
                        end_menu = true;
                        end = true;
                    }
                    else if (func_bouton(clic_mouse, x_mouse, y_mouse, 650, 1000, 437, 687)) {
                        nouvellePartie = false;
                        leJeu(fenetre, 2, nouvellePartie);
                        end=true;
                        end_menu = true;

                    }
                    break;
                }
                case ALLEGRO_EVENT_MOUSE_BUTTON_UP: {
                    if (event.mouse.button & 1) {
                        clic_mouse = false;
                    } else { clic_mouse = true; }
                    break;
                }
            }
        }
        //*******************************************************************//
        //ECRAN DE SELECTION DU MODE DE JEU
        //*******************************************************************//


        while (end_ecran_choix == false) {
            al_flip_display();
            al_wait_for_event(queue, &event);
            switch (event.type) {
                case ALLEGRO_EVENT_DISPLAY_CLOSE: {
                    end_ecran_choix = true;
                    end = true;
                    break;
                }
                case ALLEGRO_EVENT_KEY_UP: {
                    switch (event.keyboard.keycode) {
                        case ALLEGRO_KEY_ESCAPE: {
                            end_ecran_choix = true;
                            end = true;
                            break;
                        }
                    }
                    break;
                }

                case ALLEGRO_EVENT_MOUSE_BUTTON_DOWN: {
                    x_mouse = event.mouse.x;
                    y_mouse = event.mouse.y;
                    printf("clic bouton %d en %dx%d\n", event.mouse.button, event.mouse.x, event.mouse.y);
                    if (event.mouse.button & 1) {
                        clic_mouse = true;
                    } else { clic_mouse = false; }

                    if (func_bouton(clic_mouse, x_mouse, y_mouse, 105, 375, 448, 666)) { //mode capitaliste (rajouter une variable qui permet d'enregistrer le choix)
                        leJeu(fenetre, 2, nouvellePartie);
                        end_ecran_choix = true;
                        end=true;
                    }
                    else if (func_bouton(clic_mouse, x_mouse, y_mouse, 743, 1018, 450, 680)) { //mode communiste (rajouter une variable qui permet d'enregistrer le choix)
                        leJeu(fenetre, 1, nouvellePartie);
                        end_ecran_choix = true;
                        end=true;

                    }
                    else if (func_bouton(clic_mouse, x_mouse, y_mouse, 13, 51, 16, 63)) {   //bouton quitter
                        end_menu = true;
                        end = true;
                    }

                    break;
                }
                case ALLEGRO_EVENT_MOUSE_BUTTON_UP: {
                    if (event.mouse.button & 1) {
                        clic_mouse = false;
                    } else { clic_mouse = true; }
                    break;
                }
            }
        }
    }


    // Libérations (al_destroy...)
    al_destroy_event_queue(queue);
    al_destroy_timer(timer);

    timer = NULL;
    queue = NULL;

    al_destroy_bitmap(menu);
    al_destroy_bitmap(choix);
}

