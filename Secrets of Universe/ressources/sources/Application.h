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
#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_image.h>
#include <SDL_rotozoom.h>
#include <fmod.h>

#include <Input.h>
#include <Image.h>
#include <Screen.h>
#include <Object.h>



#define SCREEN_REFRESH      40
#define DEBUG               std::cerr << std::endl <<
#define NOMBRE_IMAGE        11
#define NOMBRE_MUSIQUE      1
#define NOMBRE_POLICE       0


const std::string cheminRessources = "ressources/";
const std::string cheminSon = cheminRessources + "sounds/";
const std::string cheminImage = cheminRessources + "images/";
const std::string cheminFile = cheminRessources + "files/";
const std::string cheminPolice = cheminRessources + "polices/";
const std::string cheminData = cheminRessources + "data/";


class Application
{
    public:
        Application();
        virtual ~Application();

        virtual void init();
        virtual void app();
        void run();

        void loadImages();                          /// charge les images utiles
        void loadMusics();   /// charge les musiques utiles
        void loadFonts();                           /// charge les polices utiles

        void freeImages();  /// libère les images chargées
        void freeMusics();   /// libère les musiques chargées
        void freeFonts();   /// libère les polices chargées
        void freeObjects();   /// libère les objets chargées

        static SDL_Surface* copieSurface(SDL_Surface *surf);
        static long getTime();

        void fps();             /// régule le temps
        void draw();    /// défini l'affichage
        virtual int whatImage(int a, int b);

    protected:
        void initialisation();        /// initialise le jeu
        void fermeture();             /// ferme le jeu

        /// time
        int tempsPrecedent, tempsActuel, screen_refresh;
        /// system information
        struct tm Today;
        time_t maintenant;
        std::string nameComputeur;
        std::string nameUser;
        /// screen
        Screen * screen;
        Camera * cam;
        /// ressources
        std::vector<Image*> images;
        FMOD_SYSTEM * system;
        FMOD_SOUND ** musiques;
        TTF_Font ** polices;
        /// control
        Input * in;
        /// object
        std::vector<Object*> objects;
        /// interface
        std::vector<Object*> interfaces;
};

#endif /// APPLICATION_H
