#ifndef APPTEST_H
#define APPTEST_H

#include <Application.h>


class AppTest : public Application
{
    public:
        AppTest();
        virtual ~AppTest();
    protected:
        int whatImage(int,int);
    private:
};

#endif // APPTEST_H
