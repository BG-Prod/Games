#ifndef SOUBDD_H
#define SOUBDD_H

#include <BDD.h>


class SoUBDD : public BDD
{
    public:
        SoUBDD(char * p_database);
        virtual ~SoUBDD();

    protected:
        void update();
        void save();
        void load();
};

#endif // SOUBDD_H
