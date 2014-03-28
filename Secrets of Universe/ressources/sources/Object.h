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

#ifndef OBJECT_H
#define OBJECT_H


#include <vector>

#include <Image.h>
#include <Coordonnees.h>
#include <DisplayDatas.h>
#include <Input.h>


enum direction{BAS,HAUT,DROITE,GAUCHE};

class Object
{
    public:
        virtual ~Object();

        bool collision(Object * o);
        direction getEtat(){return etat;}
        Coordonnees getPosition(){return position;}
        DisplayDatas print();
        virtual void bot();
        virtual void update(Input * in);
        static long getTime();

    protected:
        Object();               /// pour avoir une classe abstraite
        const int birth;
        Coordonnees position;
        int id;
        int type;
        bool hasMoved;
        direction etat;
        Object * ancestor;
};


#endif // OBJECT_H
