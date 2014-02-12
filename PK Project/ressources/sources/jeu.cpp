/*
    PK Project
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

#include "jeu.h"

using namespace std;


Jeu::Jeu(SDL_Surface ** p_images)
{
    m_in = new Input;
    m_images = p_images;
    m_tempsPrecedent = 0, m_tempsActuel = 0, m_screen_refresh = SCREEN_REFRESH;
    m_zone = new Zone[2];
    m_zone[0].init(p_images, m_in);
    m_zone[1].init(p_images, m_in);
}

Jeu::~Jeu()
{
    delete m_in;
    delete [] m_zone;
}

void Jeu::game()    /// boucle principale du jeu
{
    while(!m_in->get_touche(SDLK_ESCAPE) && !m_in->get_exit())
    {
        /// met à jour les evenements d'entree
        m_in->update();
        /// régule le fps
        timer();
        /// resize taille écran
        resizeScreen();

        /// mécanique du jeu
        mecanique();
        /// affichage du jeu
        affichage();
    }
}

void Jeu::mecanique()
{
    IA();
}

void Jeu::IA()
{

}

void Jeu::affichage()
{
    SDL_Rect place;
    SDL_FillRect(SDL_GetVideoSurface(), 0, SDL_MapRGB(SDL_GetVideoSurface()->format, 0, 100, 0));
    place = {0,0,0,0};
    SDL_BlitSurface(m_images[3], NULL, SDL_GetVideoSurface(), &place);
    m_zone[1].afficher();


    Texte blabla;
    blabla.print("Infos joueur", "arial", 60*RESIZE, {250,250,250}, 1540*RESIZE,50*RESIZE);



    SDL_Flip(SDL_GetVideoSurface());
}

void Jeu::explosion(SDL_Surface ** p_images, Animation * animation)
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

void Jeu::timer()
{
    fps(&m_tempsPrecedent, &m_tempsActuel, m_screen_refresh);
}

void Jeu::resizeScreen()
{
    resize_screen(*m_in);
}


