#ifndef INTERFACE_H
#define INTERFACE_H

#include <Object.h>


class Interface : public Object
{
    public:
        Interface();
        Interface(int _type);
        Interface(int _type, string _name, Coordonnees _position);

        virtual ~Interface();

        void addText(std::string t);
        void pullText(int index);

        void setState(states _st){etat[0] = _st;}

    protected:
        vector<Interface*> labels;
};

#endif // INTERFACE_H
