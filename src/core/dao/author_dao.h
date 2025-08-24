
#ifndef AUTHOR_DAO_H
#define AUTHOR_DAO_H

#include "arena_api.h"
#include "author.h"
#include <stdint.h>
#include "db.h"

typedef enum dao_status {
    DAO_SUCCESS,
    DAO_ALREADY_EXIST,
    DAO_ERROR_PREPARE,
    DAO_ERROR_EXECUTE,
    DAO_ERROR_BIND,
    DAO_ERROR_UNKNOWN,
    DAO_ERROR_NOT_FOUND,
    DAO_ERROR_INVALID_ARGS
} dao_status;

dao_status      author_dao_create(DAOContext *ctx, const char* name, const char* surname, int64_t *out_new_id);

Author*         author_dao_find_by_id(sqlite3 *db, Arena *a, int id);
Author**        author_dao_find_all(DAOContext *ctx, Arena *a, int *out_count);

int             author_dao_count(sqlite3 *db);
dao_status      author_dao_delete_by_id(sqlite3 *db, int id);

#endif
