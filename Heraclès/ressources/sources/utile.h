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


#ifndef UTILE_H_INCLUDED
#define UTILE_H_INCLUDED


#include <SDL.h>
#include <cstdlib>
#include <stdlib.h>
#include <stdio.h>
#include <FMOD/fmod.h>
#include <SDL_image.h>
#include <math.h>
#include <fstream>
#include <string>
#include <sstream>
#include <iostream>
#include <SDL_ttf.h>
#include <windows.h>
#include <WinSock.h>


#define CX_SCREEN           GetSystemMetrics(SM_CXSCREEN)            //Largeur
#define CY_SCREEN           GetSystemMetrics(SM_CYSCREEN)            //Hauteur
#define NB_CARRE_X          5
#define NB_CARRE_Y          2
#define TAILLE_CARRE        128
#define LARGEUR_ECRAN       640
#define HAUTEUR_ECRAN       640
#define SCREEN_REFRESH      40
#define NOMBRE_CARTE        62
#define NOMBRE_MUSIQUE      5
#define NB_IMAGE_MENU       8
#define NB_IMAGE_EDITEUR    7
#define NB_IMAGE_INTERFACE  16
#define NOMBRE_DECK_PERSO   3
#define NOMBRE_POLICE       6
#define ARGUMENT_IMAGE      SDL_Surface * p_monTabImage[NOMBRE_CARTE+1], SDL_Surface * p_imageMenu[NB_IMAGE_MENU], SDL_Surface * p_imageEditeur[NB_IMAGE_EDITEUR]
#define ARGUMENT            bool* peutPrendre, bool* peutPlacer, bool* peutAttaquer, bool* peutPiocher, int *** p_monTab, Input * p_in, int * vie, int memoireJeu[5][5], SDL_Surface * p_monTabImage[NOMBRE_CARTE+1], SDL_Surface * p_imageinterface[15], SDL_Surface * p_screen,TTF_Font* p_police[NOMBRE_POLICE], int p_score, bool * test, bool * zone
#define VARIABLE            &peutPrendre, &peutPlacer, &peutAttaquer, &peutPiocher, p_monTab, &p_in, vie, memoireJeu, p_monTabImage, p_imageinterface, p_screen, p_police, p_score, test, zone
#define DEBUG               std::cerr << std::endl <<
#define ARG_MUSIC           FMOD_SYSTEM * p_system, FMOD_SOUND * p_monTabZic[NOMBRE_MUSIQUE]
#define VAR_MUSIC           system, monTabZic
#define VAR_MUSIC2          p_system, p_monTabZic

struct Input
{
	char key[SDLK_LAST];
	int mousex,mousey;
	int mousexrel,mouseyrel;
	char mousebuttons[8];
    char quit;
};

class bouton;


const std::string cheminRessources = "ressources/";
const std::string cheminSon = cheminRessources + "son/";
const std::string cheminImage = cheminRessources + "image/";
const std::string cheminFile = cheminRessources + "file/";
const std::string cheminPolice = cheminRessources + "police/";

enum objet{VAISSEAU, ETRE, PROJECTILE, ASTRE};
enum phase{PIOCHE, POSE, EFFET, COMBAT};
enum etat{OFF, ON};

void updateEvents(Input *);
void load_png(ARGUMENT_IMAGE);
void free_png(ARGUMENT_IMAGE);
std::string extract_ssString(std::string s, char c);
std::string niemeLigne(const std::string & filename, int);
int nombreLignes(const std::string & filename);
int loadNombreDeCartes();
void chargerHighscores(int p_highscores[3], std::string * p_highscoreurs);
int stringTOint(std::string chaine);
void sauvegarderScore(int * p_score, std::string p_name);
void chargerDeckEditeur(int p_deck[NOMBRE_DECK_PERSO][40], std::string p_listeNoms[NOMBRE_CARTE]);
void dechargerDeckEditeur(int p_deck[NOMBRE_DECK_PERSO][40]);
void sauvegarderDeckEditeur(int p_deck[NOMBRE_DECK_PERSO][40]);

void editeurDeck(int p_deck[NOMBRE_DECK_PERSO][40], SDL_Surface * p_imageEditeur[NB_IMAGE_EDITEUR], Input p_in, SDL_Surface * p_screen, int * p_numeroDeck, int ** p_index, TTF_Font* p_police[NOMBRE_POLICE], std::string * p_cardsName, int * p_b);
void afficherEditeur(int p_deck[NOMBRE_DECK_PERSO][40], SDL_Surface * p_imageEditeur[NB_IMAGE_EDITEUR], SDL_Surface * p_screen, int * p_numeroDeck, int ** p_index, TTF_Font* p_police[NOMBRE_POLICE], std::string * p_cardsName, Input p_in, int * b);
void testCurseurEditeur(Input p_in, int * p_numeroDeck);
void afficherInfoEditeur(int * p_carteScannee, SDL_Surface * p_screen, SDL_Surface * p_imageEditeur[NB_IMAGE_EDITEUR], TTF_Font* p_police[NOMBRE_POLICE], int ** p_index, std::string * p_cardsName);
void initIndex(int ** p_deck);
void testScan(Input p_in, int * p_b, int p_deck[NOMBRE_DECK_PERSO][40], int * p_numeroDeck);

#endif // UTILE_H_INCLUDED


// MAJ DU 25 SEPTEMBRE 2013
// score en pointeurs marchent à 100%


// MAJ DU 24 SEPTEMBRE 2013
// correction orthographe
// rectification du décalage patial d'affichage des cartes
// score en pointeurs ... BUG !!!


// MAJ (2) DU 21 SEPTEMBRE 2013
// gros bug du jeu + de l'editeur SUPPRIMé :D
// fenetre modifiable
// VERSION 2.0 Prête


// MAJ DU 21 SEPTEMBRE 2013
// gros bug du jeu + de l'editeur :s


// MODIF DU 15 SEPTEMBRE 2013
// travail sur l'éditeur et les boutons


// MAJ DU 14 SEPTEMBRE 2013
// bouton universel en place


// CHOSES A FAIRE
// rajouter des cartes                                  !!! FAIT le 08/09/2013 +30 new cards
// faire des decks                                      !!! FAIT le 21/09/2013
// s'occuper de la sélection des decks                  !!! FAIT le 21/09/2013
// rajouter des boutons pour les phases de combats      !!! FAIT le 08/09/2013
// faire l'éditeur de deck                              !!! FAIT le 21/09/2013
// organiser le tout et faire la doc                    !!! FAIT le 21/09/2013 mais à continuer


// MAJ DU 2 SEPTEMBRE 2013
// retour du son avec fmodex
// combats plus clairs


// MAJ DU 1 SEPTEMBRE 2013
// 2 nouvelles cartes
// menu retravaillé
// système de high scores


// MAJ DU 30 AOUT 2013
// réparation du bug des effets
// plus de musique
// possibilité de personaliser les decks
// pioche aléatoire
// tempo du combat

// MESSAGE DU 13 AVRIL 2013
// Refonte complète du système de combat reprendre cette version en cas de problème

// MAJ older

// 10 nouvelles cartes
// retrait du fullscreen
// garde du cadre info dans l'écran
// resize du cadre info
// erreur lorsqu'on quitte avec la console avec la croix mais c'est normal apparemment
// programme licencié
// nouveau calcul du malus de défaite et malus de 3000 pour le rage quit
// implémentation des effets
// cliquer-glisser
// nouvelle interface
// bug des effets

