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

#include "Image.h"

using namespace std;

Image::Image()
{
    image = NULL;
    x = 0, y = 0, w = 0, h = 0, alpha = 255;
    lastX = 0, lastY = 0;
    name = "NULL";
}

Image::Image(string link)
{
    image = SDL_DisplayFormatAlpha(IMG_Load(link.c_str())); ///SDL_DisplayFormat(IMG_Load(link.c_str()));
    x = 0, y = 0, w = image->w, h = image->h, alpha = 255;
    lastX = 0, lastY = 0;
    name = link;
}

Image::Image(int width, int height, Uint8 r, Uint8 g, Uint8 b)
{
    image = SDL_CreateRGBSurface(SDL_HWSURFACE, width, height, 32, 0, 0, 0, 0);
    SDL_FillRect(image, NULL, SDL_MapRGBA(image->format, r, g, b, 255));
    x = 0, y = 0, w = image->w, h = image->h, alpha = 255;
    lastX = 0, lastY = 0;
    name = "Colored surface";
}

Image::Image(int width, int height, Uint8 r, Uint8 g, Uint8 b, Uint8 a)
{
    image = SDL_CreateRGBSurface(SDL_HWSURFACE, width, height, 32, 0, 0, 0, 0);
    SDL_FillRect(image, NULL, SDL_MapRGBA(image->format, r, g, b, a));
    x = 0, y = 0, w = image->w, h = image->h, alpha = a;
    lastX = 0, lastY = 0;
    name = "Colored surface";
}

Image::~Image()
{
    if(image != NULL)
    {
        SDL_FreeSurface(image);
    }
}

void Image::print()
{
    SDL_Rect where = {lastX, lastY, w, h};
    SDL_BlitSurface(image, NULL, SDL_GetVideoSurface(), &where);
}

void Image::print(int px, int py)
{
    lastX = px;
    lastY = py;
    print();
}

void Image::print(Coordonnees where, Coordonnees from)
{
    SDL_Rect ou, dou;
    ou.x = where.x();
    ou.y = where.y();
    ou.w = where.w();
    ou.h = where.h();
    dou.x = from.x();
    dou.y = from.y();
    dou.w = from.w();
    dou.h = from.h();
    SDL_BlitSurface(image, &dou, SDL_GetVideoSurface(), &ou);
}

void Image::print(Image * buffer, Coordonnees where, Coordonnees from)
{
    SDL_Rect ou, dou;
    ou.x = where.x();
    ou.y = where.y();
    ou.w = where.w();
    ou.h = where.h();
    dou.x = from.x();
    dou.y = from.y();
    dou.w = from.w();
    dou.h = from.h();
    SDL_BlitSurface(image, &dou, buffer->image, &ou);
}

void Image::resize(double percent)
{
    image = rotozoomSurface(image, 0.0,(double)percent/100,1);
}

void Image::rotate(double percent)
{
    image = rotozoomSurface(image, percent,1,1);
}

void Image::copy(Image * origin)
{
    if(this->image != NULL)
    {
        SDL_FreeSurface(image);
        image = NULL;
    }

    image = SDL_CreateRGBSurface(SDL_HWSURFACE, origin->image->w, origin->image->h,
                                       origin->image->format->BitsPerPixel,
                                       origin->image->format->Rmask,
                                       origin->image->format->Gmask,
                                       origin->image->format->Bmask,
                                       origin->image->format->Amask);

    image = SDL_DisplayFormatAlpha(origin->image);
}

void Image::clear()
{
    SDL_FillRect(image, 0, SDL_MapRGB(SDL_GetVideoSurface()->format, 0, 255, 0));
}

void Image::setAsIcon()
{
    SDL_WM_SetIcon(image, NULL);
}

void Image::setAlpha(int a)
{
    SDL_SetAlpha(image, SDL_SRCALPHA, a);
}



