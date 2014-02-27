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

#ifndef CASE_H
#define CASE_H


#include <iostream>
#include <SDL.h>
#include <SDL_ttf.h>


#include "utile.h"
#include "Input.h"


class Case
{
    public:
        Case();
        virtual ~Case();

        void afficher();
        int event();
        void setPosition(int x, int y);
        void init(SDL_Surface ** p_images, Input * p_in);

    protected:
    private:
        SDL_Rect m_position;
        SDL_Surface ** m_images;
        Input * m_in;
        int m_numImage, m_numImagePrecedente;
        std::string m_nom;
        int m_portion;
};

#endif // CASE_H
