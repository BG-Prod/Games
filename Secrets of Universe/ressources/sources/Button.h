#ifndef BUTTON_H
#define BUTTON_H

#include <Object.h>

class Button : public Object
{
    public:
        Button(int _type, Coordonnees _coor, std::string _name);
        virtual ~Button();

        bool hover(Input*);
        bool pressed(Input*);
        void update(Input * in);

    protected:
        std::string name;
};

#endif // BUTTON_H
