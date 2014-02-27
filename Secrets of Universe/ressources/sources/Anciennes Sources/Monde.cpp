#include <SDL.h>
#include <SDL_image.h>
#include <string>

#include "Monde.h"

using namespace std;

Monde::Monde(SDL_Surface ** p_images)
{
    m_echec = p_images[4];

    m_next = p_images[5];

    m_espace = p_images[6];

    for(int i = 0; i < NOMBRE_MAP; i++)
    {
        stage[i] = NULL;
    }
}

Monde::Monde(const Monde &p_mondeACopier)
{

}

Monde::~Monde()
{
    for(int i = 0; i < NOMBRE_MAP; i++)
    {
        delete stage[i];
    }
}

void Monde::playMonde(SDL_Surface *p_ecran, Input * p_in, SDL_Surface ** p_images)
{
    SDL_Rect origine = {p_ecran->w / 2 - m_espace->w / 2, p_ecran->h /2 - m_espace->h /2};

    SDL_BlitSurface(m_espace, NULL, p_ecran, &origine);
    SDL_Flip(p_ecran);

    for(int i = 0; i < NOMBRE_MAP; i++)
    {
        stage[i] = new Map(p_images);
        stage[i]->playMap(p_ecran, *p_in, p_images);
        delete stage[i];
        stage[i] = NULL;
        p_in->key[SDLK_RETURN] = 0;
        p_in->key[SDLK_ESCAPE] = 0;

        SDL_BlitSurface(m_next, NULL, p_ecran, &origine);
        SDL_Flip(p_ecran);
    }
}

