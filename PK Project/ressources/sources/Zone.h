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

#ifndef ZONE_H
#define ZONE_H


#include <iostream>
#include <SDL.h>
#include <SDL_ttf.h>


#include "utile.h"
#include "Case.h"


class Zone
{
    public:
        Zone();
        virtual ~Zone();

        void afficher();
        void setPosition(int,int);
        void init(SDL_Surface ** p_images, Input * p_in);

    protected:
    private:
        Case ** m_case;
        Input * m_in;
        SDL_Rect m_position;
        SDL_Surface ** m_images;

};

#endif // ZONE_H
