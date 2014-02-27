//#include <SDL_image.h>
#include <string>
#include <iostream>

#include "Arme.h"

using namespace std;

Arme::Arme() : m_degats(10), m_niveau(1), m_type(BATTERIE), m_actif(-1)
{
    m_position.x = 0;
    m_position.y = 0;
    for(int i = 0; i <1000; i++)
    {
        m_tirs[i] = NULL;
    }
}

Arme::Arme(string p_nom, SDL_Rect p_pos) : m_actif(-1)
{
    m_position = p_pos;

    if(p_nom == "laser")
        m_degats = 10;
        m_niveau = 1;
        m_type = LASER;
    if(p_nom == "phaseur")
        m_degats = 15;
        m_niveau = 1;
        m_type = PHASEUR;
    if(p_nom == "batterie")
        m_degats = 5;
        m_niveau = 1;
        m_type = BATTERIE;
    if(p_nom == "canon")
        m_degats = 5;
        m_niveau = 1;
        m_type = CANON;
    for(int i = 0; i <1000; i++)
    {
        m_tirs[i] = NULL;
    }
}

Arme::Arme(const Arme &armeACopier) : m_degats(armeACopier.m_degats), m_niveau(armeACopier.m_niveau)
{
    for(int i = 0; i <1000; i++)
    {
        m_tirs[i]= NULL;
    }
}

Arme::~Arme()
{
    for(int i = 0; i <1000; i++)
    {
        delete m_tirs[i];
    }
}

void Arme::tirer(int p_etatVaisseau, SDL_Surface* p_ouColler, Input p_in, int p_joueur, SDL_Rect p_carton[],int p_listeDeg[])
{
    if(p_joueur == 1)
    {
        if (p_in.key[SDLK_SPACE])
        {
            m_actif++;
            m_tirs[m_actif] = new Projectile("batterie", m_position);
            p_in.key[SDLK_SPACE] = 0;
        }
        if(m_actif >= 0)
        {
            for(int i = 0; i <= m_actif; i++)
            {
                if(m_tirs[i]->get("m_alive"))
                {
                    m_tirs[i]->IA(p_etatVaisseau, p_ouColler,p_carton,p_listeDeg);
                }
                if(!m_tirs[i]->get("m_alive") && i != m_actif)
                {
                    delete m_tirs[i];
                    m_tirs[i] = NULL;
                    m_tirs[i] = m_tirs[m_actif];
                    m_tirs[m_actif] = NULL;
                    if(m_tirs[i]->get("m_alive"))
                    {
                        m_tirs[i]->IA(p_etatVaisseau, p_ouColler,p_carton,p_listeDeg);
                    }
                    m_actif--;
                }
                if(!m_tirs[i]->get("m_alive") && i == m_actif)
                {
                    delete m_tirs[i];
                    m_tirs[i] = NULL;
                    m_actif--;
                }
            }
        }
    }

    if(p_joueur == 2)
    {
        if (p_in.key[SDLK_KP0])
        {
            m_actif++;
            m_tirs[m_actif] = new Projectile("batterie", m_position);
            p_in.key[SDLK_KP0] = 0;
        }
        if(m_actif >= 0)
        {
            for(int i = 0; i <= m_actif; i++)
            {
                if(m_tirs[i]->get("m_alive"))
                {
                    m_tirs[i]->IA(p_etatVaisseau, p_ouColler,p_carton,p_listeDeg);
                }
                if(!m_tirs[i]->get("m_alive"))
                {
                    m_tirs[i] = m_tirs[m_actif];
                    if(m_tirs[i]->get("m_alive"))
                    {
                        m_tirs[i]->IA(p_etatVaisseau, p_ouColler,p_carton,p_listeDeg);
                    }
                    m_actif--;
                }
            }
        }
    }
}

int Arme::getInt(string r)
{
    int aRetourner = 0;
    if(r == "m_degats")
        aRetourner = this->m_degats;
    if(r == "m_niveau")
        aRetourner = this->m_niveau;

    return aRetourner;
}

void Arme::actu(SDL_Rect p_position)
{
    m_position = p_position;
}

Projectile Arme::getTir(int p_i)
{
    return *m_tirs[p_i];
}

int Arme::getActiviteTir()
{
    return m_actif;
}
