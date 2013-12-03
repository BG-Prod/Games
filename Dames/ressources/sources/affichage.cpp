/*
    Draughts - Les Dames
    Copyright (C) 2013  BG Prod

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.

    Contact me : bgprod@outlook.com
*/

#include "affichage.h"


using namespace std;


void afficher_jeu(SDL_Surface ** p_images, Texte * p_page, int ** p_tableau1, int ** p_tableau2, Input p_in, int p_pion, Animation * p_repas)
{
    SDL_Rect place = {0,0,0,0};
    place.x = p_images[5]->w*10;
    SDL_FillRect(SDL_GetVideoSurface(), 0, SDL_MapRGB(SDL_GetVideoSurface()->format, 0, 0, 0));
    afficher_cases(p_images, p_tableau1);
    afficher_pions(p_images, p_tableau2);
    SDL_BlitSurface(p_images[7], NULL, SDL_GetVideoSurface(), &place);
    p_page->print_text();
    p_page->print_text(6,1260.0*RESIZE,470.0*RESIZE);
    p_page->print_text(7,1600.0*RESIZE,470.0*RESIZE);

    explosion(p_images, p_repas);

    if(p_pion)
    {
        place.x = p_in.mousex - p_images[p_pion]->w/2;
        place.y = p_in.mousey - p_images[p_pion]->h/2;
        SDL_BlitSurface(p_images[p_pion], NULL, SDL_GetVideoSurface(), &place);
    }

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

void explosion(SDL_Surface ** p_images, Animation * animation) /// permet d'afficher une explosion lorsque temps = 0
{
    if(animation->temps != -1)
    {
        if(!animation->temps)
        {
            animation->place.x = (animation->place.x * p_images[5]->w) + p_images[5]->w/2 - p_images[12]->w/8;
            animation->place.y = (p_images[5]->h * animation->place.y) + p_images[5]->h/2 - p_images[12]->h/10;
        }
        if(animation->temps < 20)
        {
            /// faire les calculs de l'image
            SDL_Rect place;
            place.x = (animation->temps%4) * p_images[12]->w/4;
            place.y = (animation->temps/4) * p_images[12]->h/5;
            place.w = p_images[12]->w / 4;
            place.h = p_images[12]->h / 5;
            SDL_BlitSurface(p_images[12], &place, SDL_GetVideoSurface(), &(animation->place));
            animation->temps = animation->temps + 1;
        }
        else
        {
            animation->temps = -1;
        }
    }
}



