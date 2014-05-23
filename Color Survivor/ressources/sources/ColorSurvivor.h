#ifndef COLORSURVIVOR_H
#define COLORSURVIVOR_H

#include <Application.h>
#include <Webcam.h>

class ColorSurvivor : public Application
{
    public:
        ColorSurvivor();
        virtual ~ColorSurvivor();

        virtual void init();
        virtual void app();
        virtual int whatImage(int a,int b);

        void coloration(int x, int y, Uint32 color);

    protected:
        Webcam * myCam;
};

#endif // COLORSURVIVOR_H
