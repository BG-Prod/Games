#ifndef VAISSEAU_H_INCLUDED
#define VAISSEAU_H_INCLUDED


#include <SDL.h>
#include <SDL_image.h>
#include <FMOD/fmod.h>
#include <iostream>


#include "Constantes.h"
#include "Personnage.h"
#include "Arme.h"


class Vaisseau : public Etre
{
    public:
    Vaisseau();
    Vaisseau(const Vaisseau&);
    ~Vaisseau();
    void attaquer(SDL_Surface* p_ouColler, Input, SDL_Rect p_carton[],int p_listeDeg[]);
    void bouclier(SDL_Surface *, Input);
    void update(SDL_Surface*, SDL_Surface*, Input, SDL_Rect p_carton[],int p_listeDeg[]);
    void IA(SDL_Surface*, Input, SDL_Rect p_carton[],int p_listeDeg[]);
    int modCoque(int mod);
    Projectile getTirs(int);
    SDL_Rect getPos();
    int getActiviteArme();
    int getParametre(int x);
    void anim_explosion(SDL_Surface * p_ou);

    protected:
    int m_energie, m_bouclier, m_coque, m_capteur, m_teleporteur, m_hypernavigateur, m_moteur, m_nb_explosion;
    Arme *m_batterie;
    SDL_Surface* m_imageBouclier[5], *m_explosion;
    SDL_Rect m_placeBouclier, m_placeArme1;
    bool m_activiteBouclier, m_bool_explosion;

};

#endif // VAISSEAU_H_INCLUDED
