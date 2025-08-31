#ifndef ENUM_H
#define ENUM_H

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

#endif
