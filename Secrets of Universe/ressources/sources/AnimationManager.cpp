#include "AnimationManager.h"

AnimationManager::AnimationManager(Image * buff)
{
    buffer = buff;
}

AnimationManager::~AnimationManager()
{
    //dtor
}

void AnimationManager::update()
{
    for(unsigned int i = 0 ; i < step.size() ; ++i)
    {
        step[i]++;
        if(!animVector[i]->isInfinite())
        {
            if(animVector[i]->getNbFrame()==step[i])
            {
                popAnim(i);
            }
        }
    }
}

void AnimationManager::pushAnim(DisplayDatas dd, Animation * anim)
{
    disDaVector.push_back(dd);
    animVector.push_back(anim);
    step.push_back(0);
}

void AnimationManager::popAnim(int index)
{
    disDaVector.erase(disDaVector.begin()+index);
    animVector.erase(animVector.begin()+index);
    step.erase(step.begin()+index);
}

void AnimationManager::displayAnimations()
{
    for(unsigned int i = 0 ; i < animVector.size() ; ++i)
    {
        animVector[i]->print(buffer,disDaVector[i].coor,step[i]);
    }
}


