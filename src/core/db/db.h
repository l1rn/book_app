#ifndef DB_H
#define DB_H

#include <sqlite3.h>

typedef struct DAOContext DAOContext;

int     db_open(const char *filename, DAOContext **ctx_out);
int     db_init(DAOContext *ctx, const char *schemaPath);
void    db_close(DAOContext *ctx);

sqlite3 *db_get_handle(DAOContext *ctx);
#endif