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

#include "Shot.h"

Shot::Shot(Object * o) : Object(), lifeTime(1000)
{
    etat = o->getEtat();
    force = 10;
    vitesse = 20;
    ancestor = o;
}

Shot::~Shot()
{

}

void Shot::init()
{

}

void Shot::use()
{

}

void Shot::update()
{
    if(etat==GAUCHE)
    {
        position.x(position.x()-vitesse);
    }
    else if(etat==DROITE)
    {
        position.x(position.x()+vitesse);
    }
    else if(etat==HAUT)
    {
        position.y(position.y()-vitesse);
    }
    else if(etat==BAS)
    {
        position.y(position.y()+vitesse);
    }
}

bool Shot::death()
{
    return false;
    ///return ( SDL_GetTicks() > (unsigned)birth+lifeTime ) ? true : false ;
}




