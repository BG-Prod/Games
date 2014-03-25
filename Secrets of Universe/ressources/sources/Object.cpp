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

Object::Object()
{
    id = 0;
    type = 0;
    hasMoved = false;
    ancestor = NULL;
    position.w(3840);
    position.h(3072);
    etat = HAUT;
}

Object::~Object()
{
    //dtor
}

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

void Object::bot()
{

}

void Object::update(Input * in)
{

}

DisplayDatas Object::print()
{
    return DisplayDatas(type,etat,position);
}

