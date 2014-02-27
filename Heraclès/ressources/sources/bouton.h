/*
    The Arvernes - The Card Game
    Copyright (C) 2013  Garçon Benoît

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

    Contact me : benoit.garconbesson@gmail.com
*/


#ifndef BOUTON_H
#define BOUTON_H


#include <SDL.h>
#include <cstdlib>
#include <stdlib.h>
#include <stdio.h>
#include <FMOD/fmod.h>
#include <SDL_image.h>
#include <math.h>
#include <fstream>
#include <string>
#include <sstream>
#include <iostream>
#include <windows.h>
#include <fstream>


#include "utile.h"
#include "affichage.h"


class bouton
{
    public:
        bouton(std::string name);
        bouton(std::string p_name, SDL_Rect p_position, SDL_Surface * p_On, SDL_Surface * p_Off);
        ~bouton();
        bouton(const bouton& other);
        SDL_Rect Getposition() { return m_position; }
        void Setposition(SDL_Rect val) { m_position = val; }
        SDL_Surface ** Getbouton() { return m_bouton; }
        void Setbouton(SDL_Surface * val, short int i) { m_bouton[i] = val; }
        bool GetinUse() { return m_inUse; }
        void SetinUse(bool val) { m_inUse = val; }
        void testPositionPiocheCombat(Input p_in, bool p_test);
        void afficher(SDL_Surface * p_screen);
        void afficherX(SDL_Surface * p_screen);
        void testPosition(Input p_in);
    protected:
    private:
        SDL_Rect m_position;
        SDL_Surface * m_bouton[5];
        SDL_Surface * m_boutonX[3];
        bool m_inUse;

};

#endif // BOUTON_H
