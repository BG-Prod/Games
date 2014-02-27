#ifndef ENVIRONNEMENT_H_INCLUDED
#define ENVIRONNEMENT_H_INCLUDED

#include <math.h>

#include "Objet.h"
#include "Univers.h"
#include "Vaisseau.h"

class Environnement
{
    public:
        Environnement();
        Environnement(const Environnement&);
        ~Environnement();

        void gerer(Vaisseau *p_tableauObjet[], SDL_Surface* p_ou, SDL_Surface*, Input p_in, SDL_Rect p_coor[], int p_listeDeg[], Univers *p_uni, int p_info[][2]);
        bool check_collision( SDL_Rect A, SDL_Rect B );
        void combienDeTirs(Projectile* p_tableauATirs[]);

    protected:
        int m_actif, m_tirsActifs;

};

#endif // ENVIRONNEMENT_H_INCLUDED
