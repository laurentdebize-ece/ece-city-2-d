cmake_minimum_required(VERSION 3.23)
project(ECE_City C)

set(CMAKE_C_STANDARD 99)

add_executable(ECE_City main.c Initialisation/Initialisation.c Initialisation/Initialisation.h "Le Jeu/Le Jeu.c" "Le Jeu/Le Jeu.h" "Ecrans accueil/Ecrans accueil.c" "Ecrans accueil/Ecrans accueil.h" Fonctions/Fonctions.c Fonctions/Fonctions.h Carte/Carte.c Carte/Carte.h)

target_link_libraries(ECE_City -lmingw32 -lallegro-5.0.10-monolith-md-debug)