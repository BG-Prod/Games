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


enum states{BOTTOM,TOP,RIGHT,LEFT,ON,OFF,DISABLED};
enum types{BUTTON0,BUTTON1,BUTTON2,BUTTON3,BUTTON4,BUTTON5,TEXT1,TEXT2,WALLPAPER0,WALLPAPER1,STARSHIP1,STARSHIP2,SHOT1,SHOT2,
EXPLOSION0,EXPLOSION1,BOARD1,SPACE_MAP_1,POPUP};

class Object
{
    public:
        virtual ~Object();

        void collision(Object * o);
        virtual int collisionPoints();
        virtual void collided(int);
        int getEtat(){return etat[0];}
        Coordonnees getPosition(){return position;}
        virtual std::vector<DisplayDatas> print();
        int numberToPrint(){return etat.size();}
        virtual void bot();
        virtual void update(Input * in);
        long getTime();
        bool isAlive();
        void setCible(Coordonnees o);
        Coordonnees getCible(){return cible;}
        virtual DisplayDatas transitoryEvents();

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
        bool alive;
        Coordonnees cible;
        std::string name, displayDetails;
};


#endif // OBJECT_H
