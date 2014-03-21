/*
    Secrets of Universe
    Copyright (C) 2014  BG Prod

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

#include "SoUApp.h"

using namespace std;

SoUApp::SoUApp()
{
    SDL_WM_SetCaption("Secrets of Universe", NULL);
}

SoUApp::~SoUApp()
{
    //dtor
}

void SoUApp::app()
{
    /// on joue la musique de fond
    FMOD_System_PlaySound(system, FMOD_CHANNEL_FREE, musiques[0], 0, NULL);

    /// affiche une intro BG Prod
    intro();

    /// création des vaisseaux
    Vaisseau * asgo = new Vaisseau();
    asgo->init();

    Vaisseau * evil = new Vaisseau();
    evil->init();

    /// boucle principale
    while(!in->get_touche(SDLK_ESCAPE) && !in->get_exit())
    {
        SDL_FillRect(SDL_GetVideoSurface(), 0, SDL_MapRGB(SDL_GetVideoSurface()->format, 0, 0, 0)); /// ecran noir

        /// collage du repère
        SDL_Rect place = {SDL_GetVideoSurface()->w/2 - images[1]->width()/2,SDL_GetVideoSurface()->h/2 - images[1]->height()/2,0,0};
        place = {SDL_GetVideoSurface()->w/2 - images[1]->width()/2,40*RESIZE,0,0};
        images[1]->print(place.x,place.y);

        /// mise à jour des events
        in->update();

        /// gestion du frame
        fps();

        /// resize taille écran
        if(in->get_touche(SDLK_F1))
        {
            screen->resize();
        }

        evil->bot();

        if(in->get_touche(SDLK_UP))
        {
            asgo->move(HAUT);
        }
        else if(in->get_touche(SDLK_DOWN))
        {
            asgo->move(BAS);
        }
        else if(in->get_touche(SDLK_LEFT))
        {
            asgo->move(GAUCHE);
        }
        else if(in->get_touche(SDLK_RIGHT))
        {
            asgo->move(DROITE);
        }
        else if(in->get_touche(SDLK_SPACE))
        {
            asgo->destroy();
            in->set_touche(SDLK_SPACE,0);
        }
        else if(in->get_touche(SDLK_RETURN))
        {
            asgo->shoot();
            in->set_touche(SDLK_SPACE,0);
        }

        asgo->update();

        /// print fond d'écran
        asgo->print();
        evil->print();

        screen->display();
    }
    /// end main loop

    delete asgo;
}

void SoUApp::intro()    /// affichage du logo
{
    SDL_Rect place = {SDL_GetVideoSurface()->w/2 - images[0]->width()/2,SDL_GetVideoSurface()->h/2 - images[0]->height()/2,0,0};

    int clign = 0;

    while(clign<256)
    {
        fps();
        SDL_FillRect(SDL_GetVideoSurface(), 0, SDL_MapRGB(SDL_GetVideoSurface()->format, 0, 0, 0));
        images[0]->setAlpha(clign);
        images[0]->print(SDL_GetVideoSurface()->w/2 - images[0]->width()/2,SDL_GetVideoSurface()->h/2 - images[0]->height()/2);
        clign+=10;
        SDL_Flip(SDL_GetVideoSurface());
    }
}
