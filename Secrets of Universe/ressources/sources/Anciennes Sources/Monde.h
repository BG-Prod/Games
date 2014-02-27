#ifndef MONDE_H_INCLUDED
#define MONDE_H_INCLUDED

#include <SDL.h>
#include <SDL_image.h>
#include <iostream>


#include "Constantes.h"
#include "Map.h"

class Monde
{
    public:
        Monde(SDL_Surface ** p_images);
        Monde(const Monde &p_mondeACopier);
        ~Monde();

        void playMonde(SDL_Surface *p_ecran, Input*, SDL_Surface ** p_images);

    protected:
        Map *stage[11];
        SDL_Surface *m_echec, *m_next, *m_espace;

};

#endif // MONDE_H_INCLUDED
