#ifndef OBJET_H_INCLUDED
#define OBJET_H_INCLUDED


#include <SDL_ttf.h>
#include <SDL_image.h>
#include <FMOD/fmod.h>
#include <iostream>


#include "Constantes.h"

typedef struct Couple Couple;
struct Couple
{
    SDL_Surface * image;
    SDL_Rect coor;
};

class Objet
{
    public:
        Objet();
        Objet(const Objet&);
        ~Objet();

        bool get(std::string);
        Couple getCouple();
        Couple getCoupleTir();
        SDL_Rect getPosition();

    protected:
        SDL_Rect m_position;
        SDL_Surface * m_image[10];
        bool m_alive;
        int m_type, m_masse;
};

#endif // OBJET_H_INCLUDED
