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

Shot::Shot(Object * o) : Object(), lifeTime(2500)
{
    etat[0] = o->getEtat();
    position = o->getPosition();
    position.w(12);
    position.h(12);
    type[0] = SHOT1;
    force = 10;
    vitesse = 20;
    ancestor = o;
    cible = o->getCible();
    alive = true;
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
/*******************************************
!!!!!!!!!!! VERSION 1.0 !!!!!!!!!!!!!!!!!!!!
void Shot::update()
{
    if(etat[0]==GAUCHE)
    {
        position.x(position.x()-vitesse);
    }
    else if(etat[0]==DROITE)
    {
        position.x(position.x()+vitesse);
    }
    else if(etat[0]==HAUT)
    {
        position.y(position.y()-vitesse);
    }
    else if(etat[0]==BAS)
    {
        position.y(position.y()+vitesse);
    }
}
!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
*******************************************/

void Shot::update()
{
    if(cible != NULL && cible != this) {
        int vecX = ((cible->getPosition()).x())-(position.x());
        int vecY = ((cible->getPosition()).y())-(position.y());
        int base = abs(vecX)+abs(vecY);
        if(base != 0) {
            int movX = vitesse*vecX/base;
            int movY = vitesse*vecY/base;
            position.x(position.x()+movX);
            position.y(position.y()+movY);
        }
    }
    else {
        if(etat[0]==GAUCHE)
        {
            position.x(position.x()-vitesse);
        }
        else if(etat[0]==DROITE)
        {
            position.x(position.x()+vitesse);
        }
        else if(etat[0]==HAUT)
        {
            position.y(position.y()-vitesse);
        }
        else if(etat[0]==BAS)
        {
            position.y(position.y()+vitesse);
        }
    }

    alive &= (SDL_GetTicks() < (unsigned)birth+lifeTime);
}

int Shot::collisionPoints()
{
    return force;
}

void Shot::collided(int perte)
{
    alive = false;
}


