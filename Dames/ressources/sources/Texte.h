/*
    Draughts - Les Dames
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


#include "utile.h"


class Texte
{
    public:
        Texte();
        virtual ~Texte();

        unsigned short int Get_m_nombre() { return m_nombre; }
        void Set_m_nombre(unsigned short int val) { m_nombre = val; }

        void load_text();
        void copy_picture(SDL_Surface * origin, SDL_Surface * destination);
        void erase_text();
        void create_text(std::string p_string, std::string p_police, int p_taille, SDL_Color p_couleur);
        void create_text(std::string p_string);

        void print_text(std::string p_string);
        void print_text(std::string p_text, std::string p_police, int p_taille, SDL_Color p_couleur, int x, int y);
        void print_text(int x, int y);
        void print_text();
        void print_text(int k);
        void print_text(int k, int x, int y);

        void chose_text(int k);

    protected:
    private:
        unsigned short int m_nombre; //!< Member variable "m_nombre"
        unsigned short int m_id; //!< Member variable "m_id"
        unsigned short int m_taille; //!< Member variable "m_taille"
        std::string * m_phrases; //!< Member variable "m_phrases"
        std::string m_lien; //!< Member variable "m_lien"
        SDL_Rect m_place_base; //!< Member variable "m_place_base"
        SDL_Rect m_place_var; //!< Member variable "m_place_var"
        SDL_Surface * m_text_image; //!< Member variable "m_text_image"
        SDL_Surface ** m_phrase_image; //!< Member variable "m_phrase_image"
        /// couleurs
        SDL_Color blanc,gris_clair,gris_fonce,noir,m_couleur;
        TTF_Font * m_style;
};

#endif // TEXTE_H
