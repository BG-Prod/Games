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

#include "Coordonnees.h"

Coordonnees::Coordonnees()
{
    for(int i = 0 ; i < 8 ; ++i)
    {
        data[i] = 0;
    }
}

Coordonnees::Coordonnees(int a, int b, int c, int d, int e, int f, int g, int h)
{
    data[4] = e;
    data[5] = f;
    data[6] = g;
    data[7] = h;

    data[0] = a;
    data[1] = b;
    data[2] = c;
    data[3] = d;
}

Coordonnees::Coordonnees(int a, int b, int c, int d)
{
    data[4] = a;
    data[5] = b;
    data[6] = c;
    data[7] = d;

    data[0] = a;
    data[1] = b;
    data[2] = c;
    data[3] = d;
}

Coordonnees::~Coordonnees()
{
    //dtor
}

Coordonnees &Coordonnees::operator=(const Coordonnees & coor)
{
    for(int i = 0 ; i < 8 ; i++)
    {
        data[i] = coor.data[i];
    }

    return *this;
}

Coordonnees &Coordonnees::operator+=(const Coordonnees & coor)
{
    for(int i = 0 ; i < 4 ; i++)
    {
        data[i+4] = data[i];
        data[i] += coor.data[i];
    }

    return *this;
}

Coordonnees &Coordonnees::operator=(const int tab[])
{
    std::cout << (sizeof(tab));
    if(sizeof(tab)/4 < 5)
    {
        for(int i = 0 ; i < 4 ; i++)
        {
            data[i+4] = data[i];
        }
    }

    for(unsigned int i = 0 ; i < sizeof(tab)/4 ; i++)
    {
        data[i] = tab[i];
    }

    return *this;
}

void Coordonnees::modify(int a, int b, int c, int d)
{
    data[4] = data[0];
    data[5] = data[1];
    data[6] = data[2];
    data[7] = data[3];

    data[0] = a != -1 ? a : data[0];
    data[1] = b != -1 ? b : data[1];
    data[2] = c != -1 ? c : data[2];
    data[3] = d != -1 ? d : data[3];
}

long random(int borneInf, int borneSup)  /// borne sup inclus
{
    return ((rand() % (borneSup + 1 - borneInf)) + borneInf);
}

