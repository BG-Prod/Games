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


#ifndef JEU_H_INCLUDED
#define JEU_H_INCLUDED


#include <SDL.h>
#include <cstdlib>
#include <stdlib.h>
#include <stdio.h>
#include <FMOD/fmod.h>
#include <SDL_image.h>
#include <math.h>
#include <string>
#include <fstream>
#include <iostream>
#include <windows.h>
#include <fstream>


#include "utile.h"
#include "affichage.h"
#include "bouton.h"


int cardGame(int *** p_monTab, Input p_in, SDL_Surface * p_monTabImage[NOMBRE_CARTE+1], SDL_Surface * p_imageinterface[15], SDL_Surface * p_screen,TTF_Font* p_police[NOMBRE_POLICE], int * p_score, ARG_MUSIC, int * p_numeroDeck);
void combat(int * c1,int * c2, int p_vie[2]);
void actualisationCarte(int * c);
int piocher(int *** p_monTab);
void IA(int *** p_monTab, int p_memoire[5][5]);
void jouerCarte(int ** p_carte, int p_numMain, int p_numTerrain, ARG_MUSIC);
void buildDeck(int ** p_deck);
void loadDeck(int ** p_deck, std::string adversaire);
void applyEffect(int *** p_monTab);
void cliquerGlisser(Input p_in, int ** p_monTab, bool p_test[5], bool p_zone[5], bool p_peutPlacer);

int calculVictoire(int * p_score, int * vie, SDL_Surface * p_imageinterface[15], SDL_Surface * p_screen, TTF_Font* p_police[NOMBRE_POLICE]);
void highscore(SDL_Surface * p_imageMenu[15], Input p_in, int * p_score, SDL_Surface * p_imageinterface[15], SDL_Surface * p_screen, TTF_Font* p_police[NOMBRE_POLICE], int * p_menu);


#endif // JEU_H_INCLUDED
