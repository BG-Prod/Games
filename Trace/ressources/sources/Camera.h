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

#ifndef CAMERA_H
#define CAMERA_H

#include <SDL.h>

#include <Coordonnees.h>
#include <Object.h>

class Camera
{
    public:
        Camera();
        virtual ~Camera();

        void cameraLeft();
        void cameraRight();
        void cameraUp();
        void cameraDown();
        void keepIn(Object * o);
        Coordonnees view(){return positionOnMap;}
        Coordonnees place(){return positionOnScreen;}

    protected:
        Coordonnees positionOnMap;
        Coordonnees positionOnScreen;
        int velocity;   /// pour la vitesse de scrolling
};

#endif // CAMERA_H
