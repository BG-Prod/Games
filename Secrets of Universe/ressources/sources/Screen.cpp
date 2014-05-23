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

#include "Screen.h"

using namespace std;

Screen::Screen()
{
    /// create a new window
    putenv("SDL_VIDEO_WINDOW_POS=center"); /// pour centrer la fenêtre
    ecran = SDL_SetVideoMode(LARGEUR_ECRAN, HAUTEUR_ECRAN, 32, SDL_HWSURFACE|SDL_DOUBLEBUF|SDL_RESIZABLE|SDL_FULLSCREEN);
    if ( !ecran )
    {
        printf("Unable to set personalized size video: %s\n", SDL_GetError());
        ecran = SDL_SetVideoMode(640, 480, 32, SDL_HWSURFACE|SDL_DOUBLEBUF|SDL_RESIZABLE);
    }

    videoBuffer = new Image(LARGEUR_ECRAN,HAUTEUR_ECRAN,0,0,0);
}

Screen::Screen(int w, int h)
{
    /// create a new window
    putenv("SDL_VIDEO_WINDOW_POS=center"); /// pour centrer la fenêtre
    ecran = SDL_SetVideoMode(w, h, 32, SDL_HWSURFACE|SDL_DOUBLEBUF|SDL_RESIZABLE);


    videoBuffer = new Image(w,h,0,0,0);
}

Screen::~Screen()
{
    delete videoBuffer;
    SDL_FreeSurface(ecran);
}

void Screen::resize()
{
    if(ecran->flags & SDL_FULLSCREEN)
    {
        windowed();
    }
    else
    {
        fullScreen();
    }
}

void Screen::fullScreen()
{
    SDL_SetVideoMode(LARGEUR_ECRAN, HAUTEUR_ECRAN, 32, SDL_HWSURFACE|SDL_DOUBLEBUF|SDL_RESIZABLE|SDL_FULLSCREEN);
}

void Screen::windowed()
{
    SDL_SetVideoMode(LARGEUR_ECRAN, HAUTEUR_ECRAN, 32, SDL_HWSURFACE|SDL_DOUBLEBUF|SDL_RESIZABLE);
}

int Screen::size_of_window(int p_hauteur_ecran)
{
    return 10*(p_hauteur_ecran/10);
}

void Screen::display()
{
    videoBuffer->print();
    SDL_Flip(SDL_GetVideoSurface());
    videoBuffer->clear();
}

Image * Screen::buffer()
{
    return videoBuffer;
}

