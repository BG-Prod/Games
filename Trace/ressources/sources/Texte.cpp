/*
    Trace
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

#include <Texte.h>


using namespace std;


Texte::Texte()
{
    blanc.r = 255; blanc.g = 255; blanc.b = 255;
    gris_clair.r = 200; gris_clair.g = 200; gris_clair.b = 200;
    gris_fonce.r = 50; gris_fonce.g = 50; gris_fonce.b = 50;
    noir.r = 0; noir.g = 0; noir.b = 0;
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

    for (std::vector<SDL_Surface *>::iterator it = m_text_image.begin() ; it != m_text_image.end(); ++it)
    {
        if(*it != NULL)
        {
            SDL_FreeSurface(*it);
            *it = NULL;
        }
    }
    m_text_image.clear();
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

int Texte::create_text(string p_string, string p_police, int p_taille, SDL_Color p_couleur, int p_size_max)
{
    m_lien = cheminPolice + p_police + ".ttf";
    m_style = TTF_OpenFont(m_lien.c_str(), p_taille);
    for (std::vector<SDL_Surface *>::iterator it = m_text_image.begin() ; it != m_text_image.end(); ++it)
    {
        if(*it != NULL)
        {
            SDL_FreeSurface(*it);
            *it = NULL;
        }
    }
    m_text_image.clear();

    SDL_Rect position = {0,0,0,0};
    int inc = 0;
    string phrase = p_string;

    while(phrase.length() > 0)
    {
        inc = (phrase.length() > (p_size_max/(p_taille/2.1))) ? (p_size_max/(p_taille/2.1)) : phrase.length();
        m_text_image.push_back(TTF_RenderText_Blended(m_style, phrase.substr(0, inc).c_str(), p_couleur));
        position.y += p_taille;
        phrase.erase(0, inc);
    }

    int toReturn = TTF_FontLineSkip(m_style);

    TTF_CloseFont(m_style);
    m_style = NULL;

    return toReturn;
}

void Texte::print(string p_text, std::string p_police, int p_taille, SDL_Color p_couleur, int x, int y)
{
    m_place.x = x;
    m_place.y = y;
    int skip = create_text(p_text, p_police, p_taille, p_couleur, SDL_GetVideoSurface()->w - x);
    for (std::vector<SDL_Surface *>::iterator it = m_text_image.begin() ; it != m_text_image.end(); ++it)
    {
        if(*it != NULL)
        {
            SDL_BlitSurface(*it,NULL,SDL_GetVideoSurface(),&m_place);
            m_place.y += skip;
        }
    }
}

std::string Texte::str()
{
    return m_chaine;
}

