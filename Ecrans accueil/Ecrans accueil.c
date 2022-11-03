#include "Ecrans accueil.h"


void ecranAccueil(){
    //Affichage de l'ecran d'accueil
    srand(time(NULL));
    bool end = false;
    bool end_menu = false;
    bool end_ecran_choix = true;
    bool end_credits = true;

    int leX = 0;
    int leY = 0;
    int leX2 = 0;
    int leY2 = 0;
    int leX3 = 0;
    int leY3 = 0;
    int leX4 = 0;
    int leY4 = 0;

    int x_mouse = 0;
    int y_mouse = 0;
    int h = 0;
    int temps = 0;

    bool clic_mouse = false;

    // Déclarations
    ALLEGRO_DISPLAY *display = NULL;
    ALLEGRO_EVENT_QUEUE *queue = NULL;
    ALLEGRO_TIMER *timer = NULL;
    ALLEGRO_EVENT event;
    ALLEGRO_KEYBOARD_STATE keyboard_state;
    //BITMAP
    ALLEGRO_BITMAP* menu;
    //ALLEGRO_BITMAP* map;
    ALLEGRO_BITMAP* choix;
    ALLEGRO_BITMAP *credits;

    // Initialisations (al_init/al_install...)
    assert(al_init());
    assert(al_install_mouse());
    assert(al_install_keyboard());
    assert(al_init_primitives_addon());
    al_init_image_addon();
    al_init_font_addon();
    al_init_ttf_addon();


    // Créations (al_create...)
    display = al_create_display(LARGEUR, HAUTEUR);
    al_set_window_position(display, 0, 0);
    al_set_window_title(display, "Projet ECE-City");
    assert(display != NULL);
    timer = al_create_timer(1.0/60.0);
    al_start_timer(timer);
    queue = al_create_event_queue();
    assert(queue!=NULL);

    al_register_event_source(queue, al_get_display_event_source(display));
    al_register_event_source(queue, al_get_timer_event_source(timer));
    al_register_event_source(queue, al_get_mouse_event_source());
    al_register_event_source(queue, al_get_keyboard_event_source());
    al_get_keyboard_state(&keyboard_state);

    printf("a");
    //BITMAP
    //FONDS
    menu = al_load_bitmap("bitmap/Menu boutons test.png");
    printf("b");

    choix = al_load_bitmap("bitmap/Menu.png");
    printf("c");

    credits = al_load_bitmap("bitmap/Fond menu.jpg");
    printf("d");


    // Boucle d'événements
    while (!end) {

        //*******************************************************************//
        // ECRAN DE MENU
        //*******************************************************************//


        while (end_menu == false) {
            al_draw_bitmap(menu, 0, 0, 0);
            printf("a");



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

                    if (func_bouton(clic_mouse, x_mouse, y_mouse, 481, 670, 488, 540)) { //commencer
                        al_draw_bitmap(choix, 0, 0, 0);
                        al_flip_display();
                        end_menu = true;
                        end_ecran_choix = false;
                    } else if (func_bouton(clic_mouse, x_mouse, y_mouse, 426, 725, 317, 360)) { //crédits
                        al_draw_bitmap(credits, 0, 0, 0);
                        al_flip_display();
                        end_menu = true;
                        end_credits = false;
                    } else if (func_bouton(clic_mouse, x_mouse, y_mouse, 426, 725, 368, 414)) { //quitter
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
                    al_draw_bitmap(choix, 0, 0, 0);

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


        // Libérations (al_destroy...)
        al_destroy_display(display);
        al_destroy_event_queue(queue);
        al_destroy_timer(timer);

        al_destroy_bitmap(menu);
        //al_destroy_bitmap(map);
        al_destroy_bitmap(choix);

    }
}
