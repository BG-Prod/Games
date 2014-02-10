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
			souris[X] = event.motion.x;
			souris[Y] = event.motion.y;
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

