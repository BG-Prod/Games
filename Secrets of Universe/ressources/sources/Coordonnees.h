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

#ifndef COORDONNEES_H
#define COORDONNEES_H

#include <iostream>
#include <cstdlib>
#include <stdlib.h>
#include <stdio.h>

long random(int borneInf, int borneSup);  /// borne sup inclus

class Coordonnees
{
    public:
        Coordonnees();
        Coordonnees(int a, int b, int c, int d, int e, int f, int g, int h);
        Coordonnees(int a, int b, int c, int d);
        virtual ~Coordonnees();
        Coordonnees &operator=(const Coordonnees &);
        Coordonnees &operator+=(const Coordonnees &);
        Coordonnees &operator=(const int[]);

        void modify(int,int,int,int);
        int x(){return data[0];}
        int y(){return data[1];}
        int w(){return data[2];}
        int h(){return data[3];}
        void x(int a){data[4] = data[0]; data[0] = a; }
        void y(int a){data[5] = data[1]; data[1] = a; }
        void w(int a){data[6] = data[2]; data[2] = a; }
        void h(int a){data[7] = data[3]; data[3] = a; }
        int px(){return data[4];}
        int py(){return data[5];}
        int pw(){return data[6];}
        int ph(){return data[7];}

    private:
        int data[8];
};

#endif /// COORDONNEES_H
