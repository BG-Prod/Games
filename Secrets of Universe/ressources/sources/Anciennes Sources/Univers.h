#ifndef UNIVERS_H_INCLUDED
#define UNIVERS_H_INCLUDED

#include "Constantes.h"

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <iostream>

class Univers
{
    public:
    Univers();
    ~Univers();
    void afficher(SDL_Surface *);
    SDL_Surface * get(std::string);
    void modValJauge(int i, int j, int x);

    protected:
    SDL_Surface *m_image[13], *m_texte[4];
    SDL_Rect m_position1, m_position2, m_posTxt1, m_posTxt2, m_posTxt3, m_posTxt4;
    TTF_Font * m_police[2];
    SDL_Color m_couleur;
    SDL_Rect m_positionBarrePhaseur, m_positionJaugePhaseur;
    SDL_Rect m_posBar1, m_posJau1;
    SDL_Rect m_posBar2, m_posJau2;
    SDL_Rect m_posBoucBar1, m_posBoucJau1;
    SDL_Rect m_posBoucBar2, m_posBoucJau2;
    SDL_Rect m_position11, m_position12;
    int m_valJauge[2][2];
};

#endif
