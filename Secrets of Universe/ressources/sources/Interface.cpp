#include "Interface.h"

Interface::Interface() : Object()
{

}

Interface::Interface(int _type) : Object()
{
    type[0] = _type;
}

Interface::Interface(int _type, string _name, Coordonnees _position) : Object()
{
    type[0] = _type;
    name = _name;
    position = _position;
}

Interface::~Interface()
{
    //dtor
}


void Interface::addText(std::string t)
{
    sons.push_back(new Interface(-26, t, position));
    labels.push_back((Interface*)sons.back());
}

void Interface::pullText(int index)
{
    delete labels[index];
    labels.erase(labels.begin()+index);
    for(unsigned int i = 0 ; i < sons.size() ; i++)
    {
        if(sons[i]==labels[index])
        {
            sons.erase(sons.begin()+i);
        }
    }
    delete labels[index];
    labels.erase(labels.begin()+index);
}


