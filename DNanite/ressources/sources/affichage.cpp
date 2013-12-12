/*
    DNanite
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



void afficher_jeu()
{

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

