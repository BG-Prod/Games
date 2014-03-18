#ifndef COORDONNEES_H
#define COORDONNEES_H

#include <iostream>

class Coordonnees
{
    public:
        Coordonnees();
        Coordonnees(int a, int b, int c, int d, int e, int f, int g, int h);
        virtual ~Coordonnees();
        Coordonnees &operator=(const Coordonnees &);
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
