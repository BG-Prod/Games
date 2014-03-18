#include "Camera.h"

Camera::Camera()
{
    velocity = 5;
    positionOnScreen.modify(0,0,SDL_GetVideoSurface()->w,SDL_GetVideoSurface()->h);
    positionOnMap.modify(0,0,SDL_GetVideoSurface()->w,SDL_GetVideoSurface()->h);
    }

Camera::~Camera()
{
    //dtor
}

void Camera::cameraLeft()
{
    positionOnMap.modify(positionOnMap.x()-velocity, -1,-1,-1);
}

void Camera::cameraRight()
{
    positionOnMap.modify(positionOnMap.x()+velocity, -1,-1,-1);
}

void Camera::cameraUp()
{
    positionOnMap.modify(-1, positionOnMap.y()-velocity,-1,-1);
}

void Camera::cameraDown()
{
    positionOnMap.modify(-1, positionOnMap.y()+velocity,-1,-1);
}

