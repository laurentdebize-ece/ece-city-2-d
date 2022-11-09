#include <stdio.h>
#include "Fonctions/Fonctions.h"
#include "Ecrans accueil/Ecrans accueil.h"
#include "Le Jeu/Le Jeu.h"

#include "Carte/Carte.h"
#include "Initialisation/Initialisation.h"



int main() {

    srand(time(NULL));

    assert(al_init());
    assert(al_install_mouse());
    assert(al_install_keyboard());
    assert(al_init_image_addon());
    al_init_image_addon();
    assert(al_init_primitives_addon());
    al_init_font_addon();
    assert(al_init_ttf_addon());
    al_init_ttf_addon();

    ALLEGRO_DISPLAY *fenetre = NULL;


    fenetre = al_create_display(LARGEUR_FENETRE, HAUTEUR_FENETRE);
    al_set_window_position(fenetre, 20, 20);
    al_set_window_title(fenetre, "ECE City");



    //ecranAccueil(fenetre);
    leJeu(fenetre);

    //**********************************************//
    /*Case** matrice = (Case**) calloc(NB_LIGNES, sizeof(Case));
    for(int i = 0; i < NB_COLONNES; i++) {
        matrice[i] = (Case*) calloc(NB_COLONNES, sizeof(Case));
    }

    initCases(matrice);

    lireFichierCarte(matrice);
*/
    //***********************************************//

    al_destroy_display(fenetre);
    fenetre = NULL;

    return 0;
}
