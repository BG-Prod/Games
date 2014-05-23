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
#include <vector>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

#include <Coordonnees.h>

#define ALPHA   0
#define RED     1
#define GREEN   2
#define BLUE    3

Uint32 color(int r, int g, int b, int alpha);
Uint32 color(int r, int g, int b);

class Image
{
    public:
        Image();    /// image NULL par défaut
        Image(std::string link);    /// image à partir d'un lien
        Image(int width, int height, Uint8 r, Uint8 g, Uint8 b);
        Image(int width, int height, Uint8 r, Uint8 g, Uint8 b, Uint8 a);
        virtual ~Image();           /// destructeur

        void print();               /// affichage par défaut direct
        void print(int px, int py); /// affichage ++ direct
        void print(Coordonnees where, Coordonnees from); /// affichage partiel direct
        void print(Image * buffer, Coordonnees where); /// affichage buffer
        void print(Image * buffer, Coordonnees where, Coordonnees from); /// affichage complet buffer
        void resize(double percent); /// redimensionne une image
        void rotate(double percent); /// pivote une image
        void copy(Image * origin);     /// copie une image
        void clear();
        void setAsIcon();
        void setAlpha(int a);
        int width(){return w;}
        int height(){return h;}

        Uint32 getPixel(int x, int y);  /// renvoie le pixel sous forme hexadecimal sur 32 bits
        const int * getPixelRGBA(int x, int y); /// renvoie le pixel sous forma d'un tableau A,R,G,B
        void setPixel(int x, int y, Uint32 coul); /// permet de paramétrer un pixel
        void line(int x1, int y1, int x2, int y2, Uint32 color);
        void circle(int x, int y, int r, int color);
        void toBlackAndWhite();
        void toGreyLevels();
        void turn90();

    protected:
        SDL_Surface * image;
        int x,y,w,h,alpha;
        int lastX, lastY;
        std::string name;

    private:
        void echangerEntiers(int* x, int* y);
};

#endif // IMAGE_H
