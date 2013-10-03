#ifndef JEU_H_INCLUDED
#define JEU_H_INCLUDED



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
#include "affichage.h"


void game(Input * p_in, SDL_Surface ** p_images);   // gère une partie entière
void jouer_jeu(Input * p_in, bool * p_can_play, int ** p_tableau, int * p_pion, int * p_origine_X, int * p_origine_Y, int * p_destination_X, int * p_destination_Y);    // gère la partie algo
void time_to_IA();                                  // gère le comportement de l'IA et si elle peut jouer
void tester_action();                               // test une action
bool tester_mouvement(int ** p_tableau,                 /// un tableau 10*10 contenant la valeur des pièces
                      int p_piece,                      /// valeur de le pièce qui effectue le mouvement
                      int p_origin_X, int p_origin_Y,   /// origine de la pièce dans le tableau
                      int p_dest_X, int p_dest_Y);      /// destination souhaitée dans le tableau

void pion_to_dame(int ** p_tableau);

void cliquer_prendre_poser(Input * p_in, int ** p_tableau, int * p_pion, int * p_origine_X, int * p_origine_Y, int * p_destination_X, int * p_destination_Y);
void prendre_piece(int ** p_tableau, int p_depart_X, int p_depart_Y,
                   int * p_pion, int * p_temp_X, int * p_temp_Y);
void poser_piece(int * p_pion, int * p_temp_X, int * p_temp_Y,
                 int ** p_tableau);
void nettoyer_deplacement(int * p_pion, int * p_origine_X, int * p_origine_Y, int * p_destination_X, int * p_destination_Y);



#endif // JEU_H_INCLUDED
