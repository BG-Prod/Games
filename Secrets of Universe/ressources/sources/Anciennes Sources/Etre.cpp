#include "Etre.h"


using namespace std;


Etre::Etre() : Objet()
{
    m_alive = true;
    m_vitesse = 5;
    m_joueur = 1;
    m_mobile = true;
}

Etre::Etre(const Etre &EtreACopier) : Objet()
{
    m_image[HAUT] = EtreACopier.m_image[HAUT];
    m_image[BAS] = EtreACopier.m_image[BAS];
    m_image[GAUCHE] = EtreACopier.m_image[GAUCHE];
    m_image[DROITE] = EtreACopier.m_image[DROITE];
    m_image[HD] = EtreACopier.m_image[HD];
    m_image[HG] = EtreACopier.m_image[HG];
    m_image[BG] = EtreACopier.m_image[BG];
    m_image[BD] = EtreACopier.m_image[BD];
    m_image[DETRUIT] = EtreACopier.m_image[DETRUIT];
    m_image[ACTUELLE] = EtreACopier.m_image[ACTUELLE];
    m_mobile = true;
}

Etre::~Etre()
{

}

void Etre::afficher(SDL_Surface* p_ouColler)
{
    SDL_BlitSurface(m_image[ACTUELLE], 0, p_ouColler, &m_position);
}

void Etre::moveUp()
{
    m_position.y -= m_vitesse;
    m_image[ACTUELLE] = m_image[HAUT];
    m_etat = HAUT;
}

void Etre::moveDown()
{
    if((m_position.y + m_image[ACTUELLE]->h) <= HAUTEUR_MAP)
    {
        m_position.y += m_vitesse;
    }
    m_image[ACTUELLE] = m_image[BAS];
    m_etat = BAS;
}

void Etre::moveLeft()
{
    m_position.x -= m_vitesse;
    m_image[ACTUELLE] = m_image[GAUCHE];
    m_etat = GAUCHE;
}

void Etre::moveRight()
{
    if((m_position.x + m_image[ACTUELLE]->w) <= LARGEUR_MAP)
    {
        m_position.x += m_vitesse;
    }
    m_image[ACTUELLE] = m_image[DROITE];
    m_etat = DROITE;
}

void Etre::moveDiag45()
{
    moveUp();
    moveRight();
    m_image[ACTUELLE] = m_image[HD];
    m_etat = HD;
}

void Etre::moveDiag135()
{
    moveDown();
    moveRight();
    m_image[ACTUELLE] = m_image[BD];
    m_etat = BD;
}

void Etre::moveDiag225()
{
    moveDown();
    moveLeft();
    m_image[ACTUELLE] = m_image[BG];
    m_etat = BG;
}

void Etre::moveDiag315()
{
    moveUp();
    moveLeft();
    m_image[ACTUELLE] = m_image[HG];
    m_etat = HG;
}

void Etre::attack()
{

}

int Etre::getEtat()
{
    return m_etat;
}

bool Etre::mobilite(bool p_vrfx)
{
    m_mobile = p_vrfx;

    return m_mobile;
}

