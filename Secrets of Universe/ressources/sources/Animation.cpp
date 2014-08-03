#include "Animation.h"

Animation::Animation(string link) : Image(link)
{
    nbFrame = 12;
    infinite = false;
    nbPerLine = 3, nbPerColumn = 4;
}

Animation::~Animation()
{
    //dtor
}

void Animation::print(Image * buffer, Coordonnees where, int which)
{
    int frameToPrint = which % nbFrame;
    SDL_Rect ou, dou;
    ou.x = where.x();
    ou.y = where.y();
    ou.w = where.w();
    ou.h = where.h();
    dou.x = (frameToPrint%nbPerLine)*width()/nbPerLine;
    dou.y = (frameToPrint/nbPerLine)*height()/nbPerColumn;
    dou.w = width()/nbPerLine;
    dou.h = height()/nbPerColumn;
    SDL_BlitSurface(image, &dou, buffer->getSurface(), &ou);
}

int Animation::getNbFrame()
{
    return nbFrame;
}

bool Animation::isInfinite()
{
    return infinite;
}

