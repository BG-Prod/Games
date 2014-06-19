/*
    Trace
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

#include "Camera.h"

Camera::Camera()
{
    velocity = 20;
    positionOnScreen.modify(0,0,SDL_GetVideoSurface()->w,SDL_GetVideoSurface()->h);
    positionOnMap.modify(0,0,SDL_GetVideoSurface()->w,SDL_GetVideoSurface()->h);
}

Camera::~Camera()
{
    //dtor
}

void Camera::cameraLeft()
{
    positionOnMap += Coordonnees(-velocity, 0, 0, 0);
}

void Camera::cameraRight()
{
    positionOnMap += Coordonnees(velocity, 0, 0, 0);
}

void Camera::cameraUp()
{
    positionOnMap += Coordonnees(0, -velocity, 0, 0);
}

void Camera::cameraDown()
{
    positionOnMap += Coordonnees(0, velocity, 0, 0);
}

void Camera::keepIn(Object * o)
{
    if(positionOnMap.x()<o->getPosition().x())
    {
        positionOnMap.x(o->getPosition().x());
    }
    if(positionOnMap.y()<o->getPosition().y())
    {
        positionOnMap.y(o->getPosition().y());
    }
    if(positionOnMap.x()+positionOnScreen.w()>o->getPosition().x()+o->getPosition().w())
    {
        positionOnMap.x(o->getPosition().x()+o->getPosition().w()-positionOnScreen.w());
    }
    if(positionOnMap.y()+positionOnScreen.h()>o->getPosition().y()+o->getPosition().h())
    {
        positionOnMap.y(o->getPosition().y()+o->getPosition().h()-positionOnScreen.h());
    }
}


