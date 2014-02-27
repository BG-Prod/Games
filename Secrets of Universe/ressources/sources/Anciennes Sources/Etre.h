#ifndef ETRE_H_INCLUDED
#define ETRE_H_INCLUDED

#include "Objet.h"

#include <iostream>

class Etre : public Objet
{
    public:
        Etre();
        Etre(const Etre&);
        ~Etre();
        void afficher(SDL_Surface *);
        void moveUp();
        void moveDown();
        void moveLeft();
        void moveRight();
        void moveDiag45();
        void moveDiag135();
        void moveDiag225();
        void moveDiag315();
        void attack();
        int getEtat();
        bool mobilite(bool);

    protected:
        bool m_mobile;
        int m_vitesse, m_etat, m_joueur;
};

#endif // ETRE_H_INCLUDED
