#ifndef BUTTON_H
#define BUTTON_H

#include <Interface.h>

class Button : public Interface
{
    public:
        Button(int _type, Coordonnees _coor, std::string _name);
        Button(int _type, Coordonnees _coor, std::string _name, states _st);
        virtual ~Button();

        bool hover(Input*);
        bool pressed(Input*);
        void update(Input * in);
        vector<DisplayDatas> print();

        void setName(string n);

    protected:
};

#endif // BUTTON_H
