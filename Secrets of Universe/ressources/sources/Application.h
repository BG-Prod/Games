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

#ifndef APPLICATION_H
#define APPLICATION_H

#include <cstdlib>
#include <stdlib.h>
#include <stdio.h>
#include <fstream>
#include <string>
#include <sstream>
#include <iostream>
#include <vector>
#include <windows.h>
#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_image.h>
#include <SDL_rotozoom.h>
#include <FMOD/fmod.h>

#include "Input.h"
#include "Image.h"

#define CX_SCREEN           GetSystemMetrics(SM_CXSCREEN)            ///Largeur
#define CY_SCREEN           GetSystemMetrics(SM_CYSCREEN)            ///Hauteur
#define NB_CARRE_X          10
#define NB_CARRE_Y          10
#define TAILLE_CARRE        HAUTEUR_ECRAN / 10
#define LARGEUR_ECRAN       CX_SCREEN                   ///     800     ///  1366    ///  1920
#define HAUTEUR_ECRAN       size_of_game(CY_SCREEN)     ///     600     ///  768     ///  1080
#define RESIZE              HAUTEUR_ECRAN/1080.0
#define SCREEN_REFRESH      40
#define DEBUG               std::cerr << std::endl <<
#define NOMBRE_IMAGE        7
#define NOMBRE_MUSIQUE      1
#define NOMBRE_POLICE       0



const std::string cheminRessources = "ressources/";
const std::string cheminSon = cheminRessources + "sons/";
const std::string cheminImage = cheminRessources + "images/";
const std::string cheminFile = cheminRessources + "fichiers/";
const std::string cheminPolice = cheminRessources + "polices/";
const std::string cheminData = cheminRessources + "datas/";


class Application
{
    public:
        Application();
        virtual ~Application();

        virtual void app();

        void loadImages();                          /// charge les images utiles
        void load_musiques(FMOD_SYSTEM * p_system, FMOD_SOUND ** p_sons);   /// charge les musiques utiles
        void load_polices(TTF_Font ** p_polices);                           /// charge les polices utiles

        void freeImages();  /// libère les images chargées
        void free_musiques(FMOD_SOUND ** p_sons);   /// libère les musiques chargées
        void free_polices(TTF_Font ** p_polices);   /// libère les polices chargées

        static SDL_Surface* copieSurface(SDL_Surface *surf);

        void fps();      /// régule le temps
        void resize_screen();       /// change la taille de l'écran

        std::vector<Image*> images;

    protected:
        void initialisation();        /// initialise le jeu
        void fermeture();             /// ferme le jeu
        int size_of_game(int p_hauteur_ecran);        /// détermine la hauteur de l'écran
        int nombreLignes (const std::string & filename);
        std::string niemeLigne(const std::string & filename, int p_count);/// attention la ligne suivante renvoie la ligne 1 si on demande la 0



        /// time
        int tempsPrecedent, tempsActuel, screen_refresh;
        /// system information
        struct tm Today;
        time_t maintenant;
        std::string nameComputeur;
        std::string nameUser;
        /// screen
        SDL_Surface* screen;
        /// ressources
        FMOD_SYSTEM * system;
        FMOD_SOUND ** musiques;
        TTF_Font ** polices;
        /// control
        Input * in;
};

#endif // APPLICATION_H
