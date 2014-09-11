#include "PopUp.h"

PopUp::PopUp()
{
    type[0] = POPUP;
}

PopUp::PopUp(string text, types t, long duration)
{
    type[0] = t;
}

PopUp::~PopUp()
{
    //dtor
}
