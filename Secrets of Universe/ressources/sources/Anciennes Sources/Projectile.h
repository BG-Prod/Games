#ifndef PROJECTILE_H_INCLUDED
#define PROJECTILE_H_INCLUDED


#include <FMOD/fmod.h>


#include "Constantes.h"
#include "Objet.h"


bool collision( SDL_Rect A, SDL_Rect B );

class Projectile : public Objet
{
    public:
        Projectile(SDL_Surface ** p_images);
        Projectile(std::string, SDL_Rect);
        Projectile(const Projectile &projectileACopier);
        ~Projectile();
        void afficher(SDL_Surface* p_ouColler);
        void IA(int, SDL_Surface*,SDL_Rect p[],int p_listeDeg[]);
        SDL_Rect getPosTir();
        bool getBool();

    protected:
        int m_degats, m_tempsCreation, m_tempsActuel, m_dir;
        FMOD_SYSTEM * m_system;
        FMOD_SOUND * m_musicBoom;

};




#endif // PROJECTILE_H_INCLUDED
