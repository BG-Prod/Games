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

#ifndef TEXTE_H
#define TEXTE_H


#include <iostream>
#include <SDL.h>
#include <SDL_ttf.h>
#include <vector>


#include "utile.h"


class Texte
{
    public:
        Texte();
        virtual ~Texte();

        void print(std::string p_text, std::string p_police, int p_taille, SDL_Color p_couleur, int x, int y);
        std::string str();


    protected:
        void copy_picture(SDL_Surface * origin, SDL_Surface * destination);
        int create_text(std::string p_string, std::string p_police, int p_taille, SDL_Color p_couleur, int p_size_max);

    private:
        std::vector<SDL_Surface *> m_text_image;
        SDL_Rect m_place;
        /// couleurs
        SDL_Color blanc,gris_clair,gris_fonce,noir,m_couleur;
        TTF_Font * m_style;
        std::string m_lien, m_chaine;
};

#endif // TEXTE_H
