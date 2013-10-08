#include <stdlib.h>
#include <stdio.h>

#include "verifier_deplacement.h"

/* fonction main de test de la fonction
int main()
{
	return 0;
}

*/

bool test_mouvement(int**p_tableau, int p_piece, p_origin_x, p_origin_y, p_dest_x, p_dest_y)
/*
 *Teste si les déplacemens proposés sont possibles
 *true si il est possible
 *false s'in n'est pas possible
 *on considère le tableau comm ayant y en pemiere coordonnée
 * et x en seconde coordonée
 */
{
	if(1 == p_piece) //cas du pion blanc
	{
		if(p_dest_x >= 0 and p_dest_x <= 10 and p_dest_y >= 0 and p_dest_y <= 10) //ne pas sortir du tableau
		{
			if(p_dest_x == 1 + p_origin_x or p_dest_x == p_origin_x - 1) //deplacement diagonal en avant
			{
				if(p_dest_y == p_origin_y - 1) //deplacement en avant
				{
					return true;
				}
				else
				{
					return false;
				}
			}
			else if(p_dest_x == 2 + p_origin_x or p_dest_x == p_origin_x - 2) //cas de prise
			{
				if(p_dest_y == p_dest_y + 2 and (tableau[p_origin_y+1][p_origin_x+1]==2 or tableau[p_origin_y+1][p_origin_x+1]==4)) //prise en arrière
				{
					return true;
				}
				else if(p_dest_y == p_dest_y - 2 and (tableau[p_origin_y+1][p_origin_x+1]==2 or tableau[p_origin_y+1][p_origin_x+1]==4))
				{
					return true;
				}
				else
				{
					return false;
				}
			}
			else //mauvais deplacement
			{
				return false;
			}
		}
		else
		{
			return false;
		}
	}

		else //sortie du tableau
		{
			return false;
		}
	}
	else if(2 == p_piece) //cas du pion noir
	{

	}
	else if(3 == p_piece) //dame blanche
	{

	}
	else //dame noire
	{

	}
}
