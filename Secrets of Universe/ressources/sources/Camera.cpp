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

