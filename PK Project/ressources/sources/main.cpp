#include <cstdlib>
#include <stdlib.h>
#include <stdio.h>
#include <fstream>
#include <string>
#include <sstream>
#include <iostream>
#include <windows.h>
#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_image.h>
#include <FMOD/fmod.h>



#include "utile.h"
#include "affichage.h"
#include "jeu.h"



int main ( int argc, char** argv )
{
// initialisation son & image
    // initialisation FMOD
    FMOD_SYSTEM * system;
    FMOD_System_Create(&system);
    // initialisation image & son
    initialisation(system);


// déclaration et chargements des ressources
    // images
    SDL_Surface** images = NULL;
    images = (SDL_Surface **) malloc (sizeof(SDL_Surface*)*NOMBRE_IMAGE);
    load_images(images);
    // sons
    FMOD_SOUND ** musiques = NULL;
    musiques = (FMOD_SOUND **) malloc (sizeof(FMOD_SOUND*)*NOMBRE_MUSIQUE);
    load_musiques(system, musiques);
    // polices
    TTF_Font ** polices = NULL;
    polices = (TTF_Font **) malloc(sizeof(TTF_Font*) * NOMBRE_POLICE);
    load_polices(polices);
    // couleurs
    SDL_Color blanc = {255,255,255};
    SDL_Color gris_clair = {200,200,200};
    SDL_Color gris_fonce = {50,50,50};
    SDL_Color noir = {0,0,0};


// Icone
    SDL_WM_SetIcon(images[0], NULL);

// create a new window
    SDL_Surface* screen = SDL_SetVideoMode(LARGEUR_ECRAN, HAUTEUR_ECRAN, 32, SDL_HWSURFACE|SDL_DOUBLEBUF|SDL_RESIZABLE|SDL_FULLSCREEN);
    if ( !screen )
    {
        printf("Unable to set 640x480 video: %s\n", SDL_GetError());
        return 1;
    }

// titre
    SDL_WM_SetCaption("Game", NULL);


// program main loop
    Input in;
    memset(&in,0,sizeof(in));
    int tempsPrecedent = 0, tempsActuel = 0;

    int * menu = new int;
    *menu = -1;

    SDL_Rect place = {LARGEUR_ECRAN/2 - images[0]->w/2,HAUTEUR_ECRAN/2 - images[0]->h/2,0,0};

//on joue la musique de fond
    FMOD_System_PlaySound(system, FMOD_CHANNEL_FREE, musiques[0], 0, NULL);

    while(!in.key[SDLK_ESCAPE] && !in.quit)         // boucle principale
    {
        // mise à jour des events
        updateEvents(&in);


        // gestion du frame
        tempsActuel = SDL_GetTicks();

        if(tempsActuel - tempsPrecedent >= SCREEN_REFRESH)
        {
            tempsPrecedent = tempsActuel;
        }
        else if (tempsActuel - tempsPrecedent < SCREEN_REFRESH)
        {
            SDL_Delay(tempsActuel - tempsPrecedent);
            tempsPrecedent = tempsActuel;
        }



        // resize taille écran
        if(in.key[SDLK_F1])
        {
            SDL_SetVideoMode(LARGEUR_ECRAN, HAUTEUR_ECRAN, 32, SDL_HWSURFACE|SDL_DOUBLEBUF|SDL_RESIZABLE|SDL_FULLSCREEN);
        }
        if(in.key[SDLK_F2])
        {
            SDL_SetVideoMode(LARGEUR_ECRAN, HAUTEUR_ECRAN, 32, SDL_HWSURFACE|SDL_DOUBLEBUF);
        }





        if(*menu == 1 || in.key[SDLK_RETURN]) // jouer
        {
            game();
        }

        if(*menu == -9) // quitter le jeu
        {
            in.quit = 1;
        }

        if(*menu == -1)
        {
            SDL_BlitSurface(images[0], NULL, screen, &place);
            DEBUG "image";
        }

        SDL_Flip(screen);
    }// end main loop


// nettoyage
    // free pointeurs
    delete menu;
    // free loaded bitmap and created surface
    SDL_FreeSurface(screen);
    free_images(images);
    free_polices(polices);
    // libération des sons
    free_musiques(musiques);
    // fermeture propre de ce qui est ouvert dans initialisation()
    fermeture(system);


// all is well ;)
    printf("Exited cleanly\n");
    return 0;
}



/// REMARQUES

// 28/09/2013 : création du jeu



