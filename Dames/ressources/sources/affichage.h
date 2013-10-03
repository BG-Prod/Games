#ifndef AFFICHAGE_H_INCLUDED
#define AFFICHAGE_H_INCLUDED



#include <cstdlib>
#include <stdlib.h>
#include <stdio.h>
#include <string>
#include <windows.h>
#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_image.h>
#include <FMOD/fmod.h>


#include "utile.h"


void afficher_jeu(SDL_Surface ** p_images, int ** p_tableau1, int ** p_tableau2);
void afficher_cases(SDL_Surface ** p_images, int ** p_tableau);
void afficher_pions(SDL_Surface ** p_images, int ** p_tableau);


#endif // AFFICHAGE_H_INCLUDED
