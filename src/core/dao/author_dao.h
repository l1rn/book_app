
#ifndef AUTHOR_DAO_H
#define AUTHOR_DAO_H

#include "arena_api.h"
#include "author.h"
#include "db.h"
#include "enum.h"

dao_status      author_dao_create(DAOContext *ctx, const char* name, const char* surname, int *out_new_id);

Author*         author_dao_find_by_id(sqlite3 *db, Arena *a, int id);
Author**        author_dao_find_all(DAOContext *ctx, Arena *a, int *out_count);

int             author_dao_count(sqlite3 *db);
dao_status      author_dao_delete_by_id(sqlite3 *db, int id);

#endif
