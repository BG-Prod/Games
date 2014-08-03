#ifndef ANIMATION_H
#define ANIMATION_H

#include <Image.h>

using namespace std;

class Animation : public Image
{
    friend Image;
    public:
        Animation(string link);
        virtual ~Animation();

        void print(Image * buffer, Coordonnees where, int which);
        int getNbFrame();
        bool isInfinite();

    protected:
        int nbFrame;
        bool infinite;
        int nbPerLine, nbPerColumn;
};

#endif /// ANIMATION_H
