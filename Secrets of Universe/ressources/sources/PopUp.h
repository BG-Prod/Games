#ifndef POPUP_H
#define POPUP_H

#include <Interface.h>


class PopUp : public Interface
{
    public:
        PopUp();
        PopUp(string text, types t, long duration);
        virtual ~PopUp();

    protected:
};

#endif // POPUP_H
