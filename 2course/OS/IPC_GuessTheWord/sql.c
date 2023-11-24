#include "sql.h"
#include <stdio.h>
#include <stdlib.h>

static sqlite3 *db;

int initDB(const char *db_path) {
  int rc = sqlite3_open(db_path, &db);
  if (rc != SQLITE_OK) {
    fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
    sqlite3_close(db);
    return rc;
  }
  return SQLITE_OK;
}

int executeQuery(const char *query, char ***result, int *row, int *column) {
  char *errMsg = 0;
  int rc = sqlite3_get_table(db, query, result, row, column, &errMsg);
  if (rc != SQLITE_OK) {
    fprintf(stderr, "SQL error: %s\n", errMsg);
    sqlite3_free(errMsg);
    sqlite3_free_table(*result);
    return rc;
  }
  return SQLITE_OK;
}

void closeDB() { sqlite3_close(db); }
