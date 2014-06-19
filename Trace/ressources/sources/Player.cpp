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

#include "Player.h"

Player::Player(int playa, int x, int y, Object * o) : Object()
{
    ancestor = o;
    type[0] = playa;
    etat[0] = random(0,3);
    position = Coordonnees(x,y,0,0);
    vitesse = 1;
}

Player::~Player()
{
    //dtor
}

void Player::move()
{
    switch(etat[0])
    {
        case BAS:
            position.y(position.y()+(vitesse*12));
            break;
        case HAUT:
            position.y(position.y()-(vitesse*12));
            break;
        case DROITE:
            position.x(position.x()+(vitesse*12));
            break;
        case GAUCHE:
            position.x(position.x()-(vitesse*12));
            break;
        case OFF:
            break;
        case ON:
            break;
    }
}

void Player::update(Input * in)
{
    if(((Map*)ancestor)->get(position.x()/12,position.y()/12) >= 0)
    {
        etat[0] = OFF;
    }
    else
    {
        if(etat[0]==HAUT || etat[0]==BAS)
        {

        }
    }
}

void Player::bot()
{
    if(-1==outOf)
    {
        int change = random(0,100);
        if(change==1){etat[0] = (states) random(0,3);}
    }
    else
    {
        if(outOf==BAS)
            etat[0] = HAUT;
        else if(outOf==HAUT)
            etat[0] = BAS;
        else if(outOf==GAUCHE)
            etat[0] = DROITE;
        else if(outOf==DROITE)
            etat[0] = GAUCHE;
        outOf = -1;
    }
    move();
}

