#include "affichage.h"

using namespace std;



void afficher_jeu(SDL_Surface ** p_images, int ** p_tableau1, int ** p_tableau2)
{
    SDL_FillRect(SDL_GetVideoSurface(), 0, SDL_MapRGB(SDL_GetVideoSurface()->format, 0, 0, 0));
    afficher_cases(p_images, p_tableau1);
    afficher_pions(p_images, p_tableau2);
    SDL_Flip(SDL_GetVideoSurface());
}

void afficher_cases(SDL_Surface ** p_images, int ** p_tableau)
{
    SDL_Rect place = {0};
    for(int i = 0 ; i < 10 ; i++)
    {
        for(int j = 0 ; j < 10 ; j++)
        {
            place = {j*TAILLE_CARRE,i*TAILLE_CARRE};
            SDL_BlitSurface(p_images[5+p_tableau[i][j]], NULL, SDL_GetVideoSurface(), &place);
        }
    }
}

void afficher_pions(SDL_Surface ** p_images, int ** p_tableau)
{
    SDL_Rect place = {0};
    for(int i = 0 ; i < 10 ; i++)
    {
        for(int j = 0 ; j < 10 ; j++)
        {
            if(p_tableau[i][j] != 0)
            {
                place = {j*TAILLE_CARRE,i*TAILLE_CARRE};
                SDL_BlitSurface(p_images[p_tableau[i][j]], NULL, SDL_GetVideoSurface(), &place);
            }
        }
    }
}

