#ifndef MAP_H
#define MAP_H

#include <Object.h>


class Map : public Object
{
    public:
        Map();
        virtual ~Map();

        void bot();
        void update(Input * in);

    protected:
    private:
};

#endif // MAP_H
