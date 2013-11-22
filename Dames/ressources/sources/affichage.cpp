/*
    Draughts - Les Dames
    Copyright (C) 2013  Garçon Benoît

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

    Contact me : benoit.garconbesson@gmail.com
*/

#include "affichage.h"

using namespace std;



void afficher_jeu(SDL_Surface ** p_images, Texte * p_page, int ** p_tableau1, int ** p_tableau2)
{
    SDL_Rect place = {0,0,0,0};
    place.x = p_images[5]->w*10;
    SDL_FillRect(SDL_GetVideoSurface(), 0, SDL_MapRGB(SDL_GetVideoSurface()->format, 0, 0, 0));
    afficher_cases(p_images, p_tableau1);
    afficher_pions(p_images, p_tableau2);
    SDL_BlitSurface(p_images[7], NULL, SDL_GetVideoSurface(), &place);
    p_page->print_text();
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

