#ifndef HATAK_H_INCLUDED
#define HATAK_H_INCLUDED

#include "Vaisseau.h"

class Hatak : public Vaisseau
{
    public:
    Hatak(SDL_Rect);
    Hatak(const Hatak&);
    ~Hatak();

    private:
};

#endif // HATAK_H_INCLUDED
