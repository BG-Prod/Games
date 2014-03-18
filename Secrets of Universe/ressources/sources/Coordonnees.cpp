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

    for(int i = 0 ; i < sizeof(tab)/4 ; i++)
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

