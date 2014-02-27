#ifndef INPUT_H
#define INPUT_H


#include <cstdlib>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <fstream>
#include <string>
#include <sstream>
#include <iostream>
#include <windows.h>
#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_image.h>
#include <SDL_rotozoom.h>
#include <SDL_getenv.h>
#include <FMOD/fmod.h>
#include <ctime>


#define X                   0
#define Y                   1
#define X_REEL              2
#define Y_REEL              3


class Input
{
    public:
        Input();
        virtual ~Input();

        void update();
        /// getter
        char get_touche(int i){return touche[i];}
        char get_souris_boutons(int i){return souris_boutons[i];}
        char get_exit(){return exit;}
        int get_souris(int i){return souris[i];}
        /// setter
        void set_touche(int i, int valeur){touche[i] = valeur;}
        void set_souris_boutons(int i, int valeur){souris_boutons[i] = valeur;}
        void set_exit(int valeur){exit = valeur;}
        void set_souris(int i, int valeur){souris[i] = valeur;}

        /// saisie
        void activerSaisie();
        std::string str();
        void getSaisie();
        void desactiverSaisie();
        bool modeSaisie();

    protected:
    private:
        char touche[SDLK_LAST], souris_boutons[8], exit;
        int souris[4];
        std::string m_str;
        bool saisieActive;
};

#endif // INPUT_H
