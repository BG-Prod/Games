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
    /// initialisation image & son
    initialisation();

    /// verification de la date
	time(&maintenant);
	Today = *localtime(&maintenant);

	/// username
    DWORD StrLen = 256;
    TCHAR SysInfoStr[256];
    GetComputerName(SysInfoStr, &StrLen);
    nameComputeur = SysInfoStr;
    GetUserName(SysInfoStr, &StrLen);
    nameUser = SysInfoStr;

    /// déclaration et chargements des ressources
    /// create a new window
    putenv("SDL_VIDEO_WINDOW_POS=center"); /// pour centrer la fenêtre
    screen = SDL_SetVideoMode(LARGEUR_ECRAN, HAUTEUR_ECRAN, 32, SDL_HWSURFACE|SDL_DOUBLEBUF|SDL_RESIZABLE|SDL_FULLSCREEN&&false);
    if ( !screen )
    {
        printf("Unable to set personalized size video: %s\n", SDL_GetError());
        screen = SDL_SetVideoMode(640, 480, 32, SDL_HWSURFACE|SDL_DOUBLEBUF|SDL_RESIZABLE);
    }
    /// images
    loadImages();
    /// sons
    musiques = NULL;
    musiques = (FMOD_SOUND **) malloc (sizeof(FMOD_SOUND*)*NOMBRE_MUSIQUE);
    load_musiques(system, musiques);
    /// polices
    polices = NULL;
    polices = (TTF_Font **) malloc(sizeof(TTF_Font*) * NOMBRE_POLICE);
    load_polices(polices);

    /// Control
    in = new Input();

    /// Icone
    images[0]->setAsIcon();

    /// titre
    SDL_WM_SetCaption("Application", NULL);

    /// time
    tempsActuel = 0, tempsPrecedent = 0, screen_refresh = SCREEN_REFRESH;
}

Application::~Application()
{
    /// free loaded bitmap and created surface
    SDL_FreeSurface(screen);
    delete in;
    freeImages();
    free_polices(polices);
    free_musiques(musiques);
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
}

void Application::fermeture()
{
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
        ///images[i]->resize((double)(100.0*(SDL_GetVideoSurface()->h)/1080.0));
    }
}

void Application::load_musiques(FMOD_SYSTEM * p_system, FMOD_SOUND ** p_musiques)
{
    string lien;

    for(int i = 0 ; i < NOMBRE_MUSIQUE ; i++)
    {
        lien = cheminSon + "son01.mid";

        FMOD_System_CreateSound(p_system, lien.c_str(), FMOD_SOFTWARE | FMOD_2D | FMOD_LOOP_NORMAL | FMOD_CREATESTREAM, 0, &p_musiques[i]);
        FMOD_Sound_SetLoopCount(p_musiques[i], -1);
    }
}

void Application::load_polices(TTF_Font ** p_polices)
{
    string lien;

    for(int i = 0 ; i < NOMBRE_POLICE ; i++)
    {
        lien = cheminPolice + "calibri.ttf";
        p_polices[i] = TTF_OpenFont(lien.c_str(), 20);
    }
}


void Application::freeImages()
{
    for(unsigned int i = 0 ; i < images.size() ; i++)
    {
        delete images[i];
    }
}

void Application::free_musiques(FMOD_SOUND ** p_sons)
{
    for(int i = 0 ; i < NOMBRE_MUSIQUE ; i++)
    {
        FMOD_Sound_Release(p_sons[i]);
    }
    free(p_sons);
}

void Application::free_polices(TTF_Font ** p_polices)
{
    for(int i = 0 ; i < NOMBRE_POLICE ; i++)
    {
        TTF_CloseFont(p_polices[i]);
    }
    free(p_polices);
}

int Application::size_of_game(int p_hauteur_ecran)
{
    int taille = p_hauteur_ecran;
    if(taille == 768){taille = 760;}
    return taille;
}


int Application::nombreLignes (const string & filename)
{
    ifstream fichier(filename.c_str());
    string s;

    if(fichier)
    {
        unsigned int count = 0;
        while(std::getline(fichier,s)) ++count;
        return count;
    }
    else
    {
        std::cout << "Can not open " << filename << std::endl;
    }
    fichier.close();
    return 0;
}

/// attention la ligne suivante renvoie la ligne 1 si on demande la 0
string Application::niemeLigne(const std::string & filename, int p_count)
{
    string ligne;
    ifstream p_fichier(filename.c_str());
    if(p_fichier)
    {
        int i = 0;
        ligne = "";
        bool test = false;
        while(getline(p_fichier, ligne) && !test)
        {
            if(i == p_count)
            {
                test = true;
            }
            i++;
        }
    }
    else
    {
        cout << "Can not open " << filename << endl;
    }
    p_fichier.close();
    return ligne;
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

void Application::resize_screen()
{
    if(in->get_touche(SDLK_F1))
    {
        SDL_SetVideoMode(LARGEUR_ECRAN, HAUTEUR_ECRAN, 32, SDL_HWSURFACE|SDL_DOUBLEBUF|SDL_RESIZABLE|SDL_FULLSCREEN);
    }
    else if(in->get_touche(SDLK_F2))
    {
        SDL_SetVideoMode(LARGEUR_ECRAN, HAUTEUR_ECRAN, 32, SDL_HWSURFACE|SDL_DOUBLEBUF);
    }
}

void Application::app()
{

}


