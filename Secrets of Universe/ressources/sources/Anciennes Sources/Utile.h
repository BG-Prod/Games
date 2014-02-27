#ifndef UTILE_H_INCLUDED
#define UTILE_H_INCLUDED


#include <SDL_ttf.h>
#include <SDL_image.h>
#include <FMOD/fmod.h>
#include <iostream>
#include <windows.h>


#include "Constantes.h"

struct Input
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


void jeu(SDL_Surface ** p_images);

void animation(SDL_Surface ** p_animation, SDL_Rect p_position, SDL_Surface* p_ouColler, int i);
bool collision( SDL_Rect A, SDL_Rect B );

void charger();


class BarreVie
{
 public:
  BarreVie();
  ~BarreVie();

  void setPosition(SDL_Rect p_position);
  void actualiserEtat(int p_vie);
  void afficher(SDL_Surface *p_ecran);

 protected:
  int m_vie;
  SDL_Rect m_barreInfo;
  SDL_Rect m_tailleCadre;
  SDL_Surface *m_barreCadre;
  SDL_Surface *m_barreJauge;
  bool m_estVisible;
};

#endif
