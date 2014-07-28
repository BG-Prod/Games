#include "Interface.h"

Interface::Interface() : Object()
{

}

Interface::Interface(int _type) : Object()
{
    type[0] = _type;
}

Interface::~Interface()
{
    //dtor
}


