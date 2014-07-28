#ifndef INTERFACE_H
#define INTERFACE_H

#include <Object.h>


class Interface : public Object
{
    public:
        Interface();
        Interface(int _type);

        virtual ~Interface();

    protected:
};

#endif // INTERFACE_H
