#ifndef ARME_H_INCLUDED
#define ARME_H_INCLUDED

#include "Constantes.h"
#include "Utile.h"
#include "Projectile.h"

SDL_Surface* copierEtRetourner(SDL_Surface*); // Auteur : Tomaka17

class Arme
{
    public:
        Arme();
        Arme(std::string, SDL_Rect);
        Arme(const Arme &armeACopier);
        ~Arme();
        void tirer(int p_etatVaisseau, SDL_Surface* p_ouColler, Input, int, SDL_Rect p_carton[],int p_listeDeg[]);
        int getInt(std::string);
        void actu(SDL_Rect);
        Projectile getTir(int);
        int getActiviteTir();

    protected:
        int m_degats, m_niveau, m_type, m_actif;
        SDL_Rect m_position;
        Projectile* m_tirs[1000];
};

#endif // ARME_H_INCLUDED
