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

void SoUApp::init()
{
    /// on joue la musique de fond
    FMOD_System_PlaySound(system, FMOD_CHANNEL_FREE, musiques[0], 0, NULL);

    /// affiche une intro BG Prod
    intro();

    for(int i = 0 ; i < images[7]->width() ; i++)
    {
        for(int j = 0 ; j < images[7]->height() ; j++)
        {
            images[7]->setPixel(i,j,((images[7]->getPixel(i,j)) & 0xFF1100BB));
        }
    }

    /// génération des étoiles
    for(int i = 0 ; i < 500 ; i++)
    {
        images[7]->setPixel(random(0,images[7]->width()), random(0,images[7]->height()), color(random(200,255),random(200,255),random(180,200)));
    }

    /// création des vaisseaux
    objects.push_back(new Map());
    objects.push_back(new Vaisseau(0,0));
    for(int i = 0 ; i < 10 ; i++)
    {
        objects.push_back(new Vaisseau(STARSHIP2, random(0,(int)(objects[0]->getPosition()).w()) , random(0,(int)(objects[0]->getPosition()).h())) );
    }

    /// mise en place de l'interface utilisateur
    interfaces.push_back(new Interface(BOARD1));
    interfaces.push_back(new Button(BUTTON1, Coordonnees(50,950,128,64), "FIRE"));

}

void SoUApp::app()
{
    /// resize taille écran
    if(in->get_touche(SDLK_F1))
    {
        screen->resize();
    }
    /// bouger la caméra
    if(in->get_touche(SDLK_UP))
    {
        cam->cameraUp();
    }
    if(in->get_touche(SDLK_DOWN))
    {
        cam->cameraDown();
    }
    if(in->get_touche(SDLK_LEFT))
    {
        cam->cameraLeft();
    }
    if(in->get_touche(SDLK_RIGHT))
    {
        cam->cameraRight();
    }
    cam->keepIn(objects[0]);

    /// sont-ils morts ?
    for(unsigned int i = 0 ; i < objects.size() ; i++)
    {
        if(!objects[i]->isAlive())
        {
            delete objects[i];
            objects.erase(objects.begin()+i);
        }
    }
    /// objets sur les bords ?
    /// collision objets ?
    for(unsigned int i = 0 ; i < objects.size() ; i++)
    {
        int changeOfDir = -1;
        if(i!=0){changeOfDir = objects[i]->isOut(objects[0]);}
        if(i!=0 && (-1 < changeOfDir))
        {
            objects[i]->setOutOf(changeOfDir);
        }
        for(unsigned int j = 1 ; j < objects.size() ; j++)
        {
            if(i!=j)
            {
                objects[i]->collision(objects[j]);
            }
        }
    }
    /// màj des objets
    for(unsigned int i = 2 ; i < objects.size() ; i++)
    {
        objects[i]->bot();
    }
    /// màj des interfaces
    for(unsigned int i = 0 ; i < interfaces.size() ; i++)
    {
        interfaces[i]->update(in);
    }
    objects[1]->update(in);
}

void SoUApp::intro()    /// affichage du logo
{
    int clign = 0;

    while(clign<256)
    {
        SDL_FillRect(SDL_GetVideoSurface(), 0, SDL_MapRGBA(SDL_GetVideoSurface()->format, 0, 0, 0, 0));
        images[0]->setAlpha(clign);
        images[0]->print(SDL_GetVideoSurface()->w/2 - images[0]->width()/2,SDL_GetVideoSurface()->h/2 - images[0]->height()/2);
        clign+=10;
        fps();
        SDL_Flip(SDL_GetVideoSurface());
    }

    while(clign<512)
    {
        SDL_FillRect(SDL_GetVideoSurface(), 0, SDL_MapRGBA(SDL_GetVideoSurface()->format, 0, 0, 0, 0));
        images[1]->setAlpha(clign);
        images[1]->print(SDL_GetVideoSurface()->w/2 - images[1]->width()/2,SDL_GetVideoSurface()->h/2 - images[1]->height()/2);
        clign+=10;
        fps();
        SDL_Flip(SDL_GetVideoSurface());
    }
}

int SoUApp::whatImage(int a, int b)
{
    int retour = -1;
    if(a==SPACE_MAP_1)
    {
        retour = 7;
    }
    if(a==STARSHIP1)
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
    if(a==STARSHIP2)
    {
        if(b==BAS)
        {
            retour = 11;
        }
        else if(b==HAUT)
        {
            retour = 12;
        }
        else if(b==DROITE)
        {
            retour = 13;
        }
        else if(b==GAUCHE)
        {
            retour = 14;
        }
    }
    if(a==BOARD1)
    {
        retour = 8;
    }
    if(a==SHOT1)
    {
        retour = 6;
    }
    if(a==BUTTON1)
    {
        if(b==ON)
        {
            retour = 10;
        }
        else if(b==OFF)
        {
            retour = 9;
        }
    }

    return retour;
}

