#ifndef BUTTON_H
#define BUTTON_H

#include <Interface.h>

class Button : public Interface
{
    public:
        Button(int _type, Coordonnees _coor, std::string _name);
        virtual ~Button();

        bool hover(Input*);
        bool pressed(Input*);
        void update(Input * in);
        vector<DisplayDatas> print();

    protected:
        std::string name;
};

#endif // BUTTON_H
