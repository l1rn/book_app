#include "dao_handle.h"

#include <stddef.h>
#include <stdio.h>

void handle_dao_sql_error(dao_status status) {
    const char *msg = NULL;
    switch (status) {
        case DAO_ERROR_PREPARE:
            msg = "SQL prepare failed.";
            break;
        case DAO_ERROR_EXECUTE:
            msg = "SQL execution failed.";
            break;
        case DAO_ERROR_BIND:
            msg = "SQL bind failed.";
            break;
        case DAO_ERROR_NOT_FOUND:
            msg  = "Record not found.";
            break;
        case DAO_ERROR_UNKNOWN:
            msg = "Unknown error";
            break;
        case DAO_ALREADY_EXIST:
            msg = "Record already exist";
            break;
        default:
            msg = "Unknown error.";
            break;
    }

    fprintf(stderr, "%s %s\n", msg);
}