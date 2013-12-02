/*
    Draughts - Les Dames
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
#include "Texte.h"


void afficher_jeu(SDL_Surface ** p_images, Texte * p_page, int ** p_tableau1, int ** p_tableau2, Input p_in, int p_pion, Animation * p_repas);
void afficher_cases(SDL_Surface ** p_images, int ** p_tableau);
void afficher_pions(SDL_Surface ** p_images, int ** p_tableau);
void explosion(SDL_Surface ** p_images, Animation * animation); /// permet d'afficher une explosion lorsque temps = 0


#endif /// AFFICHAGE_H_INCLUDED
