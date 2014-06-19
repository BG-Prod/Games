/*
    Trace
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

#include "Trace.h"

Trace::Trace() : Application()
{
    SDL_WM_SetCaption("Trace", NULL);
    screen->resize(660,480);
}

Trace::~Trace()
{

}

void Trace::intro()
{
    long base = SDL_GetTicks();
/**
    FMOD_System_PlaySound(system, FMOD_CHANNEL_FREE, musiques[2], 0, NULL);

    while(SDL_GetTicks()-base < 3100)
    {
        SDL_FillRect(SDL_GetVideoSurface(), 0, SDL_MapRGBA(SDL_GetVideoSurface()->format, 255, 255, 255, 0));
        images[0]->print(SDL_GetVideoSurface()->w/2 - images[0]->width()/2,SDL_GetVideoSurface()->h/2 - images[0]->height()/2);
        fps();
        SDL_Flip(SDL_GetVideoSurface());
    }

    base = SDL_GetTicks();
**/
    FMOD_System_PlaySound(system, FMOD_CHANNEL_FREE, musiques[0], 0, NULL);

    while(SDL_GetTicks()-base < 3500)
    {
        SDL_FillRect(SDL_GetVideoSurface(), 0, SDL_MapRGBA(SDL_GetVideoSurface()->format, 0, 0, 0, 0));
        images[1]->print(SDL_GetVideoSurface()->w/2 - images[1]->width()/2,SDL_GetVideoSurface()->h/2 - images[1]->height()/2);
        fps();
        SDL_Flip(SDL_GetVideoSurface());
    }/**
    FMOD_System_PlaySound(system, FMOD_CHANNEL_FREE, musiques[1], 0, NULL);
    while(SDL_GetTicks()-base < 1100)
    {
        SDL_FillRect(SDL_GetVideoSurface(), 0, SDL_MapRGBA(SDL_GetVideoSurface()->format, 0, 0, 0, 0));
        images[1]->print(SDL_GetVideoSurface()->w/2 - images[1]->width()/2,SDL_GetVideoSurface()->h/2 - images[1]->height()/2);
        fps();
        SDL_Flip(SDL_GetVideoSurface());
    }*/
}

void Trace::init()
{
    intro();
    /// creation map
    objects.push_back(new Map(660, 480, 11));
    /// terrain
    images.push_back(new Image(660,480,0,0,0,0));
    /**for(int i = 0; i < images[7]->width() ; i++)
    {
        for(int j = 0; j < images[7]->height() ; j++)
        {
            if(images[7]->getPixel(i,j)==0)
            {
                images[7]->setPixel(i,j,0xFFFFFFFF);
            }
        }
    }**/
    for(int i = -6 ; i < 660 ; i=i+6)
    {
        images[6]->print(images[7], Coordonnees(i,0,12,12));
        images[6]->print(images[7], Coordonnees(i,468,12,12));
        if(i<480)
        {
            images[6]->print(images[7], Coordonnees(0,i,12,12));
            images[6]->print(images[7], Coordonnees(648,i,12,12));
        }
    }
    /// creation des joueurs
    for(int i = 0 ; i < 4 ; i++)
    {
        int x = random(0, 659);
        x -= x%12;
        int y = random(0, 479);
        y -= y%12;
        objects.push_back(new Player(i, x, y, objects[0]));
    }
    screen->setClearing(false);
}

void Trace::app()
{
    /// sorties
    for(unsigned int i = 0 ; i < objects.size() ; i++)
    {
        int changeOfDir = -1;
        if(i!=0){changeOfDir = objects[i]->isOut(objects[0]);}
        if(i!=0 && (-1 < changeOfDir))
        {
            objects[i]->setOutOf(changeOfDir);
        }
    }
/*
    /// ia
    for(int i = 0 ; i < objects.size() ; i++)
    {
        objects[i]->update(in);
    }
*/
    /// moves
    for(int i = 0 ; i < objects.size() ; i++)
    {
        objects[i]->bot();
    }
}

int Trace::whatImage(int a, int b)
{
    int retour = -1;

    if(a==PLAYA1)
    {
        retour = 2;
    }
    else if(a==PLAYA2)
    {
        retour = 3;
    }
    else if(a==PLAYA3)
    {
        retour = 4;
    }
    else if(a==PLAYA4)
    {
        retour = 5;
    }
    else if(a==11)
    {
        retour = 7;
    }

    return retour;
}

