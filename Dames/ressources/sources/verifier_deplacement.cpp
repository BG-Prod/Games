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

#include "verifier_deplacement.h"


bool test_mouvement(int ** p_tableau, int p_piece, int p_origin_x, int p_origin_y, int p_dest_x, int p_dest_y)
/*
 *Teste si les déplacemens proposés sont possibles
 *true si il est possible
 *false s'in n'est pas possible
 *on considère le p_tableau comm ayant y en pemiere coordonnée
 * et x en seconde coordonée
 */
{
    int i = 0, j = 0;
    bool possible = true; //si le déplacement est possible ou non

	if(1 == p_piece) //cas du pion blanc
	{
		if((p_dest_x >= 0 and p_dest_x <= 9 and p_dest_y >= 0 and p_dest_y <= 9) and (p_tableau[p_dest_y][p_dest_x] == 0)) //ne pas sortir du p_tableau et case vide
		{
			if(p_dest_x == 1 + p_origin_x or p_dest_x == p_origin_x - 1) //deplacement diagonal en avant
			{
				if(p_dest_y == p_origin_y - 1) //deplacement en avant
				{
					possible = true;
				}
				else
				{
					possible = false;
				}
			}
			else if(p_dest_y == 2 + p_origin_y ) //cas de prise en arierre
			{
			    if((p_dest_x ==  p_origin_x - 2) and ((p_tableau[p_origin_y + 1][p_origin_x - 1] == 2) or (p_tableau[p_origin_y + 1][p_origin_x - 1] == 4))) //a gauche
                {
                    p_tableau[p_origin_y + 1][p_origin_x - 1] = 0;
                    possible = true;
                }
                else if((p_dest_x ==  p_origin_x + 2) and ((p_tableau[p_origin_y + 1][p_origin_x + 1] == 2) or (p_tableau[p_origin_y + 1][p_origin_x + 1] == 4))) //a droite
                {
                    p_tableau[p_origin_y + 1][p_origin_x + 1] = 0;
                    possible = true;
                }
                else
                {
                    possible = false;
                }
			}
            else if(p_dest_y == p_origin_y - 2) //cas de prise en avant
            {
                if(p_dest_x == p_origin_x - 2 and ((p_tableau[p_origin_y - 1][p_origin_x - 1] == 2) or (p_tableau[p_origin_y - 1][p_origin_x - 1] == 4))) //a gauche
                {
                    p_tableau[p_origin_y - 1][p_origin_x - 1] = 0;
                    possible = true;
                }
                else if(p_dest_x == p_origin_x + 2 and ((p_tableau[p_origin_y - 1][p_origin_x + 1] == 2) or (p_tableau[p_origin_y - 1][p_origin_x + 1] == 4))) //a droite
                {
                    p_tableau[p_origin_y - 1][p_origin_x + 1] = 0;
                    possible = true;
                }
                else
                {
                    possible = false;
                }
            }
            else //mauvais deplacement
            {
                possible = false;
            }
		}
		else //sortie du p_tableau
		{
			possible =  false;
		}
	} //fin pion noir
	else if(2 == p_piece) //cas du pion noir
	{
		if((p_dest_x >= 0 and p_dest_x < 10 and p_dest_y >= 0 and p_dest_y < 10) and (p_tableau[p_dest_y][p_dest_x] == 0)) //ne pas sortir du p_tableau et case vide
		{
			if(p_dest_x == 1 + p_origin_x or p_dest_x == p_origin_x - 1) //deplacement diagonal en avant
			{
				if(p_dest_y == p_origin_y + 1) //deplacement en avant
				{
					possible = true;
				}
				else
				{
					possible = false;
				}
			}
			else if(p_dest_y == 2 + p_origin_y ) //cas de prise en avant
			{
			    if((p_dest_x ==  p_origin_x - 2) and ((p_tableau[p_origin_y + 1][p_origin_x - 1] == 1) or (p_tableau[p_origin_y + 1][p_origin_x - 1] == 3))) //a gauche
                {
                    p_tableau[p_origin_y + 1][p_origin_x - 1] = 0;
                    possible = true;
                }
                else if((p_dest_x ==  p_origin_x + 2) and ((p_tableau[p_origin_y + 1][p_origin_x + 1] == 1) or (p_tableau[p_origin_y + 1][p_origin_x + 1] == 3))) //a droite
                {
                    p_tableau[p_origin_y + 1][p_origin_x + 1] = 0;
                    possible = true;
                }
                else
                {
                    possible = false;
                }
			}
            else if(p_dest_y == p_origin_y - 2) //cas de prise en arriere
            {
                if(p_dest_x == p_origin_x - 2 and (p_tableau[p_origin_y - 1][p_origin_x - 1]%2)) //a gauche
                {
                    p_tableau[p_origin_y - 1][p_origin_x - 1] = 0;
                    possible = true;
                }
                else if(p_dest_x == p_origin_x + 2 and (p_tableau[p_origin_y - 1][p_origin_x + 1]%2)) //a droite
                {
                    p_tableau[p_origin_y - 1][p_origin_x + 1] = 0;
                    possible = true;
                }
                else
                {
                    possible = false;
                }
            }
			else //mauvais deplacement
			{
				possible = false;
			}
		}
		else //sortie du p_tableau
		{
			possible = false;
		}
	}//fin pion noir
	else if(3 == p_piece) //dame blanche
	{
	    if(p_tableau[p_dest_y][p_dest_x] != 0)
        {
            possible = false;
        }
        else
        {
            if(abs(p_dest_y-p_origin_y) != abs(p_dest_x-p_origin_x))
            {
                possible = false;
            }
            else
            {
                int noires = 0, blanches = 0;
                i = p_origin_x;
                j = p_origin_y;

                while(i!=p_dest_x)
                {
                    if(2==p_tableau[j][i] or 4==p_tableau[j][i])
                    {
                        noires++;
                    }
                    blanches += p_tableau[j][i]%2;
                    i += ((p_dest_x-p_origin_x)/(abs(p_dest_x-p_origin_x)));
                    j += ((p_dest_y-p_origin_y)/(abs(p_dest_y-p_origin_y)));
                }

                if(noires > 1 || blanches > 0)
                {
                    possible = false;
                }
                else if(noires == 1)
                {
                    possible = true;
                    i = p_origin_x;
                    j = p_origin_y;
                    while(i!=p_dest_x)
                    {
                        if(2==p_tableau[j][i] or 4==p_tableau[j][i])
                        {
                            p_tableau[j][i] = 0;
                        }

                        i += ((p_dest_x-p_origin_x)/(abs(p_dest_x-p_origin_x)));
                        j += ((p_dest_y-p_origin_y)/(abs(p_dest_y-p_origin_y)));
                    }
                }
                else
                {
                    possible = true;
                }
            }
        }
    } //fin dame blanche
	else if(4 == p_piece) //dame noire
	{
	    if(p_tableau[p_dest_y][p_dest_x] != 0)
        {
            possible = false;
        }
        else
        {
            if(abs(p_dest_y-p_origin_y) != abs(p_dest_x-p_origin_x))
            {
                possible = false;
            }
            else
            {
                int noires = 0, blanches = 0;
                i = p_origin_x;
                j = p_origin_y;

                while(i!=p_dest_x)
                {
                    if(2==p_tableau[j][i] or 4==p_tableau[j][i])
                    {
                        noires++;
                    }
                    blanches += p_tableau[j][i]%2;
                    i += ((p_dest_x-p_origin_x)/(abs(p_dest_x-p_origin_x)));
                    j += ((p_dest_y-p_origin_y)/(abs(p_dest_y-p_origin_y)));
                }

                if(noires > 0 || blanches > 1)
                {
                    possible = false;
                }
                else if(blanches == 1)
                {
                    possible = true;
                    i = p_origin_x;
                    j = p_origin_y;

                    while(i!=p_dest_x)
                    {
                        if(p_tableau[j][i]%2)
                        {
                            p_tableau[j][i] = 0;
                        }

                        i += ((p_dest_x-p_origin_x)/(abs(p_dest_x-p_origin_x)));
                        j += ((p_dest_y-p_origin_y)/(abs(p_dest_y-p_origin_y)));
                    }

                }
                else
                {
                    possible = true;
                }
            }
        }
    } //fin dame noire

    return possible;
} //fin fonction


