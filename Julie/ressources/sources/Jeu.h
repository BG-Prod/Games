/*
    Julie
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

#ifndef JEU_H_INCLUDED
#define JEU_H_INCLUDED



#include <cstdlib>
#include <stdlib.h>
#include <stdio.h>
#include <string>
#include <vector>
#include <windows.h>
#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_image.h>
#include <FMOD/fmod.h>


#include "Input.h"
#include "Texte.h"
#include "utile.h"
#include "BDD.h"


class Jeu
{
    public:
        Jeu(SDL_Surface **);
        virtual ~Jeu();

        void game();
        void conjugaison();
        void mecanique();
        void affichage();
        void mecanique2();
        void affichage2();
        void timer();
        void resizeScreen();

        void explosion(SDL_Surface ** p_images, Animation * animation); /// permet d'afficher une explosion lorsque temps = 0

    protected:
    private:
        Input * m_in;
        int m_tempsPrecedent, m_tempsActuel, m_screen_refresh, note;
        Texte *question, *reponse;
        int data[40];
        std::string data2[100];
        SDL_Surface ** m_images;
};


#endif // JEU_H_INCLUDED
