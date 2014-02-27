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


#include "bouton.h"

bouton::bouton(std::string name)
{
    std::string lien = cheminImage + "boutonOFF_p.png";
    m_bouton[1] = SDL_DisplayFormat(IMG_Load(lien.c_str()));

    lien = cheminImage + "boutonON_p.png";
    m_bouton[2] = SDL_DisplayFormat(IMG_Load(lien.c_str()));

    lien = cheminImage + "boutonOFF_c.png";
    m_bouton[3] = SDL_DisplayFormat(IMG_Load(lien.c_str()));

    lien = cheminImage + "boutonON_c.png";
    m_bouton[4] = SDL_DisplayFormat(IMG_Load(lien.c_str()));

    m_bouton[0] = m_bouton[1];

    m_position.w = m_bouton[0]->w;
    m_position.h = m_bouton[0]->h;
    m_position.x = LARGEUR_ECRAN/2 - m_position.w/2;
    m_position.y = 128 - m_position.h/2;

    m_inUse = false;
}

bouton::bouton(std::string p_name, SDL_Rect p_position, SDL_Surface * p_On, SDL_Surface * p_Off)
{
    m_inUse = false;
    m_position = p_position;
    m_boutonX[1] = p_Off;
    m_boutonX[2] = p_On;
    m_boutonX[0] = m_boutonX[1];

    for(int i = 0; i < 5 ; i++) // ne pas vider la dernière image qui sert de mémoire tampon
    {
        if(m_bouton[i] != NULL)
        {
            m_bouton[i] = NULL;
        }
    }
}

bouton::~bouton()
{
    for(int i = 1; i < 5 ; i++) // ne pas vider la dernière image qui sert de mémoire tampon
    {
        if(m_bouton[i] != NULL)
        {
            SDL_FreeSurface(m_bouton[i]);
        }
    }
}

bouton::bouton(const bouton& other)
{
    //copy ctor
}

void bouton::testPositionPiocheCombat(Input p_in, bool p_test)
{
    if(p_test)
    {
        if(p_in.mousex >= m_position.x && p_in.mousex < m_position.x + m_position.w && p_in.mousey >= m_position.y && p_in.mousey < m_position.y + m_position.h)
        {
                m_bouton[0] = m_bouton[2];

                if(p_in.mousebuttons[SDL_BUTTON_LEFT])
                {
                    m_inUse = true;
                }
                else{m_inUse = false;}
        }
        else{m_bouton[0] = m_bouton[1]; m_inUse = false;}
    }
    else
    {
        if(p_in.mousex >= m_position.x && p_in.mousex < m_position.x + m_position.w && p_in.mousey >= m_position.y && p_in.mousey < m_position.y + m_position.h)
        {
                m_bouton[0] = m_bouton[4];

                if(p_in.mousebuttons[SDL_BUTTON_LEFT])
                {
                    m_inUse = true;
                }
                else{m_inUse = false;}
        }
        else{m_bouton[0] = m_bouton[3]; m_inUse = false;}
    }
}

void bouton::testPosition(Input p_in)
{
    if(p_in.mousex >= m_position.x && p_in.mousex < m_position.x + m_position.w && p_in.mousey >= m_position.y && p_in.mousey < m_position.y + m_position.h)
    {
            m_boutonX[0] = m_boutonX[2];

            if(p_in.mousebuttons[SDL_BUTTON_LEFT])
            {
                m_inUse = true;
            }
            else{m_inUse = false;}
    }
    else{m_boutonX[0] = m_boutonX[1]; m_inUse = false;}
}

void bouton::afficherX(SDL_Surface * p_screen)
{
    SDL_BlitSurface(m_boutonX[0], NULL, p_screen, &m_position);
}

void bouton::afficher(SDL_Surface * p_screen)
{
    SDL_BlitSurface(m_bouton[0], NULL, p_screen, &m_position);
}


