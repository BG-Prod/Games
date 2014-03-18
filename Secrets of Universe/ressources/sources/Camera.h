#ifndef CAMERA_H
#define CAMERA_H

#include <SDL.h>

#include <Coordonnees.h>

class Camera
{
    public:
        Camera();
        virtual ~Camera();

        void cameraLeft();
        void cameraRight();
        void cameraUp();
        void cameraDown();
        Coordonnees view(){return positionOnMap;}
        Coordonnees place(){return positionOnScreen;}

    protected:
        Coordonnees positionOnMap;
        Coordonnees positionOnScreen;
        int velocity;   /// pour la vitesse de scrolling
};

#endif // CAMERA_H
