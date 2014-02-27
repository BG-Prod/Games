#include "Objet.h"


using namespace std;


Objet::Objet()
{
    m_alive = true;
    m_position.x = 600;//LARGEUR_MAP / 2 - m_image[ACTUELLE]->w / 2;
    m_position.y = 500;//HAUTEUR_MAP / 2 - m_image[ACTUELLE]->h / 2;
    m_position.w = 0;
    m_position.h = 0;
}

Objet::Objet(const Objet &p_ObjetACopier)
{
    m_alive = true;
}

Objet::~Objet()
{

}

bool Objet::get(string p_bool)
{
    bool acc;
    if (p_bool == "m_alive")
    {
        acc = this->m_alive;
    }
    return acc;
}

Couple Objet::getCouple()
{
    Couple iC = {m_image[ACTUELLE], m_position};
    return iC;
}

Couple Objet::getCoupleTir()
{
    Couple iC = {m_image[0], m_position};
    return iC;
}

SDL_Rect Objet::getPosition()
{
    return m_position;
}

