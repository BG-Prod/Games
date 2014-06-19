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

#include "Map.h"

using namespace std;

Map::Map(int w, int h, int _type) : Object()
{
    id = 0;
    type[0] = (_type);
    hasMoved = false;
    ancestor = NULL;
    position = Coordonnees(0,0,w,h);
    etat[0] = HAUT;

    nbCasesH = 40;
    nbCasesW = 55;
    for(int i = 0 ; i < nbCasesH ; i++)
    {
        for(int j = 0 ; j < nbCasesW ; j++)
        {
            field[i][j] = -1;
        }
    }
}

Map::~Map()
{
    //dtor
}

void Map::update(Input * in)
{

}

void Map::bot()
{

}

