#ifndef UTILE_H_INCLUDED
#define UTILE_H_INCLUDED



#include <cstdlib>
#include <stdlib.h>
#include <stdio.h>
#include <fstream>
#include <string>
#include <sstream>
#include <iostream>
#include <windows.h>
#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_image.h>
#include <FMOD/fmod.h>



#define CX_SCREEN           GetSystemMetrics(SM_CXSCREEN)            ///Largeur
#define CY_SCREEN           GetSystemMetrics(SM_CYSCREEN)            ///Hauteur
#define NB_CARRE_X          10
#define NB_CARRE_Y          10
#define TAILLE_CARRE        HAUTEUR_ECRAN / 10
#define LARGEUR_ECRAN       CX_SCREEN                   ///     800     ///  1366    ///  1920
#define HAUTEUR_ECRAN       size_of_game(CY_SCREEN)     ///     600     ///  768     ///  1080
#define SCREEN_REFRESH      40
#define DEBUG               std::cerr << std::endl <<
#define NOMBRE_IMAGE        7
#define NOMBRE_MUSIQUE      1
#define NOMBRE_POLICE       1



const std::string cheminRessources = "ressources/";
const std::string cheminSon = cheminRessources + "sons/";
const std::string cheminImage = cheminRessources + "images/";
const std::string cheminFile = cheminRessources + "fichiers/";
const std::string cheminPolice = cheminRessources + "polices/";



struct Input    /// structure pour la capture des évènements
{
	char key[SDLK_LAST];
	int mousex,mousey;
	int mousexrel,mouseyrel;
	char mousebuttons[8];
    char quit;
};



void updateEvents(Input *);             /// MàJ des évènements

void initialisation(FMOD_SYSTEM * p_system);        /// initialise le jeu
void fermeture(FMOD_SYSTEM * p_system);             /// ferme le jeu

void load_images(SDL_Surface ** p_images);                          /// charge les images utiles
void load_musiques(FMOD_SYSTEM * p_system, FMOD_SOUND ** p_sons);   /// charge les musiques utiles
void load_polices(TTF_Font ** p_polices);                           /// charge les polices utiles

void free_images(SDL_Surface ** p_images);  /// libère les images chargées
void free_musiques(FMOD_SOUND ** p_sons);   /// libère les musiques chargées
void free_polices(TTF_Font ** p_polices);   /// libère les polices chargées

int size_of_game(int p_hauteur_ecran);        /// détermine la hauteur de l'écran



#endif /// UTILE_H_INCLUDED
