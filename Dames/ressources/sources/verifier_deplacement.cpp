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
    int i = 0;
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
		if((p_dest_x >= 0 and p_dest_x <= 9 and p_dest_y >= 0 and p_dest_y <= 9) and (p_tableau[p_dest_y][p_dest_x] == 0)) //ne pas sortir du p_tableau et case vide
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
            else if(p_dest_y == p_origin_y - 2) //cas de prise en arierre
            {
                if(p_dest_x == p_origin_x - 2 and ((p_tableau[p_origin_y - 1][p_origin_x - 1] == 1) or (p_tableau[p_origin_y - 1][p_origin_x - 1] == 3))) //a gauche
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
			possible = false;
		}
	}//fin pion noir
	else if(3 == p_piece) //dame blanche
	{
	    if((p_dest_x >= 0 and p_dest_x <= 9 and p_dest_y >= 0 and p_dest_y <= 9) and (p_tableau[p_dest_y][p_dest_x] == 0)) //sortie tableau ou case vide
        {
            if(abs(p_dest_x - p_origin_x) == abs (p_dest_y - p_origin_y)) //déplacement en diagonale
            {
                if((p_dest_y - p_origin_y) < 0) //vers le haut
                {
                    if((p_dest_x - p_origin_x) > 0) //vers la droite
                    {
                        for(i=1; i<abs(p_dest_x - p_origin_x); i++) //verifie si il y a un pion sur la trajectoire de la dame
                        {
                            if((p_tableau[p_origin_y - i][p_origin_x + i] == 1) or (p_tableau[p_origin_y - i][p_origin_x + i] == 3))
                            {
                                possible = false;
                            }
                        }
                        if((possible != false) and ((p_tableau[p_dest_y + 1][p_dest_x - 1] == 2) or (p_tableau[p_dest_y + 1][p_dest_x - 1] == 4)))
                        {
                            p_tableau[p_dest_y + 1][p_dest_x - 1] = 0;
                        }
                    }
                    else //vers la gauche
                    {
                        for(i=1; i<abs(p_dest_x - p_origin_x); i++) //verifie si il y a un pion sur la trajectoire de la dame
                        {
                            if((p_tableau[p_origin_y - i][p_origin_x - i] == 1) or (p_tableau[p_origin_y - i][p_origin_x - i] == 3))
                            {
                                possible = false;
                            }
                        }
                        if((possible != false) and ((p_tableau[p_dest_y + 1][p_dest_x + 1] == 2) or (p_tableau[p_dest_y + 1][p_dest_x + 1] == 4)))
                        {
                            p_tableau[p_dest_y + 1][p_dest_x + 1] = 0;
                        }
                    }
                }
                else //vers le bas
                {
                    if((p_dest_x - p_origin_x) > 0) //vers la droite
                    {
                        for(i=1; i<abs(p_dest_x - p_origin_x); i++) //verifie si il y a un pion sur la trajectoire de la dame
                        {
                            if((p_tableau[p_origin_y + i][p_origin_x + i] == 1) or (p_tableau[p_origin_y + i][p_origin_x + i] == 3))
                            {
                                possible = false;
                            }
                        }
                        if((possible != false) and ((p_tableau[p_dest_y - 1][p_dest_x - 1] == 2) or (p_tableau[p_dest_y - 1][p_dest_x - 1] == 4)))
                        {
                            p_tableau[p_dest_y - 1][p_dest_x - 1] = 0;
                        }
                    }
                    else //vers la gauche
                    {
                        for(i=1; i<abs(p_dest_x - p_origin_x); i++) //verifie si il y a un pion sur la trajectoire de la dame
                        {
                            if((p_tableau[p_origin_y + i][p_origin_x - i] == 1) or (p_tableau[p_origin_y + i][p_origin_x - i] == 3))
                            {
                                possible = false;
                            }
                        }
                        if((possible != false) and ((p_tableau[p_dest_y - 1][p_dest_x + 1] == 2) or (p_tableau[p_dest_y - 1][p_dest_x + 1] == 4)))
                        {
                            p_tableau[p_dest_y - 1][p_dest_x + 1] = 0;
                        }
                    }
                }
            }
            else //mauvais déplacement
            {
                possible = false;
            }
        }
        else //sortie de tableau ou case non vide
        {
            possible = false;
        }
	} //fin dame blanche
	else if(4 == p_piece) //dame noire
	{
	    if((p_dest_x >= 0 and p_dest_x <= 9 and p_dest_y >= 0 and p_dest_y <= 9) and (p_tableau[p_dest_y][p_dest_x] == 0)) //sortie tableau ou case vide
        {
            if(abs(p_dest_x - p_origin_x) == abs (p_dest_y - p_origin_y)) //déplacement en diagonale
            {
                if((p_dest_y - p_origin_y) < 0) //vers le bas
                {
                    if((p_dest_x - p_origin_x) > 0) //vers la droite
                    {
                        for(i=1; i<abs(p_dest_x - p_origin_x); i++) //verifie si il y a un pion sur la trajectoire de la dame
                        {
                            if((p_tableau[p_origin_y - i][p_origin_x + i] == 1) or (p_tableau[p_origin_y - i][p_origin_x + i] == 3))
                            {
                                possible = false;
                            }
                        }
                        if((possible != false) and ((p_tableau[p_dest_y + 1][p_dest_x - 1] == 2) or (p_tableau[p_dest_y + 1][p_dest_x - 1] == 4)))
                        {
                            p_tableau[p_dest_y + 1][p_dest_x - 1] = 0;
                        }
                    }
                    else //vers la gauche
                    {
                        for(i=1; i<abs(p_dest_x - p_origin_x); i++) //verifie si il y a un pion sur la trajectoire de la dame
                        {
                            if((p_tableau[p_origin_y - i][p_origin_x - i] == 1) or (p_tableau[p_origin_y - i][p_origin_x - i] == 3))
                            {
                                possible = false;
                            }
                        }
                        if((possible != false) and ((p_tableau[p_dest_y + 1][p_dest_x + 1] == 2) or (p_tableau[p_dest_y + 1][p_dest_x + 1] == 4)))
                        {
                            p_tableau[p_dest_y + 1][p_dest_x + 1] = 0;
                        }
                    }
                }
                else //vers le haut
                {
                    if((p_dest_x - p_origin_x) > 0) //vers la droite
                    {
                        for(i=1; i<abs(p_dest_x - p_origin_x); i++) //verifie si il y a un pion sur la trajectoire de la dame
                        {
                            if((p_tableau[p_origin_y + i][p_origin_x + i] == 1) or (p_tableau[p_origin_y + i][p_origin_x + i] == 3))
                            {
                                possible = false;
                            }
                        }
                        if((possible != false) and ((p_tableau[p_dest_y - 1][p_dest_x - 1] == 2) or (p_tableau[p_dest_y - 1][p_dest_x - 1] == 4)))
                        {
                            p_tableau[p_dest_y - 1][p_dest_x - 1] = 0;
                        }
                    }
                    else //vers la gauche
                    {
                        for(i=1; i<abs(p_dest_x - p_origin_x); i++) //verifie si il y a un pion sur la trajectoire de la dame
                        {
                            if((p_tableau[p_origin_y + i][p_origin_x - i] == 1) or (p_tableau[p_origin_y + i][p_origin_x - i] == 3))
                            {
                                possible = false;
                            }
                        }
                        if((possible != false) and ((p_tableau[p_dest_y - 1][p_dest_x + 1] == 2) or (p_tableau[p_dest_y - 1][p_dest_x + 1] == 4)))
                        {
                            p_tableau[p_dest_y - 1][p_dest_x + 1] = 0;
                        }
                    }
                }
            }
            else //mauvais déplacement
            {
                possible = false;
            }
        }
        else //sortie de tableau ou case non vide
        {
            possible = false;
        }
	} //fin dame noire

    return possible;
} //fin fonction


