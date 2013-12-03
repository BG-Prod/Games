/*
    Draughts - Les Dames
    Copyright (C) 2013  BG Prod

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

#ifndef VERIFIER_DEPLACEMENT_H_INCLUDED
#define VERIFIER_DEPLACEMENT_H_INCLUDED


#include <stdlib.h>
#include <stdio.h>
#include <math.h>


#include "utile.h"


bool test_mouvement(int ** p_tableau, int p_piece, int p_origin_x, int p_origin_y, int p_dest_x, int p_dest_y, Animation * p_repas);

bool test_reprise(int ** p_tableau, int p_piece, int p_origin_x, int p_origin_y);

#endif //VERIFIER_DEPLACEMENT_H_INCLUDED
