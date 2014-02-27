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
    SDL_Rect place = {LARGEUR_ECRAN/2 - images[0]->w/2,HAUTEUR_ECRAN/2 - images[0]->h/2,0,0};

/// on joue la musique de fond
    FMOD_System_PlaySound(system, FMOD_CHANNEL_FREE, musiques[0], 0, NULL);

/// affichage du logo
    int clign = 0;
    while(clign<256)
    {
        SDL_FillRect(SDL_GetVideoSurface(), 0, SDL_MapRGB(SDL_GetVideoSurface()->format, 0, 0, 0));
        place = {LARGEUR_ECRAN/2 - images[0]->w/2,HAUTEUR_ECRAN/2 - images[0]->h/2,0,0};
        SDL_SetAlpha(images[0], SDL_SRCALPHA, clign);
        SDL_BlitSurface(images[0], NULL, SDL_GetVideoSurface(), &place);
        clign++;
        SDL_Flip(SDL_GetVideoSurface());
    }

    while(clign>=0)
    {
        SDL_FillRect(SDL_GetVideoSurface(), 0, SDL_MapRGB(SDL_GetVideoSurface()->format, 0, 0, 0));
        place = {LARGEUR_ECRAN/2 - images[0]->w/2,HAUTEUR_ECRAN/2 - images[0]->h/2,0,0};
        SDL_SetAlpha(images[0], SDL_SRCALPHA, clign);
        SDL_BlitSurface(images[0], NULL, SDL_GetVideoSurface(), &place);
        clign--;
        SDL_Flip(SDL_GetVideoSurface());
    }

    place = {LARGEUR_ECRAN/2 - images[1]->w/2,HAUTEUR_ECRAN/2 - images[1]->h/2,0,0};

    Vaisseau * asgo = new Vaisseau();
    asgo->init(images);

    while(!in->get_touche(SDLK_ESCAPE) && !in->get_exit())  /// boucle principale
    {
        SDL_FillRect(SDL_GetVideoSurface(), 0, SDL_MapRGB(SDL_GetVideoSurface()->format, 0, 0, 0));

        /// mise à jour des events
        in->update();

        /// gestion du frame
        fps();

        /// resize taille écran
        resize_screen();

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
        else if(in->get_touche(SDLK_KP_PLUS))
        {
            asgo->resize(120);
        }
        else if(in->get_touche(SDLK_KP_MINUS))
        {
            asgo->resize(80);
        }
        else if(in->get_touche(SDLK_SPACE))
        {
            asgo->destroy();
        }

        asgo->print();

        place = {LARGEUR_ECRAN/2 - images[1]->w/2,40*RESIZE,0,0};
        SDL_BlitSurface(images[1], NULL, SDL_GetVideoSurface(), &place);

        SDL_Flip(SDL_GetVideoSurface());
    }/// end main loop

    delete asgo;
}

