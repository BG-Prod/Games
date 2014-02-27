#ifndef MAP_H_INCLUDED
#define MAP_H_INCLUDED

#include <SDL.h>
#include <SDL_image.h>
#include <iostream>

#include "Constantes.h"
#include "Utile.h"
#include "Univers.h"
#include "BC304.h"
#include "Hatak.h"
#include "Environnement.h"

class Map
{
    public:
        Map(SDL_Surface ** p_images);
        Map(const Map &p_mapACopier);
        ~Map();

        int charger();
        void playMap(SDL_Surface *p_ecran, Input p_in, SDL_Surface ** p_images);
        void majCoor();
        void majCartonDegat(int p_i, int p_mod);
        int getCartonDegat(int p_i);
        void rebootCartonDegat();

    protected:
        SDL_Surface *m_fond, *m_fondBase, *m_planete[16], *m_menu;
        SDL_Rect m_position, m_sysPlanete, m_placeFond, m_coorObjet[];
        int m_carte[(LARGEUR_MAP / 40) + 1][(HAUTEUR_MAP / 40) + 1];
        int m_spawnPoint[(LARGEUR_MAP / 40) + 1][(HAUTEUR_MAP / 40) + 1];
        int m_cartonDegat[20];
        int m_cartonInfo[20][2];
        FMOD_SOUND * m_musique;
        FMOD_SYSTEM * m_system;
        Environnement m_ent;
        Vaisseau *m_cartonAVaisseaux[20];
        Univers *m_uniPremiereMap;

};

#endif // MAP_H_INCLUDED
