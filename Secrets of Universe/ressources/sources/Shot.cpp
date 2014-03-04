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

Shot::Shot(Object * o) : Object(), birth(SDL_GetTicks()), lifeTime(1000)
{
    etat = o->getEtat();
    force = 10;
    vitesse = 20;
    ancestor = o;
    biblio = o->biblio;
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
    oldPosition = position;

    if(etat==GAUCHE)
    {
        position.x -= vitesse;
    }
    else if(etat==DROITE)
    {
        position.x += vitesse;
    }
    else if(etat==HAUT)
    {
        position.y -= vitesse;
    }
    else if(etat==BAS)
    {
        position.y += vitesse;
    }
}

bool Shot::death()
{
    return ( SDL_GetTicks() > birth+lifeTime ) ? true : false ;
}

void Shot::print()
{
    biblio[0][6]->print(position.x,position.y);
}


