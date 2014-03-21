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

#include "Weapon.h"

Weapon::Weapon(Object * o) : Object()
{
    type = 1;
    etat = o->getEtat();
    ancestor = o;
}

Weapon::~Weapon()
{
    //dtor
}

void Weapon::init()
{

}

void Weapon::use()
{
    etat = ancestor->getEtat();
    salve.push_back(new Shot(this));
}

void Weapon::update()
{
    for(unsigned int i = 0 ; i < salve.size() ; ++i)
    {
        if(salve[i]->death())
        {
            delete salve[i];
            salve.erase(salve.begin()+i);
        }
        else
        {
            salve[i]->update();
        }
    }
    for(unsigned int i = 0 ; i < salve.size() ; ++i)
    {
        salve[i]->print();
    }
}


