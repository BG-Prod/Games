#include "ColorSurvivor.h"

ColorSurvivor::ColorSurvivor() : Application()
{
    SDL_WM_SetCaption("Color Survivor", NULL);
    if(screen!=NULL)
    {
        delete screen;
        screen = new Screen(512,512);
    }
}

ColorSurvivor::~ColorSurvivor()
{
    //dtor
}

void ColorSurvivor::init()
{
    images.push_back(new Image(cheminImage+"lena.png"));
    objects.push_back(new Object());
    images[1]->toBlackAndWhite();
    images[1]->turn90();
    images[1]->line(0,0,400,300, 0xFFFF);
}

void ColorSurvivor::app()
{

}

int ColorSurvivor::whatImage(int a, int b)
{
    return 1;
}

