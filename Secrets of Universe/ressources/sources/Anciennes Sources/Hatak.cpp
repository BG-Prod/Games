#include "Hatak.h"


using namespace std;


Hatak::Hatak(SDL_Rect p_coor) : Vaisseau()
{
    string lien;
    lien = cheminImage + "Hatak.bmp";

    for(int i = 0 ; i < 10 ; i++)
    {
        m_image[i] = SDL_DisplayFormat(IMG_Load(lien.c_str()));
        SDL_SetColorKey(m_image[i], SDL_SRCCOLORKEY, SDL_MapRGB(m_image[HAUT]->format, 255, 255, 255));
    }

    m_joueur = 2;

    lien = cheminImage + "boom.bmp";
    m_image[DETRUIT] = SDL_DisplayFormat(IMG_Load(lien.c_str()));
    SDL_SetColorKey(m_image[DETRUIT], SDL_SRCCOLORKEY, SDL_MapRGB(m_image[DETRUIT]->format, 0, 0, 0));


    lien = cheminImage + "bouclier_Hatak.png";
    m_imageBouclier[BOUCLIER] = IMG_Load(lien.c_str());
    m_position = p_coor;
    m_position.w = m_image[ACTUELLE]->w;
    m_position.h = m_image[ACTUELLE]->h;
}

Hatak::Hatak(const Hatak &p_HatakACopier) : Vaisseau()
{
    string lien;
    lien = cheminImage + "Hatak.bmp";

    for(int i = 0 ; i < 10 ; i++)
    {
        m_image[i] = SDL_DisplayFormat(IMG_Load(lien.c_str()));
        SDL_SetColorKey(m_image[i], SDL_SRCCOLORKEY, SDL_MapRGB(m_image[HAUT]->format, 255, 255, 255));
    }

    m_joueur = 2;

    lien = cheminImage + "bouclier_Hatak.png";
    m_imageBouclier[BOUCLIER] = SDL_DisplayFormat(IMG_Load(lien.c_str()));
    m_position = p_HatakACopier.m_position;
}

Hatak::~Hatak()
{
    SDL_FreeSurface(m_imageBouclier[BOUCLIER]);
    for(int i = 0 ; i < 10 ; i++)
    {
        SDL_FreeSurface(m_image[i]);
    }
}


