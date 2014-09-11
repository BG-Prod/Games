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
#include <unordered_map>
#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_image.h>
#include <SDL_rotozoom.h>
#include <fmod.h>
#include <dirent.h>

#ifndef WIN32
    #include <sys/types.h>
#endif

#include <Input.h>
#include <BDD.h>
#include <AnimationManager.h>
#include <Image.h>
#include <Animation.h>
#include <Screen.h>
#include <Object.h>
#include <Texte.h>
#include <Button.h>


#define SCREEN_REFRESH      40
#define DEBUG               std::cerr << std::endl <<


const std::string cheminRessources = "ressources/";
const std::string cheminSon = cheminRessources + "sounds/";
const std::string cheminImage = cheminRessources + "images/";
const std::string cheminFile = cheminRessources + "files/";
const std::string cheminPolice = cheminRessources + "polices/";
const std::string cheminData = cheminRessources + "data/";

enum appStates{GOMENU,MENU,LOADGAME,NEWGAME,MAIN,KINECTMODE,OPTIONS,EXIT};

using namespace std;

class Application
{
    public:
        Application();
        virtual ~Application();

        virtual void init();
        virtual void windowAttributes();
        virtual void intro();
        virtual void menu();
        virtual void app();
        void run();
/*******    Old School
    /**/    void loadImages();      /// charge les images utiles
    /**/    void loadMusics();      /// charge les musiques utiles
    /**/    void loadFonts();       /// charge les polices utiles
/*******/

        void loadRessources(); /// new version with sqlite database for ressources loading

        void freeImages();  /// libère les images chargées
        void freeMusics();   /// libère les musiques chargées
        void freeFonts();   /// libère les polices chargées
        void freeObjects();   /// libère les objets chargées ainsi que les interfaces

        static SDL_Surface* copieSurface(SDL_Surface *surf);
        static long getTime();
        static string itos(long number);
        static double norme(Coordonnees a, Coordonnees b);
        /// getion de dossiers
        DIR * openDirectory(string url);
        void closeDirectory(DIR * directory);
        vector<string> scanDirectory(string url);

        void fps();             /// régule le temps
        void draw();    /// défini l'affichage
        virtual int whatImage(int a, int b);

        void addButton(Button * b);
        void pullButton(int index);

    protected:
        void initialisation();        /// initialise le jeu
        void fermeture();             /// ferme le jeu
        bool mouseOn(Object * o);                 /// la souris est-elle au dessus
        void mouseManager();

        /// time
        int tempsPrecedent, tempsActuel, screen_refresh;
        /// application
        appStates state;
        /// system information
        struct tm Today;
        time_t maintenant;
        string nameComputeur;
        string nameUser;
        /// screen
        Screen * screen;
        Camera * cam;
        /// ressources
        unordered_map<string,Image*> images;
        FMOD_SYSTEM * system;
        vector<FMOD_SOUND *> musiques;
        vector<TTF_Font *> polices;
        /// control
        Input * in;
        /// object
        vector<Object*> objects;
        /// interface
        vector<Interface*> interfaces;
        vector<Button*> buttons;
        AnimationManager * animationManager;

        unsigned int NOMBRE_IMAGE;
        unsigned int NOMBRE_ANIM;
        unsigned int NOMBRE_MUSIQUE;
        unsigned int NOMBRE_POLICE;
};

#endif /// APPLICATION_H
