/*
    The Arvernes - The Card Game
    Copyright (C) 2013  Garçon Benoît

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

    Contact me : benoit.garconbesson@gmail.com
*/


#ifndef AFFICHAGE_H_INCLUDED
#define AFFICHAGE_H_INCLUDED


#include <SDL.h>
#include <cstdlib>
#include <stdlib.h>
#include <stdio.h>
#include <FMOD/fmod.h>
#include <SDL_ttf.h>
#include <SDL_image.h>
#include <math.h>
#include <string>
#include <fstream>
#include <iostream>
#include <windows.h>
#include <fstream>
#include <sstream>


#include "utile.h"
class bouton;


void afficherCarte(int ** p_monTab, SDL_Surface * p_monTabImage[NOMBRE_CARTE+1], SDL_Surface * p_ouColler);
void afficherInterface(SDL_Surface * p_imageInterface[15], SDL_Surface * p_ouColler, int p_vie[2],TTF_Font* p_police[NOMBRE_POLICE]);
void majAffichage(int ** p_monTab, SDL_Surface * p_monTabImage[NOMBRE_CARTE+1], SDL_Surface * p_imageInterface[15], SDL_Surface * p_ouColler, int p_vie[2],TTF_Font* p_police[NOMBRE_POLICE], Input in, bool p_test[5], bouton * p_bouton);
void afficherInfos(int ** p_monTab, SDL_Surface * p_imageInterface[15], SDL_Surface * p_ouColler, Input p_in,TTF_Font* p_police[NOMBRE_POLICE]);
void afficherScore(SDL_Surface * p_imageInterface[15], SDL_Surface * p_ouColler, int * p_score, std::string p_chaine, TTF_Font* p_police[NOMBRE_POLICE]);
void afficherCarteEnnemi(int ** p_monTab, SDL_Surface * p_monTabImage[NOMBRE_CARTE+1], SDL_Surface * p_ouColler);
SDL_Rect testCurseur(Input p_in);
int testCurseur2(Input p_in);
void afficherCliquerGlisser(int ** p_monTab, bool p_test[5], SDL_Surface * p_monTabImage[NOMBRE_CARTE+1], Input p_in, SDL_Surface * p_ouColler);
std::string afficherEffet(int p_z, int ** p_monTab);
int afficherMenu(Input in, SDL_Surface *screen, SDL_Surface *p_imageMenu[NB_IMAGE_MENU]);

#endif // AFFICHAGE_H_INCLUDED
