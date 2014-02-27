#ifndef PERSONNAGES_H_INCLUDED
#define PERSONNAGES_H_INCLUDED

#include "Constantes.h"
#include "Etre.h"

#include <SDL.h>
#include <SDL_image.h>
#include <FMOD/fmod.h>
#include <iostream>

class Personnage : public Etre
{
    public:
        Personnage();
        Personnage(const Personnage&);
        ~Personnage();

    protected:
};

#endif
