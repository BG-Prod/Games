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

#ifndef IMAGE_H
#define IMAGE_H

#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_image.h>
#include <SDL_rotozoom.h>
#include <SDL_getenv.h>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

class Image
{
    public:
        Image();    /// image NULL par défaut
        Image(std::string link);    /// image à partir d'un lien
        Image(int width, int height, Uint8 r, Uint8 g, Uint8 b);
        Image(int width, int height, Uint8 r, Uint8 g, Uint8 b, Uint8 a);
        virtual ~Image();           /// destructeur

        void print();               /// affichage par défaut
        void print(int px, int py); /// affichage ++
        void resize(double percent); /// redimensionne une image
        void rotate(double percent); /// pivote une image

    protected:
        SDL_Surface * image;
        int x,y,w,h,alpha;
        int lastX, lastY;
        std::string name;
};

#endif // IMAGE_H
