#include "ColorSurvivor.h"

using namespace std;

ColorSurvivor::ColorSurvivor() : Application()
{
    SDL_WM_SetCaption("Color Survivor", NULL);
    myCam = new Webcam();
    if(screen!=NULL)
    {
        delete screen;
        screen = new Screen(myCam->width()*2,myCam->height());
    }
}

ColorSurvivor::~ColorSurvivor()
{
    delete myCam;
}

void ColorSurvivor::init()
{
    images.push_back(new Image(cheminImage+"lena.png"));
    images.push_back(myCam->getFrame());
    objects.push_back(new Object);
    objects.push_back(new Object(640,0));
    delete images[1];
    images[1] = myCam->getFrame();
    images[2]->toGreyLevels();
    images[1]->toGreyLevels();

    for(int i = 1 ; i < 639 ; i++) {
        for(int j = 1 ; j < 479 ; j++) {
            images[2]->setPixel(i,j,
                (images[1]->getPixelRGBA(i,j)[1]*4
                -images[1]->getPixelRGBA(i+1,j+1)[1]
                -images[1]->getPixelRGBA(i-1,j-1)[1]
                -images[1]->getPixelRGBA(i+1,j-1)[1]
                -images[1]->getPixelRGBA(i-1,j+1)[1]
                -images[1]->getPixelRGBA(i+1,j)[1]*2
                -images[1]->getPixelRGBA(i-1,j)[1]*2
                -images[1]->getPixelRGBA(i,j+1)[1]*2
                -images[1]->getPixelRGBA(i,j-1)[1]*2)/16
            );
        }
    }

    for(int i = 1 ; i < 639 ; i++) {
        for(int j = 1 ; j < 479 ; j++) {
            images[1]->setPixel(i,j,
                (images[2]->getPixelRGBA(i,j)[1])*8
                -images[2]->getPixelRGBA(i+1,j+1)[1]
                -images[2]->getPixelRGBA(i-1,j-1)[1]
                -images[2]->getPixelRGBA(i+1,j-1)[1]
                -images[2]->getPixelRGBA(i-1,j+1)[1]
                -images[2]->getPixelRGBA(i+1,j)[1]
                -images[2]->getPixelRGBA(i-1,j)[1]
                -images[2]->getPixelRGBA(i,j+1)[1]
                -images[2]->getPixelRGBA(i,j-1)[1]
            );
        }
    }
}

void ColorSurvivor::app()
{



/*
    if(in->get_souris_boutons(1))
    {
        coloration(in->mouse(X),in->mouse(Y),color(255,0,0));
    }*/
}

int ColorSurvivor::whatImage(int a, int b)
{
    return 1+a;
}

void ColorSurvivor::coloration(int x, int y, Uint32 color)
{
    if(images[1]->getPixel(x,y)==0)
    {
        images[1]->setPixel(abs(x),abs(y),color);
        coloration(abs(x+1),abs(y),color);
        coloration(abs(x-1),abs(y),color);
        coloration(abs(x),abs(y+1),color);
        coloration(abs(x),abs(y-1),color);
    }
}

