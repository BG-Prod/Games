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

#include "Input.h"


Input::Input()
{
    for(int i = 0 ; i < SDLK_LAST ; i++)
    {
        touche[i] = 0;
    }
    for(int i = 0 ; i < 8 ; i++)
    {
        souris_boutons[i] = 0;
    }
    exit = 0;
    for(int i = 0 ; i < 4 ; i++)
    {
        souris[i] = 0;
    }
    m_str = "";
    saisieActive = false;
}

Input::~Input()
{

}

void Input::update()
{
	SDL_Event event;
    souris_boutons[SDL_BUTTON_WHEELUP] = 0;
    souris_boutons[SDL_BUTTON_WHEELDOWN] = 0;
	while(SDL_PollEvent(&event))
	{
		if(event.type == SDL_KEYDOWN)
		{
            touche[event.key.keysym.sym] = 1;
            if(saisieActive)
            {
                if(event.key.keysym.sym == SDLK_BACKSPACE)
                {
                    if(m_str.length() > 0)
                    {
                        m_str.erase(m_str.length()-1);
                    }
                }
                else if(event.key.keysym.sym == SDLK_RETURN || event.key.keysym.sym == SDLK_KP_ENTER)
                {
                    saisieActive = false;
                }
                else if(event.key.keysym.sym >= SDLK_KP0 && event.key.keysym.sym <= SDLK_KP9)
                {
                    m_str += (char)(event.key.keysym.sym-SDLK_KP0+SDLK_0);
                }
                else if(event.key.keysym.sym == SDLK_SPACE)
                {
                    m_str += ' ';
                }
                else if(event.key.keysym.sym == SDLK_a)
                {
                    m_str += 'q';
                }
                else if(event.key.keysym.sym == SDLK_q)
                {
                    m_str += 'a';
                }
                else if(event.key.keysym.sym == SDLK_w)
                {
                    m_str += 'z';
                }
                else if(event.key.keysym.sym == SDLK_z)
                {
                    m_str += 'w';
                }
                else if(event.key.keysym.sym == SDLK_SEMICOLON)
                {
                    m_str += 'm';
                }
                else if(event.key.keysym.sym == SDLK_MINUS)
                {
                    m_str += ')';
                }
                else if(event.key.keysym.sym == SDLK_m)
                {
                    m_str += ',';
                }
                else if(event.key.keysym.sym == SDLK_1)
                {
                    m_str += '&';
                }
                else if(event.key.keysym.sym == SDLK_2)
                {
                    m_str += 'é';
                }
                else if(event.key.keysym.sym == SDLK_3)
                {
                    m_str += '"';
                }
                else if(event.key.keysym.sym == SDLK_4)
                {
                    m_str += "'";
                }
                else if(event.key.keysym.sym == SDLK_5)
                {
                    m_str += '(';
                }
                else if(event.key.keysym.sym == SDLK_6)
                {
                    m_str += '-';
                }
                else if(event.key.keysym.sym == SDLK_7)
                {
                    m_str += 'è';
                }
                else if(event.key.keysym.sym == SDLK_8)
                {
                    m_str += '_';
                }
                else if(event.key.keysym.sym == SDLK_9)
                {
                    m_str += 'ç';
                }
                else if(event.key.keysym.sym == SDLK_0)
                {
                    m_str += 'à';
                }
                else if(event.key.keysym.sym == SDLK_KP_MULTIPLY)
                {
                    m_str += '*';
                }
                else if(event.key.keysym.sym == SDLK_BACKSLASH)
                {
                    m_str += '*';
                }
                else if(event.key.keysym.sym == SDLK_ESCAPE)
                {

                }
                else if(event.key.keysym.sym == SDLK_LSHIFT || event.key.keysym.sym == SDLK_RSHIFT)
                {

                }
                else
                {
                    m_str += SDL_GetKeyName(event.key.keysym.sym);
                }

            }
		}
		if(event.type == SDL_KEYUP)
		{
		    touche[event.key.keysym.sym] = 0;
		}
		if(event.type == SDL_MOUSEMOTION)
		{
			souris[X_WIN] = event.motion.x;
			souris[Y_WIN] = event.motion.y;
			souris[X_REEL] = event.motion.xrel;
			souris[Y_REEL] = event.motion.yrel;
		}
		if(event.type == SDL_MOUSEBUTTONDOWN)
		{
			souris_boutons[event.button.button] = 1;
		}
		if(event.type == SDL_MOUSEBUTTONUP)
		{
            if (event.button.button!=SDL_BUTTON_WHEELUP && event.button.button!=SDL_BUTTON_WHEELDOWN)
			{
                souris_boutons[event.button.button] = 0;
            }
		}
		if(event.type == SDL_QUIT)
		{
			exit = 1;
		}
	}
}

void Input::activerSaisie()
{
    m_str = "";
    saisieActive = true;
}

void Input::desactiverSaisie()
{
    saisieActive = false;
}

bool Input::modeSaisie()
{
    return saisieActive;
}

std::string Input::str()
{
    return m_str;
}

