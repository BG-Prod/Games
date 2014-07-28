#ifndef ANIMATION_H
#define ANIMATION_H

#include <Image.h>

class Animation
{
    public:
        Animation();
        virtual ~Animation();

        Image * getAnim();
        void addAnim(Image * i);
        void playAnim(bool b);

    protected:
        std::vector<Image*> anim;
        int index;
        bool play;
        int echelle, cran;
};

#endif // ANIMATION_H
