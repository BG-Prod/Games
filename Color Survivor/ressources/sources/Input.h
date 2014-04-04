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

#ifndef INPUT_H
#define INPUT_H


#include <cstdlib>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <fstream>
#include <string>
#include <sstream>
#include <iostream>
#include <windows.h>
#include <SDL.h>
#include <ctime>


#define X                   0
#define Y                   1
#define X_REEL              2
#define Y_REEL              3


class Input
{
    public:
        Input();
        virtual ~Input();

        void update();
        /// getter
        char get_touche(int i){return touche[i];}
        char get_souris_boutons(int i){return souris_boutons[i];}
        char get_exit(){return exit;}
        int mouse(int i){return souris[i];}
        /// setter
        void set_touche(int i, int valeur){touche[i] = valeur;}
        void set_souris_boutons(int i, int valeur){souris_boutons[i] = valeur;}
        void set_exit(int valeur){exit = valeur;}
        void set_souris(int i, int valeur){souris[i] = valeur;}

        /// saisie
        void activerSaisie();
        std::string str();
        void getSaisie();
        void desactiverSaisie();
        bool modeSaisie();

    protected:
    private:
        char touche[SDLK_LAST], souris_boutons[8], exit;
        int souris[4];
        std::string m_str;
        bool saisieActive;
};

#endif // INPUT_H
