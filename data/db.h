#ifndef DB_H
#define DB_H

#include <sqlite3.h>

extern sqlite3 *db;

int     dbOpen(const char *filename);
int     dbInit(const char *schemaPath);
void  dbClose(void);

#endif