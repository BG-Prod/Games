#ifndef BC304_H_INCLUDED
#define BC304_H_INCLUDED


#include <SDL_image.h>


#include "Vaisseau.h"

class BC304 : public Vaisseau
{
    public:
    BC304(SDL_Surface ** p_images);
    BC304(const BC304&);
    ~BC304();

    private:
};

#endif // BC304_H_INCLUDED
