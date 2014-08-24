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

#include "Object.h"

using namespace std;

Object::Object() : birth(getTime())
{
    displayDetails = "";
    id = 0;
    type.push_back(0);
    hasMoved = false;
    ancestor = NULL;
    position = Coordonnees(0,0,0,0);
    etat.push_back(TOP);
    alive = true;
    isVisible = true;
    cible = Coordonnees(0,0,1,1);
}

Object::~Object()
{
    //dtor
}
/*********
!!!!!!!!!!!!!!!!!
!!! FIRST VERSION
!!!!!!!!!!!!!!!!!
bool Object::collision(Object * o)
{
    ///Les cotes des rectangles
    int leftA, leftB;
    int rightA, rightB;
    int topA, topB;
    int bottomA, bottomB;
    ///Calcul les cotes du rectangle A
    leftA = this->position.x();
    rightA = this->position.x() + this->position.w();
    topA = this->position.y();
    bottomA = this->position.y() + this->position.h();
    ///Calcul les cotes du rectangle B
    leftB = o->position.x();
    rightB = o->position.x() + o->position.w();
    topB = o->position.y();
    bottomB = o->position.y() + o->position.h();

    ///Tests de collision
    if( bottomA <= topB )
    {
        return false;
    }
    if( topA >= bottomB )
    {
        return false;
    }
    if( rightA <= leftB )
    {
        return false;
    }
    if( leftA >= rightB )
    {
        return false;
    }
    ///Si conditions collision detectee
    return true;
}
******/

void Object::collision(Object * o)
{
    ///Les cotes des rectangles
    int leftA, leftB, rightA, rightB,
        topA, topB, bottomA, bottomB;
    ///Calcul les cotes du rectangle A
    leftA = this->position.x();
    rightA = this->position.x() + this->position.w();
    topA = this->position.y();
    bottomA = this->position.y() + this->position.h();
    ///Calcul les cotes du rectangle B
    leftB = o->position.x();
    rightB = o->position.x() + o->position.w();
    topB = o->position.y();
    bottomB = o->position.y() + o->position.h();

    ///Tests de collision
    if( (bottomA <= topB || topA >= bottomB || rightA <= leftB || leftA >= rightB) == false )
    {
        this->collided(o->collisionPoints());
        o->collided(this->collisionPoints());
    }

    for(int i = 0 ; i < o->sons.size() ; i++)
    {
        this->collision(o->sons[i]);
    }

    for(int i = 0 ; i < sons.size() ; i++)
    {
        sons[i]->collision(o);
    }
}

void Object::bot()
{

}

void Object::update(Input * in)
{

}

bool Object::isAlive()
{
    return alive;
}

vector<DisplayDatas> Object::print()
{
    vector<DisplayDatas> dt;

    dt.push_back(DisplayDatas(type[0],etat[0],position, displayDetails));
    dt.push_back(transitoryEvents());
    for(int i = 0 ; i < sons.size() ; i++)
    {
        vector<DisplayDatas> dt_sons = sons[i]->print();
        for(int j = 0 ; j < dt_sons.size() ; j++)
        {
            dt.push_back(dt_sons[j]);
        }
    }

    return dt;
}

long Object::getTime()
{
    return SDL_GetTicks();
}

void Object::collided(int perte)
{

}

int Object::collisionPoints()
{
    return 5;
}

void Object::setCible(Coordonnees o)
{
    cible = o;
    for (int i = 0 ; i < sons.size() ; i ++){
        sons[i]->setCible(cible);
    }
}

DisplayDatas Object::transitoryEvents()
{
    return DisplayDatas(-1,-1,Coordonnees(0,0,0,0));
}

void Object::setVisible(bool choice)
{
    isVisible = choice;
}

