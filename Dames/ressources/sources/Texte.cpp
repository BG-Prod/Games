/*
    Draughts - Les Dames
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

#include "Texte.h"


using namespace std;


Texte::Texte()
{
    m_lien = cheminFile + "texte.txt";
    m_place_base = {HAUTEUR_ECRAN+(100./840.)*HAUTEUR_ECRAN,(840./1080.)*HAUTEUR_ECRAN,0,0};
    m_place_var = {0,0,0,0};
    m_nombre = nombreLignes(m_lien.c_str())-1+2;
    m_id = 0;
    m_taille = 30.0*RESIZE;
    blanc = {255,255,255};
    gris_clair = {200,200,200};
    gris_fonce = {50,50,50};
    noir = {0,0,0};
    m_couleur = noir;
    m_phrases = new string[m_nombre];
    for(int i = 0 ; i < m_nombre ; i++)
    {
        m_phrases[i] = niemeLigne(m_lien.c_str(), i);
    }
    m_text_image = NULL;
    m_phrase_image = new SDL_Surface*[m_nombre];
    for(int i = 0 ; i < m_nombre ; i++)
    {
        m_phrase_image[i] = NULL;
    }
    m_lien = cheminPolice + "arial" + ".ttf";
    m_style = TTF_OpenFont(m_lien.c_str(),m_taille);
}

Texte::~Texte()
{
    erase_text();
    TTF_CloseFont(m_style);
}

void Texte::load_text()
{
    for(int i = 0 ; i < m_nombre-2 ; i++)
    {
        m_place_var = m_place_base;
        create_text(m_phrases[i].c_str(), "calibri", m_taille, m_couleur);
        m_phrase_image[i] = copieSurface(m_text_image);
    }
    /// username
    DWORD StrLen = 256;
    TCHAR SysInfoStr[256];
    GetComputerName(SysInfoStr, &StrLen);
    std::string nameComputeur = SysInfoStr;
    GetUserName(SysInfoStr, &StrLen);
    std::string nameUser = SysInfoStr;

    create_text(nameUser.c_str(), "calibri", m_taille, m_couleur);
    m_phrase_image[m_nombre-2] = copieSurface(m_text_image);

    create_text(nameComputeur.c_str(), "calibri", m_taille, m_couleur);
    m_phrase_image[m_nombre-1] = copieSurface(m_text_image);
}

void Texte::erase_text()
{
    delete [] m_phrases;
    for(int i = 0 ; i < m_nombre ; i++)
    {
        if(m_phrase_image[i] != NULL)
        {
            SDL_FreeSurface(m_phrase_image[i]);
        }
    }
    delete [] m_phrase_image;
}

void Texte::copy_picture(SDL_Surface * origin, SDL_Surface * destination)
{
    if(destination != NULL)
    {
        SDL_FreeSurface(destination);
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
    m_taille = p_taille;
    m_couleur = p_couleur;
    m_lien = cheminPolice + p_police + ".ttf";
    TTF_CloseFont(m_style);
    m_style = TTF_OpenFont(m_lien.c_str(), m_taille);
    if(m_text_image != NULL)
    {
        SDL_FreeSurface(m_text_image);
    }
    m_text_image = TTF_RenderText_Blended(m_style, p_string.c_str(), m_couleur);
}

void Texte::create_text(string p_string)
{
    SDL_FreeSurface(m_text_image);
    m_text_image = TTF_RenderText_Blended(m_style, p_string.c_str(), m_couleur);
}

void Texte::print_text(string p_text, std::string p_police, int p_taille, SDL_Color p_couleur, int x, int y)
{
    m_place_var.x = x;
    m_place_var.y = y;
    create_text(p_text, p_police, p_taille, p_couleur);
    SDL_BlitSurface(m_text_image,NULL,SDL_GetVideoSurface(),&m_place_var);
}

void Texte::print_text(int x, int y)
{
    m_place_var.x = x;
    m_place_var.y = y;
    SDL_BlitSurface(m_text_image,NULL,SDL_GetVideoSurface(),&m_place_var);
}

void Texte::print_text()
{
    SDL_BlitSurface(m_text_image,NULL,SDL_GetVideoSurface(),&m_place_base);
}

void Texte::print_text(int k)
{
    SDL_BlitSurface(m_phrase_image[k],NULL,SDL_GetVideoSurface(),&m_place_base);
}

void Texte::print_text(int k, int x, int y)
{
    m_place_var.x = x;
    m_place_var.y = y;
    SDL_BlitSurface(m_phrase_image[k],NULL,SDL_GetVideoSurface(),&m_place_var);
}

void Texte::chose_text(int k)
{
    if(k >= 0 && k < m_nombre)
    {
        m_text_image = m_phrase_image[k];
    }
}

