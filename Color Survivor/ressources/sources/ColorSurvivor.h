#ifndef COLORSURVIVOR_H
#define COLORSURVIVOR_H

#include <Application.h>


class ColorSurvivor : public Application
{
    public:
        ColorSurvivor();
        virtual ~ColorSurvivor();

        virtual void init();
        virtual void app();
        virtual int whatImage(int a,int b);

    protected:
    private:
};

#endif // COLORSURVIVOR_H
