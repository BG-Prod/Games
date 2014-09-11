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
    vitesse = 50;
    ancestor = o;
    cible = o->getCible();
    alive = true;
    if(etat[0]==LEFT)
    {
        movX = -vitesse;
    }
    else if(etat[0]==RIGHT)
    {
        movX = vitesse;
    }
    else if(etat[0]==TOP)
    {
        movY = -vitesse;
    }
    else if(etat[0]==BOTTOM)
    {
        movY = vitesse;
    }
    init();
}

Shot::~Shot()
{

}

void Shot::init()
{
    /**
    *** On déplace proportionnellement à la distance à parcourir le vaisseau sur les deux axes.
    *** Ensuite on signale si on a bougé
    **/
    Coordonnees pos = Coordonnees(position.x()+position.w()/2, position.y()+position.h()/2, position.w(), position.h());
    int vecX = cible.x()-pos.x();
    int vecY = cible.y()-pos.y();
    int base = abs(vecX)+abs(vecY);
    if(base > vitesse) {
        movX = vitesse*vecX/base;
        movY = vitesse*vecY/base;
        etat[0] = (abs(movX)>abs(movY)) ? (movX>0 ? RIGHT : LEFT) : (movY>0 ? BOTTOM : TOP);
    }
}

void Shot::use()
{
    /**
    *** On déplace proportionnellement à la distance à parcourir le vaisseau sur les deux axes.
    *** Ensuite on signale si on a bougé
    **/
    position.x(position.x()+movX);
    position.y(position.y()+movY);
    hasMoved = true;
}

void Shot::update()
{
    use();
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


