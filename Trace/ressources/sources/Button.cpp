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

#include "Button.h"

Button::Button(int _type, Coordonnees _coor, std::string _name) : Object()
{
    type[0] = _type;
    etat[0] = OFF;
    name = _name;
    position = _coor;
}

Button::~Button()
{
    //dtor
}

bool Button::hover(Input * in)
{
    bool retour = false;

    if(in->mouse(X) < position.w()+position.x()
       && in->mouse(X) >= position.x()
       && in->mouse(Y) < position.h()+position.y()
       && in->mouse(Y) >= position.y())
    {
        retour = true;
    }

    return retour;
}

bool Button::pressed(Input * in)
{
    bool retour = false;

    if(hover(in) && in->get_souris_boutons(0))
    {
        retour = true;
    }

    return retour;
}

void Button::update(Input * in)
{
    etat[0] = (pressed(in)) ? ON : OFF;
}

