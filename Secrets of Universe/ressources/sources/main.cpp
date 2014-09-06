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

#include <cstdlib>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <fstream>
#include <string>
#include <sstream>
#include <iostream>
#include <windows.h>
#include <fmod.h>
#include <ctime>
#include <SDL_net.h>


#include <BDD.h>
#include <Texte.h>
#include <SoUApp.h>


using namespace std;


int main(int argc, char** argv)
{
    Application * t = new SoUApp();

    t->run();

    delete t;

    return 0;
}

/*** A FAIRE
  **
  ** systeme de tir                         ===> 80%
        -> faire en sorte que les vaisseaux puissent tirer
        -> visée automatique après sélection de cible
        -> régler problèmes de tir chelou
  ** boucliers                              ===> 95%
        -> les boucliers absorbent les dégats
        -> les boucliers consomment de l'énergie
        -> les boucliers s'arrete lorsque qu'il n'y a plus d'énergie
        -> les boucliers stope s'ils sont détruits
        -> activation/désactivation avec ESPACE
  ** IA avec zone de détection radar        ===> 75%
        -> il n'est possible d'intéragir qu'avec les vaisseaux de la zone "radar"
        -> un vaisseau communique avec un allié et attaque un ennemi
  ** scan de dossier                        ===> 30%
        -> on va chercher les nouveaux media dans le dossier pour les rajouter à la base de données
  ** pop up de message                      ===> 10%
        -> crée un pop-up dans la fenetre d'execution
        -> doit etre standard mais personalisable
        -> ne suspend pas l'execution
  ** saisie clavier propre                  ===>  5%
        -> crée un champs de saisie simple
  ** charger sauvegarder                    ===>  0%
        -> permet de sauver et charger des parties
        -> dans la base de données
        -> sauve tous les objets du jeu
  ** génération de vaisseau à partir de la base de données  ===> 00%
        -> les constructeurs des vaisseaux doivent utiliser la base de données
  ** créer la base de données               ===> 15%
        -> pour toutes les carac du jeu : vaisseaux, perso, armes, sauvegardes, etc.
  **
  ** c'est déjà bien
  **
****/
