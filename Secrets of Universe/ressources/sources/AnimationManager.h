#ifndef ANIMATIONMANAGER_H
#define ANIMATIONMANAGER_H

#include <Animation.h>
#include <DisplayDatas.h>


class AnimationManager
{
    public:
        AnimationManager(Image * buff);
        virtual ~AnimationManager();

        void update();
        void displayAnimations();
        void pushAnim(DisplayDatas dd, Animation * anim);
        void popAnim(int index);

    protected:
        vector<DisplayDatas> disDaVector;
        vector<Animation *> animVector;
        vector<int> step;

        Image * buffer;
};

#endif // ANIMATIONMANAGER_H
