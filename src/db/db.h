#ifndef DB_H
#define DB_H

#include <sqlite3.h>

extern sqlite3 *db;

int     db_open(const char *filename);
int     db_init(const char *schemaPath);
int     db_check();
void  db_close(void);

#endif