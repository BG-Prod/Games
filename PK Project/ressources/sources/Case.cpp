/*
    PK Project
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

#include "Case.h"


using namespace std;


Case::Case()
{
    m_images = NULL;
    m_in = NULL;
    m_position.x = 0*RESIZE;
    m_position.y = 0*RESIZE;
    m_position.w = 90*RESIZE;
    m_position.h = 65*RESIZE;
    m_numImage = 11;
}

Case::~Case()
{

}

void Case::init(SDL_Surface ** p_images, Input * p_in)
{
    m_in = p_in;
    m_images = p_images;
}

void Case::afficher()
{
    event();
    SDL_BlitSurface(m_images[m_numImage], NULL, SDL_GetVideoSurface(), &m_position);
}

void Case::setPosition(int x, int y)
{
    m_position.x = x;
    m_position.y = y;
}

int Case::event()
{
    if(m_in->mouse(X) >= m_position.x &&
       m_in->mouse(X) < m_position.x+m_position.w &&
       m_in->mouse(Y) >= m_position.y &&
       m_in->mouse(Y) < m_position.y+m_position.h)
    {
        m_numImage = 8;
    }
    else
    {
        m_numImage = 11;
    }
}

