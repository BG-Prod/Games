#include "Animation.h"

Animation::Animation()
{
    index = 0;
    play = false;
    echelle = 1;
    cran = 0;
}

Animation::~Animation()
{
    //dtor
}

void Animation::playAnim(bool b)
{
    play = b;
}

void Animation::addAnim(Image * i)
{
    anim.push_back(i);
}

Image * Animation::getAnim()
{
    if(play)
    {
        if(echelle == cran)
        {
            index++;
            index = index<anim.size() ? index : 0 ;
            cran = 0;
        }
        else
        {
            cran++;
        }
    }
    return anim[index];
}
