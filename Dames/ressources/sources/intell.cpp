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

/**
    Les priorites de jeu doivent dependre du cas dans lequel on est
    (voir fiche descriptive IA)

    Sans doutes faire un tableaux avec differentes priorités en fonction du cas et toujours attribuer
    la meme case du tableau comme priorite de deplacement du pion


    faire une fonction qui vire les deplacement pas importants juste avant de return les tableau de position
    et ne retourner qu'un tableau de dimension 1 au final
*/


#include "intell.h"

void faire_jouer_ia( ) ///je ne sais pas encore ce que ca va prendre, mais ca va prendre cher !
{
    int ** deplacements = (int*)malloc(XXX * sizeof(int*)); ///XXX a remplacer par le nombre de fonctions de test de deplacement



}

int ** dame() ///va sans doute prendre un tableau
{
    /// variables, ne pas oublier de free()

    int ** deplacement = (int **)malloc(5 * sizeof(int*)); ///tous les deplacements trouvés
    for(int i =0; i<5; i++)
    {
        deplacement[i] = (int*)malloc(3 * sizeof(int));
    }

    int ligne = 0; ///indice pour placer les deplacement dans le tableau

    ///initialisation du tableau a 0 si jamais on a pas de point qui va dedans
    for(int i = 0; i < 5; i++)
    {
        for(int j = 0 ;j < 3; j++)
        {
            deplacement[i][j] = 0;
        }
    }
            /**
            deplacement[][0] -> coordonnee x
            deplacement[][1] -> coordonnee y
            deplacement[][2] -> priorite du deplacement
                                                        */


    for(int i=1; i<10; i+=2)
    {
        ///avoir un pion noir sur l'avant derniere ligne des blancs
        if(2 == p_tableau[8][i])
        {
            ///savoir si on peut devenir une Dame noire
            if(tester_mouvement(p_tableau, 2, i, 8, i+1, 9) || tester_mouvement(p_tableau, 2, i, 8, i-1, 9))
            {
                deplacement[0] = 8; ///coordonee x (colonne)
                deplacement[1] = i; ///coordonee y (ligne)
                if(true == pion_menace_arierre(i, 8) || pion_une_menace_avant(i, 8))
                {
                    deplacement[ligne][2] = 100; ///pion pouvant faire une dame et etant menace
                }
                else
                {
                    deplacement[ligne][2] = 75; ///pion pouvant seulement faire une dame
                }
            }
        }
        ligne++; ///on va ecrire sur la ligne suivante
    }

    ///nettoyer les deplacement, prendre le plus important, free() deplacement et retourner un int* depl

    return ;
}

bool pion_menace_arierre(int x, int y)
/**
    teste si un pion est menacé par l'arierre
        true si c'est le cas
        false sinon

    parametres
    * tableau de deplacement
    * coordonnees de deplacement

    la fonction doit gerer le test d'une case en dehors du tableau

    la fonction doit gerer le fait qu'il puisse y avoir un pion empechant la prise
*/
{

}

bool pion_une_menace_avant(int x, int y)
/**
    Cette fonction va tester s'il y a un pion blanc dans l'une des deux diago avant du pion noir
        true si au moins un en avant
        false si aucun en avant
*/
{

}
