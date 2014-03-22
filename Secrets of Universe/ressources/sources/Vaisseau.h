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
#include <fmod.h>
#include <iostream>
#include <vector>

#include <Object.h>
#include <Image.h>
#include <Weapon.h>
#include <DisplayDatas.h>


class Vaisseau : public Object
{
    public:
        Vaisseau();
        /// constructeur de badass
        Vaisseau(int _energie, int _bouclier, int _coque, int _capteur, int _vitesse, int _joueur, int _type,
                 int _masse, int _teleporteur, int _hypernavigateur, int _moteur, int _id, Coordonnees _position,
                 direction _etat, Object * _ancestor);
        virtual ~Vaisseau();

        void move(direction d);
        void destroy();
        void bot();
        void shoot();
        void update(Input * in);

    protected:
        int energie, bouclier, coque, capteur, vitesse, joueur,
        masse, teleporteur, hypernavigateur, moteur;
        bool activiteBouclier, alive;
        Weapon * batterie;

};

#endif // VAISSEAU_H_INCLUDED
