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

#include "Texte.h"


using namespace std;


Texte::Texte()
{
    blanc = {255,255,255};
    gris_clair = {200,200,200};
    gris_fonce = {50,50,50};
    noir = {0,0,0};
    m_text_image = NULL;
    m_style = NULL;
    m_lien = "";
    m_chaine = "";
}

Texte::~Texte()
{
    if(m_style != NULL)
    {
        TTF_CloseFont(m_style);
        m_style = NULL;
    }

    if(m_text_image != NULL)
    {
        SDL_FreeSurface(m_text_image);
        m_text_image = NULL;
    }
}

void Texte::copy_picture(SDL_Surface * origin, SDL_Surface * destination)
{
    if(destination != NULL)
    {
        SDL_FreeSurface(destination);
        destination = NULL;
    }

    destination = SDL_CreateRGBSurface(SDL_HWSURFACE, origin->w, origin->h,
                                       origin->format->BitsPerPixel,
                                       origin->format->Rmask,
                                       origin->format->Gmask,
                                       origin->format->Bmask,
                                       origin->format->Amask);

    destination = SDL_DisplayFormatAlpha(origin);
}

void Texte::create_text(string p_string, string p_police, int p_taille, SDL_Color p_couleur)
{
    m_lien = cheminPolice + p_police + ".ttf";
    m_style = TTF_OpenFont(m_lien.c_str(), p_taille);
    if(m_text_image != NULL)
    {
        SDL_FreeSurface(m_text_image);
        m_text_image = NULL;
    }
    m_text_image = TTF_RenderText_Blended(m_style, p_string.c_str(), p_couleur);
    TTF_CloseFont(m_style);
    m_style = NULL;
}

void Texte::print(string p_text, std::string p_police, int p_taille, SDL_Color p_couleur, int x, int y)
{
    m_place.x = x;
    m_place.y = y;
    create_text(p_text, p_police, p_taille, p_couleur);
    SDL_BlitSurface(m_text_image,NULL,SDL_GetVideoSurface(),&m_place);
}

std::string Texte::str()
{
    return m_chaine;
}

