/*
    Trace
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

#include "bdd.h"


BDD::BDD(char * p_database)
{
	m_database = NULL;
	openDB(p_database);
}

BDD::~BDD()
{
    closeDB();
}

void BDD::openDB(char * p_database)
{
	if(sqlite3_open(p_database, &m_database) != SQLITE_OK)
	{
	    cout << "Erreur d'ouverture de la base de données.";
	}
}

vector<vector<string> > BDD::request(char * p_query)
{
	sqlite3_stmt * statement;
	vector<vector<string> > results;

	if(sqlite3_prepare_v2(m_database, p_query, -1, &statement, 0) == SQLITE_OK)
	{
		int cols = sqlite3_column_count(statement);
		int result = 0;
		while(true)
		{
			result = sqlite3_step(statement);

			if(result == SQLITE_ROW)
			{
				vector<string> values;
				for(int col = 0; col < cols; col++)
				{
					values.push_back((char*)sqlite3_column_text(statement, col));
				}
				results.push_back(values);
			}
			else
			{
				break;
			}
		}

		sqlite3_finalize(statement);
	}
	else
    {
        vector<string> values;
        values.push_back("Error : cannot answer this query");
        results.push_back(values);
    }

	return results;
}

void BDD::request2(char * p_query)
{
    char *zErrMsg = 0;
    int test;
    test = sqlite3_exec(m_database, p_query, callback2, 0, &zErrMsg);
    if( test!=SQLITE_OK )
    {
        fprintf(stderr, "SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
    }
}

void BDD::closeDB()
{
	sqlite3_close(m_database);
	m_database = NULL;
}


int BDD::callback1(void *NotUsed, int argc, char **argv, char **azColName)
{
    int i;
    for(i=0; i<argc; i++)
    {
        printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
    }
    printf("\n");
    return 0;
}

int BDD::callback2(void *NotUsed, int argc, char **argv, char **azColName)
{
    int i;
    ofstream fichier("./ressources/output/results.txt", ios::app);
    for(i=0; i<argc; i++)
    {
        printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
        fichier << (argv[i] ? argv[i] : "NULL") << " ";

    }
    printf("\n");
    fichier << "; ";
    fichier.close();
    return 0;
}

