#include <stdio.h>
#include "Fonctions/Fonctions.h"
#include "Ecrans accueil/Ecrans accueil.h"

#include "Initialisation/Initialisation.h"
#include "Carte/Carte.h"

int main() {

    srand(time(NULL));

    assert(al_init());
    assert(al_install_mouse());
    assert(al_install_keyboard());
    assert(al_init_image_addon());
    assert(al_init_primitives_addon());
    al_init_font_addon();
    assert(al_init_ttf_addon());

    ALLEGRO_DISPLAY *fenetre = NULL;


    fenetre = al_create_display(LARGEUR_FENETRE, HAUTEUR_FENETRE);
    al_set_window_title(fenetre, "ECE City");


    //ecranAccueil(fenetre);






    al_destroy_display(fenetre);
    fenetre = NULL;

    return 0;
}
