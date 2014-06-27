#include "Button.h"

Button::Button(int _type, Coordonnees _coor, std::string _name) : Object()
{
    type[0] = _type;
    etat[0] = OFF;
    name = _name;
    position = _coor;
}

Button::~Button()
{
    //dtor
}

bool Button::hover(Input * in)
{
    bool retour = false;

    if(in->mouse(X) < position.w()+position.x()
       && in->mouse(X) >= position.x()
       && in->mouse(Y) < position.h()+position.y()
       && in->mouse(Y) >= position.y())
    {
        retour = true;
    }

    return retour;
}

bool Button::pressed(Input * in)
{
    bool retour = false;

    if(hover(in) && in->get_souris_boutons(1))
    {
        retour = true;
    }

    return retour;
}

void Button::update(Input * in)
{
    etat[0] = (pressed(in)) ? ON : OFF;
}

