/*
    Secrets of Universe
    Copyright (C) 2014  BG Prod

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.

    Contact me : bgprod@outlook.com
*/

#ifndef VAISSEAU_H_INCLUDED
#define VAISSEAU_H_INCLUDED


#include <SDL.h>
#include <SDL_image.h>
#include <FMOD/fmod.h>
#include <iostream>
#include <vector>

#include <Image.h>
#include <Application.h>

enum direction{BAS,HAUT,DROITE,GAUCHE};

class Vaisseau
{
    public:
        Vaisseau();
       /// Vaisseau(const Vaisseau&);
        virtual ~Vaisseau();
       /** void attaquer(SDL_Surface* p_ouColler, Input, SDL_Rect p_carton[],int p_listeDeg[]);
        void bouclier(SDL_Surface *, Input);
        void update(SDL_Surface*, SDL_Surface*, Input, SDL_Rect p_carton[],int p_listeDeg[]);
        void IA(SDL_Surface*, Input, SDL_Rect p_carton[],int p_listeDeg[]);
        int modCoque(int mod);
        Projectile getTirs(int);
        SDL_Rect getPos();
        int getActiviteArme();
        int getParametre(int x);
        void anim_explosion(SDL_Surface * p_ou);**/

        void move(direction d);
        void print();
        void destroy();
        void resize(int);
        void init(SDL_Surface**);

    protected:
        int energie, bouclier, coque, capteur;
        int teleporteur, hypernavigateur, moteur, nb_explosion;
        ///Arme *batterie;
        std::vector<Image*> image;
        SDL_Surface* imageBouclier[5], *explosion;
        SDL_Rect placeBouclier, placeArme1;
        bool activiteBouclier, bool_explosion;
        bool mobile;
        int vitesse, etat, joueur;
        SDL_Rect position;
        bool alive;
        int type, masse;

};

#endif // VAISSEAU_H_INCLUDED
