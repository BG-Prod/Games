#ifndef LABEL_H
#define LABEL_H

#include <Interface.h>


class Label : public Interface
{
    public:
        Label();
        virtual ~Label();

    protected:
        string text;
        int id;
};

#endif // LABEL_H
