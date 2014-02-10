/*
    PK Project
    Copyright (C) 2013  BG Prod

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

#include "utile.h"

using namespace std;


void initialisation(FMOD_SYSTEM * p_system)
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
    FMOD_System_Init(p_system, 32, FMOD_INIT_NORMAL, NULL);
}

void fermeture(FMOD_SYSTEM * p_system)
{
    /// fermeture propre de fmodex
    FMOD_System_Close(p_system);
    FMOD_System_Release(p_system);
}


void load_images(SDL_Surface ** p_images)
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

        p_images[i] = SDL_DisplayFormat(IMG_Load(lien.c_str()));

        p_images[i] = rotozoomSurface(p_images[i], 0.0,(double)(SDL_GetVideoSurface()->h/1080.0),1);     /// on utilise la hauteur de la fenêtre et non celle de l'écran
    }
}

void load_musiques(FMOD_SYSTEM * p_system, FMOD_SOUND ** p_musiques)
{
    string lien;

    for(int i = 0 ; i < NOMBRE_MUSIQUE ; i++)
    {
        lien = cheminSon + "son01.mid";
        FMOD_System_CreateSound(p_system, lien.c_str(), FMOD_CREATESAMPLE, 0, &p_musiques[i]);
    }
}

void load_polices(TTF_Font ** p_polices)
{
    string lien;

    for(int i = 0 ; i < NOMBRE_POLICE ; i++)
    {
        lien = cheminPolice + "calibri.ttf";
        p_polices[i] = TTF_OpenFont(lien.c_str(), 20);
    }
}


void free_images(SDL_Surface ** p_images)
{
    for(int i = 0 ; i < NOMBRE_IMAGE ; i++)
    {
        SDL_FreeSurface(p_images[i]);
    }
    free(p_images);
}

void free_musiques(FMOD_SOUND ** p_sons)
{
    for(int i = 0 ; i < NOMBRE_MUSIQUE ; i++)
    {
        FMOD_Sound_Release(p_sons[i]);
    }
    free(p_sons);
}

void free_polices(TTF_Font ** p_polices)
{
    for(int i = 0 ; i < NOMBRE_POLICE ; i++)
    {
        TTF_CloseFont(p_polices[i]);
    }
    free(p_polices);
}

int size_of_game(int p_hauteur_ecran)
{
    int taille = p_hauteur_ecran;
    if(taille == 768){taille = 760;}
    return taille;
}


int nombreLignes (const string & filename)
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
string niemeLigne(const std::string & filename, int p_count)
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
SDL_Surface* copieSurface(SDL_Surface *src)
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

void fps(int * tempsPrecedent, int * tempsActuel, int screen_refresh)
{
    *tempsActuel = SDL_GetTicks();

    if(*tempsActuel - *tempsPrecedent >= screen_refresh)
    {
        *tempsPrecedent = *tempsActuel;
    }
    else if (*tempsActuel - *tempsPrecedent < screen_refresh)
    {
        SDL_Delay(*tempsActuel - *tempsPrecedent);
        *tempsPrecedent = *tempsActuel;
    }
}

void resize_screen(Input in)
{
    if(in.get_touche(SDLK_F1))
    {
        SDL_SetVideoMode(LARGEUR_ECRAN, HAUTEUR_ECRAN, 32, SDL_HWSURFACE|SDL_DOUBLEBUF|SDL_RESIZABLE|SDL_FULLSCREEN);
    }
    if(in.get_touche(SDLK_F2))
    {
        SDL_SetVideoMode(LARGEUR_ECRAN, HAUTEUR_ECRAN, 32, SDL_HWSURFACE|SDL_DOUBLEBUF);
    }
}
