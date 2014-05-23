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

#include <Coordonnees.h>
#include <DisplayDatas.h>
#include <Input.h>


enum direction{BAS,HAUT,DROITE,GAUCHE};

class Object
{
    public:
        virtual ~Object();

        bool collision(Object * o);
        virtual int collisionPoints();
        virtual void collided(int);
        direction getEtat(){return etat[0];}
        Coordonnees getPosition(){return position;}
        int isOut(Object * o);
        void setOutOf(int dir);    /// 0 : l'objet ne sort pas ; 1,2,3,4 : l'objet sort en bas en haut à droite ou à gauche;
        DisplayDatas print();
        DisplayDatas print(int num);
        virtual void bot();
        virtual void update(Input * in);
        static long getTime();
        bool isAlive();

    protected:
        Object();               /// pour avoir une classe abstraite
        const int birth;
        Coordonnees position;
        int id;
        std::vector<int> type;
        bool hasMoved;
        std::vector<direction> etat;
        Object * ancestor;
        int outOf;
        bool alive;
};


#endif // OBJECT_H
