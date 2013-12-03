#include "jeu.h"

using namespace std;


void game()
{
// initialisation données du jeu



// loop of the game
    Input in;
    memset(&in,0,sizeof(in));
    int tempsPrecedent = 0, tempsActuel = 0;

    while(!in.key[SDLK_ESCAPE] && !in.quit)
    {
    // events
        updateEvents(&in);

    // FPS
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


    // mécanique du jeu
    jouer_jeu();
    // affichage du jeu
    afficher_jeu();
    }

// fermeture du jeu

}

void jouer_jeu()
{

}

