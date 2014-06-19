/*
    Trace
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


enum states{BAS,HAUT,DROITE,GAUCHE,ON,OFF};
enum types{BUTTON1,BUTTON2,STARSHIP1,STARSHIP2,SHOT1,SHOT2,BOARD1,SPACE_MAP_1};

class Object
{
    public:
        virtual ~Object();

        bool collision(Object * o);
        virtual int collisionPoints();
        virtual void collided(int);
        int getEtat(){return etat[0];}
        Coordonnees getPosition(){return position;}
        int isOut(Object * o);
        void setOutOf(int dir);    /// 0 : l'objet ne sort pas ; 1,2,3,4 : l'objet sort en bas en haut à droite ou à gauche;
        std::vector<DisplayDatas> print();
        int numberToPrint(){return etat.size();}
        virtual void bot();
        virtual void update(Input * in);
        long getTime();
        bool isAlive();

    protected:
        Object();               /// pour avoir une classe abstraite
        const int birth;
        Coordonnees position;
        int id;
        std::vector<int> type;
        std::vector<Object*> sons;
        bool hasMoved;
        std::vector<int> etat;
        Object * ancestor;
        int outOf;
        bool alive;
};


#endif // OBJECT_H
