
#ifndef AUTHOR_DAO_H
#define AUTHOR_DAO_H

#include "author.h"
typedef enum failure_status {
    FAIL_NONE = 0,
    FAIL_PREPARE,
    FAIL_EXECUTE,
    FAIL_BIND,
    FAIL_NOT_FOUND,
    FAIL_MEMORY_ALLOC,
    FAIL_ALREADY_EXIST
} failure_status;

failure_status  author_dao_create(Author *author);
Author*          author_dao_find_by_id(int id);
Author**        author_dao_find_all(int *out_count);
int                  author_dao_count();
failure_status  author_dao_delete_by_id(int id);

#endif
