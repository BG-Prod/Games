/*
    Secrets of Universe
    Copyright (C) 2014  BG Prod

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.

    Contact me : bgprod@outlook.com
*/

#ifndef BDD_H_INCLUDED
#define BDD_H_INCLUDED


#include <stdio.h>
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <iomanip>
#include "sqlite3.h"


using namespace std;


class BDD
{
    public:
        BDD(char * p_database);
        virtual ~BDD(void);

        void openDB(char * p_database);
        vector<vector<string> > request(char * p_request);
        void closeDB();
        void request2(char * p_query);

    protected:
        sqlite3 * m_database;

    private:
        static int callback1(void *NotUsed, int argc, char **argv, char **azColName);
        static int callback2(void *NotUsed, int argc, char **argv, char **azColName);
};


#endif // BDD_H_INCLUDED
