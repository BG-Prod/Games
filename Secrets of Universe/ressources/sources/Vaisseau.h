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
        Vaisseau(int,int); /// pour placer où on veut
        Vaisseau(int _type, int x, int y);
        /// constructeur de badass
        Vaisseau(int _energie, int _bouclier, int _coque, int _capteur, int _vitesse, int _joueur, int _type,
                 int _masse, int _teleporteur, int _hypernavigateur, int _moteur, int _id, int _pib, Coordonnees _position,
                 states _etat, Weapon * _arme, string _displayDetails, Object * _ancestor);
        virtual ~Vaisseau();

        void move();
        void destroy();
        void bot();
        void shoot();
        void update(Input * in);
        void collided(int);
        int collisionPoints();
        void switchShield();
        DisplayDatas transitoryEvents();
        void clearRadar();
        void addEchoRadar(Coordonnees c);
        int getCapteur();

    protected:
        int weaponTarget = 0;
        int energie, bouclier, coque, capteur, vitesse, joueur,
        masse, teleporteur, hypernavigateur, moteur, pib;
        bool activiteBouclier, touched;
        Weapon * batterie;
        vector<Coordonnees> radar;
};

#endif /// VAISSEAU_H_INCLUDED
