/*
    PK Project
    Copyright (C) 2013  BG Prod

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
	openDB(p_database);
}

BDD::~BDD()
{
    closeDB();
}

void BDD::openDB(char * p_database)
{
	if(sqlite3_open(p_database, &database) != SQLITE_OK)
	{
	    cout << "Erreur d'ouverture de la base de données.";
	}
}

vector<vector<string> > BDD::request(char * query)
{
	sqlite3_stmt *statement;
	vector<vector<string> > results;

	if(sqlite3_prepare_v2(database, query, -1, &statement, 0) == SQLITE_OK)
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

	string error = sqlite3_errmsg(database);
	if(error != "not an error") cout << query << " " << error << endl;

	return results;
}

void BDD::closeDB()
{
	sqlite3_close(database);
	database = NULL;
}

