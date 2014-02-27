#include <SDL.h>
#include <cstdlib>
#include <stdlib.h>
#include <stdio.h>
#include <FMOD/fmod.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <windows.h>
#include <math.h>
#include <string.h>
#include <SDL_getenv.h>


#include "Constantes.h"
#include "Personnage.h"
#include "Etre.h"
#include "Vaisseau.h"
#include "BC304.h"
#include "Hatak.h"
#include "Utile.h"
#include "Generator.h"
#include "Univers.h"
#include "Monde.h"
#include "Map.h"


#include <iostream>


using namespace std;


int main ( int argc, char** argv )
{
/// initialisation son & image
    /// initialisation FMOD
    FMOD_SYSTEM * system;
    FMOD_System_Create(&system);
    /// initialisation image & son
    initialisation(system);


/// déclaration et chargements des ressources
    /// create a new window
    putenv("SDL_VIDEO_WINDOW_POS=center"); /// pour centrer la fenêtre
    SDL_Surface* screen = SDL_SetVideoMode(LARGEUR_ECRAN, HAUTEUR_ECRAN, 32, SDL_HWSURFACE|SDL_DOUBLEBUF|SDL_RESIZABLE/*|SDL_FULLSCREEN*/);


    if ( !screen )
    {
        printf("Unable to set 640x480 video: %s\n", SDL_GetError());
        return 1;
    }
    /// images
    SDL_Surface** images = NULL;
    images = (SDL_Surface **) malloc (sizeof(SDL_Surface*) * NOMBRE_IMAGE);
    load_images(images);
    /// sons
    FMOD_SOUND ** musiques = NULL;
    musiques = (FMOD_SOUND **) malloc (sizeof(FMOD_SOUND*) * NOMBRE_MUSIQUE);
    load_musiques(system, musiques);
    /// polices
    TTF_Font ** polices = NULL;
    polices = (TTF_Font **) malloc(sizeof(TTF_Font*) * NOMBRE_POLICE);
    load_polices(polices);
    /// couleurs
    SDL_Color blanc = {255,255,255};
    SDL_Color gris_clair = {200,200,200};
    SDL_Color gris_fonce = {50,50,50};
    SDL_Color noir = {0,0,0};


/// Icone
    SDL_WM_SetIcon(images[0], NULL);

/// titre
    SDL_WM_SetCaption("Secrets of Universe", NULL);



/// fonction qui lance le jeu
    jeu(images);



/// nettoyage
    /// free pointeurs

    /// free loaded bitmap and created surface
    SDL_FreeSurface(screen);
    free_images(images);
    free_polices(polices);
    /// libération des sons
    free_musiques(musiques);
    /// fermeture propre de ce qui est ouvert dans initialisation()
    fermeture(system);


/// all is well ;)
    cout << "Exited cleanly\n";
    return 0;
}


// graves problemes de mémoires avec les "delete this" mis dans map et monde play car crash au lieu de supprimer
// peut etre a cause du fait que j'essai de supprimer des objets qui ont déjà disparu
// en effet suppression des listes dans destructeur de monde et map mais aussi par les objets eux-mêmes

// la solution au probleme precedent c'est peut etre creer  mes propres new et delete comme dans "C++ pour les nuls"

// retrouver le putain d'endroit d'où sortent les munitions !!!!

// revoir barreVie des vaisseaux

// tout le systeme de combat n'est adapté qu''à nos deux joueurs

// faire attribuer m_joueur par map permettrai de faire plus de vaisseaux et de les individualiser

// changer la zone de non effet temporel des tirs en zone physique


