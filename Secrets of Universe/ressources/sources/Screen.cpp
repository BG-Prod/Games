#include "Screen.h"

Screen::Screen()
{
    /// create a new window
    putenv("SDL_VIDEO_WINDOW_POS=center"); /// pour centrer la fenêtre
    ecran = SDL_SetVideoMode(LARGEUR_ECRAN, HAUTEUR_ECRAN, 32, SDL_HWSURFACE|SDL_DOUBLEBUF|SDL_RESIZABLE|SDL_FULLSCREEN&&false);
    if ( !ecran )
    {
        printf("Unable to set personalized size video: %s\n", SDL_GetError());
        ecran = SDL_SetVideoMode(640, 480, 32, SDL_HWSURFACE|SDL_DOUBLEBUF|SDL_RESIZABLE);
    }

    videoBuffer = new Image(1920,1080,0,255,0);
    ///videoBuffer->setAsScreen();
    cam = new Camera;
}

Screen::~Screen()
{
    delete videoBuffer;
    delete cam;
    SDL_FreeSurface(ecran);
}

void Screen::resize()
{
    if(ecran->flags & SDL_FULLSCREEN)
    {
        windowed();
    }
    else
    {
        fullScreen();
    }
}

void Screen::fullScreen()
{
    SDL_SetVideoMode(LARGEUR_ECRAN, HAUTEUR_ECRAN, 32, SDL_HWSURFACE|SDL_DOUBLEBUF|SDL_RESIZABLE|SDL_FULLSCREEN);
}

void Screen::windowed()
{
    SDL_SetVideoMode(LARGEUR_ECRAN, HAUTEUR_ECRAN, 32, SDL_HWSURFACE|SDL_DOUBLEBUF|SDL_RESIZABLE);
}

int Screen::size_of_window(int p_hauteur_ecran)
{
    return 10*(p_hauteur_ecran/10);
}

void Screen::display()
{
   // videoBuffer->print(cam->place(), cam->view());
  //  videoBuffer->clear();
    SDL_Rect endroit = {0,0,1920,1080};
    SDL_Rect partie = {0,0,1920,1080};
    SDL_BlitSurface(ecran, &partie, SDL_GetVideoSurface(), &endroit);
    SDL_Flip(ecran);
}

