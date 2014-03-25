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

SoUApp::SoUApp() : Application()
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
    objects.push_back(new Map());
    objects.push_back(new Vaisseau());
    objects.push_back(new Vaisseau());

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

        objects[1]->bot();
        objects[0]->update(in);

        /// print l'image à l'écran
        draw();
    }
    /// end main loop
}

void SoUApp::intro()    /// affichage du logo
{
    int clign = 0;

    while(clign<256)
    {
        SDL_FillRect(SDL_GetVideoSurface(), 0, SDL_MapRGB(SDL_GetVideoSurface()->format, 0, 0, 0));
        images[0]->setAlpha(clign);
        images[0]->print(SDL_GetVideoSurface()->w/2 - images[0]->width()/2,SDL_GetVideoSurface()->h/2 - images[0]->height()/2);
        clign+=10;
        fps();
        SDL_Flip(SDL_GetVideoSurface());
    }
}

void SoUApp::draw()
{
    for(unsigned int i = 0 ; i < objects.size() ; i++)
    {
        DisplayDatas tmp = objects[i]->print();

        int numImage = whatImage(tmp.type, tmp.etat);

        if(numImage >= 0)
        {
            images[numImage]->print(screen->buffer(), tmp.coor, cam->place());
        }
    }
    screen->display();
}

int SoUApp::whatImage(int a, int b)
{
    int retour = -1;
    if(a==0)
    {
        retour = 7;
    }
    if(a==1)
    {
        if(b==BAS)
        {
            retour = 2;
        }
        else if(b==HAUT)
        {
            retour = 3;
        }
        else if(b==DROITE)
        {
            retour = 4;
        }
        else if(b==GAUCHE)
        {
            retour = 5;
        }
    }

    return retour;
}

