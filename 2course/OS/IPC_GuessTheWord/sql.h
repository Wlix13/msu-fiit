#ifndef SQL_H
#define SQL_H

#include <sqlite3.h>

// Initialize the database
int initDB(const char *db_path);

//  Execute a query and return results
int executeQuery(const char *query, char ***result, int *row, int *column);

// Close the database
void closeDB();

#endif // SQL_H
