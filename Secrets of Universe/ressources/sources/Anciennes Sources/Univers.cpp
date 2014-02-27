#include "Univers.h"


using namespace std;


Univers::Univers()
{
    m_couleur.r = 60;
    m_couleur.g = 60;
    m_couleur.b = 60;
    string lien;
    lien = cheminPolice + "tunga.ttf";
    m_police[0] = TTF_OpenFont(lien.c_str(), 20);
    lien = cheminPolice + "Rockeb.TTF";
    m_police[1] = TTF_OpenFont(lien.c_str(), 22);
    lien = cheminImage + "interface169.png";
    m_image[0] = SDL_DisplayFormat(IMG_Load(lien.c_str()));
    SDL_SetColorKey(m_image[0], SDL_SRCCOLORKEY, SDL_MapRGB(m_image[0]->format, 0, 183, 239));
    m_texte[0] = TTF_RenderText_Blended(m_police[1], "BOC GETRONIAN", m_couleur);
    m_texte[1] = TTF_RenderText_Blended(m_police[1], "RAY STARV", m_couleur);
    m_texte[2] = TTF_RenderText_Blended(m_police[1], "TEXTE 3", m_couleur);
    m_texte[3] = TTF_RenderText_Blended(m_police[1], "TEXTE 4", m_couleur);

    for(int i = 0; i <2; i++)
    {
        for(int j = 0; j <2; j++)
        {
            m_valJauge[i][j] = 100;
        }
    }

    m_position1.x = 0;
    m_position1.y = 0;
    m_position2.x = 0;
    m_position2.y = 0;

    m_positionBarrePhaseur.x = 0;
    m_positionBarrePhaseur.y = 0;
    m_positionBarrePhaseur.w = 0;
    m_positionBarrePhaseur.h = 0;

    m_positionJaugePhaseur.x = 0;
    m_positionJaugePhaseur.y = 0;
    m_positionJaugePhaseur.w = 0;
    m_positionJaugePhaseur.h = 0;

    m_posBar1.x = 50;
    m_posBar1.y = 900;
    m_posBar1.w = 4;
    m_posBar1.h = 4;

    m_posJau1.x = 54;
    m_posJau1.y = 904;
    m_posJau1.w = 408;
    m_posJau1.h = 32;

    m_posBar2.x = 700;
    m_posBar2.y = 900;
    m_posBar2.w = 4;
    m_posBar2.h = 4;

    m_posJau2.x = 704;
    m_posJau2.y = 904;
    m_posJau2.w = 408;
    m_posJau2.h = 32;

    m_posBoucBar1.x = 50;
    m_posBoucBar1.y = 960;
    m_posBoucBar1.w = 4;
    m_posBoucBar1.h = 4;

    m_posBoucJau1.x = 54;
    m_posBoucJau1.y = 964;
    m_posBoucJau1.w = 408;
    m_posBoucJau1.h = 32;

    m_posBoucBar2.x = 700;
    m_posBoucBar2.y = 960;
    m_posBoucBar2.w = 4;
    m_posBoucBar2.h = 4;

    m_posBoucJau2.x = 704;
    m_posBoucJau2.y = 964;
    m_posBoucJau2.w = 408;
    m_posBoucJau2.h = 32;

    m_image[1] = SDL_CreateRGBSurface(SDL_HWSURFACE, m_posJau1.w + 2*m_posBar1.h, m_posJau1.h + 2*m_posBar1.h, 32, 0, 0, 0, 0);
    SDL_FillRect(m_image[1], NULL, SDL_MapRGB(m_image[1]->format, 60, 60, 60));

    m_image[2] = SDL_CreateRGBSurface(SDL_HWSURFACE, m_posJau2.w + 2*m_posBar2.h, m_posJau2.h + 2*m_posBar2.h, 32, 0, 0, 0, 0);
    SDL_FillRect(m_image[2], NULL, SDL_MapRGB(m_image[2]->format, 60, 60, 60));

    m_image[3] = SDL_CreateRGBSurface(SDL_HWSURFACE, m_posJau1.w, m_posJau1.h, 32, 0, 0, 0, 0);
    SDL_FillRect(m_image[3], NULL, SDL_MapRGB(m_image[3]->format, 200, 0, 0));

    m_image[4] = SDL_CreateRGBSurface(SDL_HWSURFACE, m_posJau2.w, m_posJau2.h, 32, 0, 0, 0, 0);
    SDL_FillRect(m_image[4], NULL, SDL_MapRGB(m_image[4]->format, 200, 0, 0));



    m_image[5] = SDL_CreateRGBSurface(SDL_HWSURFACE, m_posJau1.w + 2*m_posBar1.h, m_posJau1.h + 2*m_posBar1.h, 32, 0, 0, 0, 0);
    SDL_FillRect(m_image[5], NULL, SDL_MapRGB(m_image[5]->format, 60, 60, 60));

    m_image[6] = SDL_CreateRGBSurface(SDL_HWSURFACE, m_posJau2.w + 2*m_posBar2.h, m_posJau2.h + 2*m_posBar2.h, 32, 0, 0, 0, 0);
    SDL_FillRect(m_image[6], NULL, SDL_MapRGB(m_image[6]->format, 60, 60, 60));

    m_image[7] = SDL_CreateRGBSurface(SDL_HWSURFACE, m_posJau1.w, m_posJau1.h, 32, 0, 0, 0, 0);
    SDL_FillRect(m_image[7], NULL, SDL_MapRGB(m_image[7]->format, 0, 0, 200));

    m_image[8] = SDL_CreateRGBSurface(SDL_HWSURFACE, m_posJau2.w, m_posJau2.h, 32, 0, 0, 0, 0);
    SDL_FillRect(m_image[8], NULL, SDL_MapRGB(m_image[8]->format, 0, 0, 200));



    m_image[9] = NULL;
    m_image[10] = NULL;

    lien = cheminImage + "playa001.png";
    m_image[11] = SDL_DisplayFormat(IMG_Load(lien.c_str()));
    SDL_SetColorKey(m_image[11], SDL_SRCCOLORKEY, SDL_MapRGB(m_image[11]->format, 0, 183, 239));
    lien = cheminImage + "playa002.png";
    m_image[12] = SDL_DisplayFormat(IMG_Load(lien.c_str()));
    SDL_SetColorKey(m_image[12], SDL_SRCCOLORKEY, SDL_MapRGB(m_image[12]->format, 0, 183, 239));

    m_position11.x = 50;
    m_position11.y = 788;
    m_position11.w = 0;
    m_position11.h = 0;

    m_position12.x = 700;
    m_position12.y = 788;
    m_position12.w = 0;
    m_position12.h = 0;


    m_posTxt1.x = m_position11.x +154;
    m_posTxt1.y = m_position11.y +52 - m_texte[2]->h /2;
    m_posTxt2.x = m_position12.x +154;
    m_posTxt2.y = m_position12.y +52 - m_texte[2]->h /2;
    m_posTxt3.x = 0;
    m_posTxt3.y = 0;
    m_posTxt4.x = 0;
    m_posTxt4.y = 0;

}

Univers::~Univers()
{
    for(int i = 0 ; i < 13 ; i++)
    {
        SDL_FreeSurface(m_image[i]);
    }

    for(int i = 0 ; i < 4 ; i++)
    {
        SDL_FreeSurface(m_texte[i]);
    }

    for(int i = 0 ; i < 2 ; i++)
    {
        TTF_CloseFont(m_police[i]);
    }
}

void Univers::afficher(SDL_Surface* p_ouColler)
{
    SDL_BlitSurface(m_image[0], NULL, p_ouColler, NULL);

    m_posJau1.w = m_valJauge[0][0];
    m_posJau2.w = m_valJauge[1][0];
    m_posBoucJau1.w = m_valJauge[0][1];
    m_posBoucJau2.w = m_valJauge[1][1];

    SDL_Rect pop = {0,0,0,m_posBoucJau1.h};

    SDL_FillRect(m_image[3], NULL, SDL_MapRGB(m_image[3]->format, 60, 60, 60));
    SDL_FillRect(m_image[4], NULL, SDL_MapRGB(m_image[4]->format, 60, 60, 60));
    SDL_FillRect(m_image[7], NULL, SDL_MapRGB(m_image[7]->format, 60, 60, 60));
    SDL_FillRect(m_image[8], NULL, SDL_MapRGB(m_image[8]->format, 60, 60, 60));

    pop.w = 408*m_posJau1.w / 100;
    SDL_FillRect(m_image[3], &pop, SDL_MapRGB(m_image[3]->format, 200, 0, 0));
    pop.w = 408*m_posJau2.w / 100;
    SDL_FillRect(m_image[4], &pop, SDL_MapRGB(m_image[4]->format, 200, 0, 0));
    pop.w = 408*m_posBoucJau1.w / 100;
    SDL_FillRect(m_image[7], &pop, SDL_MapRGB(m_image[7]->format, 0, 0, 200));
    pop.w = 408*m_posBoucJau2.w / 100;
    SDL_FillRect(m_image[8], &pop, SDL_MapRGB(m_image[8]->format, 0, 0, 200));

    SDL_BlitSurface(m_image[1], NULL, p_ouColler, &m_posBar1);
    SDL_BlitSurface(m_image[3], NULL, p_ouColler, &m_posJau1);
    SDL_BlitSurface(m_image[2], NULL, p_ouColler, &m_posBar2);
    SDL_BlitSurface(m_image[4], NULL, p_ouColler, &m_posJau2);

    SDL_BlitSurface(m_image[5], NULL, p_ouColler, &m_posBoucBar1);
    SDL_BlitSurface(m_image[7], NULL, p_ouColler, &m_posBoucJau1);
    SDL_BlitSurface(m_image[6], NULL, p_ouColler, &m_posBoucBar2);
    SDL_BlitSurface(m_image[8], NULL, p_ouColler, &m_posBoucJau2);

    SDL_BlitSurface(m_image[11], NULL, p_ouColler, &m_position11);
    SDL_BlitSurface(m_image[12], NULL, p_ouColler, &m_position12);
    SDL_BlitSurface(m_texte[0], NULL, p_ouColler, &m_posTxt1);
    SDL_BlitSurface(m_texte[1], NULL, p_ouColler, &m_posTxt2);
}

SDL_Surface * Univers::get(string p_image)
{
    return m_image[0];
}

void Univers::modValJauge(int i, int j, int x)
{
    m_valJauge[i][j] = x;
}


