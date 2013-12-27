#include "bdd.h"

static int callback(void *NotUsed, int argc, char **argv, char **azColName)
{
    int i;
    for(i=0; i<argc; i++)
    {
        printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
    }
    printf("\n");
    return 0;
}


/// EXEMPLE OF USE

/**
  *  int main()
  *  {
  *      cout << "Hello world!" << endl;
  *
  *      sqlite3 * dico;
  *      char *zErrMsg = 0;
  *      int test;
  *
  *      test = sqlite3_open("ressources/database/dictionnaire.db", &dico);
  *      if( test )
  *      {
  *          fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(dico));
  *          sqlite3_close(dico);
  *          return(1);
  *      }
  *      test = sqlite3_exec(dico, "SELECT np_nom FROM nom_propre", callback, 0, &zErrMsg);
  *      if( test!=SQLITE_OK )
  *      {
  *          fprintf(stderr, "SQL error: %s\n", zErrMsg);
  *          sqlite3_free(zErrMsg);
  *      }
  *
  *      sqlite3_close(dico);
  *
  *      return 0;
  *  }
  **/

