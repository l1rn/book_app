
#ifndef AUTHOR_DAO_H
#define AUTHOR_DAO_H

#include "author.h"
typedef enum failure_status {
    FAIL_NONE = 0,
    FAIL_PREPARE,
    FAIL_EXECUTE,
    FAIL_BIND,
    FAIL_NOT_FOUND
} failure_status;

failure_status author_dao_create(Author *author);
failure_status author_dao_find_by_id(Author *author);
failure_status author_dao_find_all();

#endif 
