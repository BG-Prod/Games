#include "ColorSurvivor.h"

ColorSurvivor::ColorSurvivor() : Application()
{
    SDL_WM_SetCaption("Color Survivor", NULL);
    if(screen!=NULL)
    {
        delete screen;
        screen = new Screen(640,480);
    }
}

ColorSurvivor::~ColorSurvivor()
{
    //dtor
}

void ColorSurvivor::init()
{
    images.push_back(new Image(640,480, 0,0,0));
    objects.push_back(new Object());
}

void ColorSurvivor::app()
{
    bool verif[480][640] = {false};
    for(int i = 0 ; i < 640 ; i++)
    {
        for(int j = 0 ; j < 480 ; j++)
        {
            verif[j][i]= (images[1]->getPixel(i-1,j-1)!=0 ||
               images[1]->getPixel(i,j-1)!=0 ||
               images[1]->getPixel(i+1,j-1)!=0 ||
               images[1]->getPixel(i-1,j+1)!=0 ||
               images[1]->getPixel(i,j+1)!=0 ||
               images[1]->getPixel(i+1,j+1)!=0 ||
               images[1]->getPixel(i-1,j)!=0 ||
               images[1]->getPixel(i+1,j)!=0);
        }
    }


    for(int i = 0 ; i < 640 ; i++)
    {
        for(int j = 0 ; j < 480 ; j++)
        {
            if(verif[j][i])
                images[1]->setPixel(i,j,color(255*(i+j)/(640+480),255*i/640,255*j/480));
        }
    }

    for(int i = 0 ; i < 4 ; i++)
    {
        images[1]->setPixel(random(0,639),random(0,479),color(random(240,255),5,5));
    }
    images[1]->circle(random(0,639),random(0,479),64,0xFFFFFFFF);

    images[1]->line(random(0,639),random(0,479),random(0,639),random(0,479),random(0xFF000000,0xFFFFFFFF));
}

int ColorSurvivor::whatImage(int a, int b)
{
    return 1;
}

