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

#include "Application.h"

using namespace std;

Application::Application()
{
    /// initialisation son & image
    /// initialisation FMOD
    FMOD_System_Create(&system);

    /// verification de la date
	time(&maintenant);
	Today = *localtime(&maintenant);
    /// initialisation de l'aléatoire
    srand(time(NULL));

	/// create new screen
	screen = new Screen;
	cam = new Camera;

	/// username
    DWORD StrLen = 256;
    TCHAR SysInfoStr[256];
    GetComputerName(SysInfoStr, &StrLen);
    nameComputeur = SysInfoStr;
    GetUserName(SysInfoStr, &StrLen);
    nameUser = SysInfoStr;

    /// Control
    in = new Input();

    /// initialisation image & son
    initialisation();

    /// Icone
    images.at(0)->setAsIcon();

    /// titre
    SDL_WM_SetCaption("Application", NULL);

    /// time
    tempsActuel = 0, tempsPrecedent = 0, screen_refresh = SCREEN_REFRESH;

    /// application states
    state = MENU;
}

Application::~Application()
{
    /// free loaded bitmap and created surface
    delete screen;
    delete cam;
    delete in;
    fermeture();
}

void Application::initialisation()
{
    /// initialise SDL video
    if ( SDL_Init( SDL_INIT_VIDEO ) < 0 )
    {
        printf( "Unable to init SDL: %s\n", SDL_GetError() );
    }

    /// initialise SDL TTF
    TTF_Init();

    /// make sure SDL cleans up before exit
    atexit(SDL_Quit);
    atexit(TTF_Quit);

    /// initialisation de FMOD
    FMOD_System_Init(system, 32, FMOD_INIT_NORMAL, NULL);

    /// initialisation et chargement des ressources
    /// images
    loadImages();
    /// sons
    musiques = NULL;
    musiques = (FMOD_SOUND **) malloc (sizeof(FMOD_SOUND*)*NOMBRE_MUSIQUE);
    loadMusics();
    /// polices
    polices = NULL;
    polices = (TTF_Font **) malloc(sizeof(TTF_Font*) * NOMBRE_POLICE);
    loadFonts();
}

void Application::fermeture()
{
    /// libération des données
    freeImages();
    freeFonts();
    freeMusics();
    freeObjects();

    /// fermeture propre de fmodex
    FMOD_System_Close(system);
    FMOD_System_Release(system);
}


void Application::loadImages()
{
    string lien;
    char a[2];
    for(int i = 0 ; i < NOMBRE_IMAGE ; i++)
    {
        itoa(i,a,10);
        if(i < 10)
        {
            lien = cheminImage + "image0" + a + ".png";
        }
        else
        {
            lien = cheminImage + "image" + a + ".png";
        }

        images.push_back(new Image(lien));
        images[i]->resize((double)(100.0*(SDL_GetVideoSurface()->h)/1080.0));
    }
}

void Application::loadMusics()
{
    string lien;

    for(int i = 0 ; i < NOMBRE_MUSIQUE ; i++)
    {
        lien = cheminSon + "son01.mid";

        FMOD_System_CreateSound(system, lien.c_str(), FMOD_SOFTWARE | FMOD_2D | FMOD_LOOP_NORMAL | FMOD_CREATESTREAM, 0, &musiques[i]);
        FMOD_Sound_SetLoopCount(musiques[i], -1);
    }
}

void Application::loadFonts()
{
    string lien;

    for(int i = 0 ; i < NOMBRE_POLICE ; i++)
    {
        lien = cheminPolice + "calibri.ttf";
        polices[i] = TTF_OpenFont(lien.c_str(), 20);
    }
}


void Application::freeImages()
{
    for(unsigned int i = 0 ; i < images.size() ; i++)
    {
        delete images[i];
    }
}

void Application::freeObjects()
{
    for(unsigned int i = 0 ; i < objects.size() ; i++)
    {
        delete objects[i];
    }
    for(unsigned int i = 0 ; i < interfaces.size() ; i++)
    {
        delete interfaces[i];
    }
}

void Application::freeMusics()
{
    for(int i = 0 ; i < NOMBRE_MUSIQUE ; i++)
    {
        FMOD_Sound_Release(musiques[i]);
    }
    free(musiques);
}

void Application::freeFonts()
{
    for(int i = 0 ; i < NOMBRE_POLICE ; i++)
    {
        TTF_CloseFont(polices[i]);
    }
    free(polices);
}

/// Pour copier une SDL_Surface
SDL_Surface* Application::copieSurface(SDL_Surface *src)
{
    if(src != NULL)
    {
        return SDL_ConvertSurface(src, src->format, SDL_SWSURFACE);
    }
    else
    {
        return NULL;
    }
}

void Application::fps()
{
    tempsActuel = SDL_GetTicks();

    if(tempsActuel - tempsPrecedent >= screen_refresh)
    {
        tempsPrecedent = tempsActuel;
    }
    else if (tempsActuel - tempsPrecedent < screen_refresh)
    {
        SDL_Delay(tempsActuel - tempsPrecedent);
        tempsPrecedent = tempsActuel;
    }
}

void Application::init()
{

}

void Application::run()
{
    this->intro();
    while(!in->get_touche(SDLK_ESCAPE) && !in->get_exit() && state != EXIT)
    {
        state = MENU;
        while(!in->get_touche(SDLK_ESCAPE) && !in->get_exit() && state == MENU)
        {
            this->fps();
            in->update();
            this->menu();
            this->draw();
        }
        this->init();
        /** TEST TIMING **/// int compteurDeTour = 0;
        /** TEST TIMING **/// int timeMemory = SDL_GetTicks();
        while(!in->get_touche(SDLK_ESCAPE) && !in->get_exit() && state == MAIN)
        {
            this->fps();
            in->update();
            this->app();
            this->draw();

        /** TEST TIMING **///     if(SDL_GetTicks()-timeMemory>=1000){cout << "Nombre d'exécution en 1 seconde : " << compteurDeTour+1 << endl; compteurDeTour=0; timeMemory = SDL_GetTicks();}
        /** TEST TIMING **///     else{compteurDeTour++;}
        }
    }
}

void Application::app()
{

}

void Application::menu()
{
    state = MAIN;
}

void Application::intro()
{

}

void Application::draw()
{
    for(unsigned int i = 0 ; i < objects.size() ; i++)
    {
        vector<DisplayDatas> tmps = objects[i]->print();
        for(int j = 0 ; j < tmps.size() ; j++)
        {
            DisplayDatas tmp = tmps[j];

            int numImage = whatImage(tmp.type, tmp.etat);

            if(numImage >= 0)
            {
                Coordonnees relativePlace(tmp.coor);
                relativePlace.x(relativePlace.x()-cam->view().x());
                relativePlace.y(relativePlace.y()-cam->view().y());
                images[numImage]->print(screen->buffer(), (i==0)?cam->place():relativePlace, (i==0)?cam->view():cam->place());
            }
        }
    }

    for(unsigned int i = 0 ; i < interfaces.size() ; i++)
    {
        vector<DisplayDatas> tmps = interfaces[i]->print();
        for(int j = 0 ; j < tmps.size() ; j++)
        {
            DisplayDatas tmp = tmps[j];

            int numImage = whatImage(tmp.type, tmp.etat);

            if(numImage >= 0)
            {
                Coordonnees relativePlace(tmp.coor);
                images[numImage]->print(screen->buffer(), relativePlace);
            }
            else if(numImage == -26)
            {
                Texte * txt = new Texte();
                SDL_Color couleur = {255,255,255};
                vector<Image*> textToPrint = txt->print(tmp.detail,"calibri",20,couleur,tmp.coor.x(),tmp.coor.y());
                for(int k = 0 ; k < textToPrint.size() ; k++)
                {
                    Coordonnees placeToBlitt(tmp.coor.x()+tmp.coor.w()/2-textToPrint[k]->width()/2,tmp.coor.y()+tmp.coor.h()/2-textToPrint[k]->height()/2, textToPrint[k]->width(), textToPrint[k]->height());
                    textToPrint[k]->print(screen->buffer(), placeToBlitt);
                }
                delete txt;
                for(int incr = 0 ; incr < textToPrint.size() ; incr++)
                {
                    delete textToPrint[incr];
                }
            }
        }
    }

    screen->display();
}

void Application::addButton(Button * b)
{
    interfaces.push_back(b);
    buttons.push_back(b);
}

int Application::whatImage(int a, int b)
{

}

