
#include <stdio.h>
#include "publisher_dao.h"

dao_status publisher_dao_create(DAOContext *ctx, const char *company_name, int *out_new_id){
    if(ctx == NULL){
        return DAO_ERROR_INVALID_ARGS;
    }

    sqlite3 *db = db_get_handle(ctx);
    if(!db | !company_name){
        return DAO_ERROR_INVALID_ARGS;
    }
    sqlite3_stmt *stmt = NULL;
    const char *sql = "INSERT INTO Publisher(company_name) VALUES (?);";

    dao_status status = DAO_ERROR_UNKNOWN;

    do {
        if(sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) != SQLITE_OK){
            status = DAO_ERROR_INVALID_ARGS;
            break;
        }

        if (sqlite3_bind_text(stmt, 1, company_name, -1, SQLITE_TRANSIENT) != SQLITE_OK) {
            status = DAO_ERROR_BIND;
            break;
        }

        if (sqlite3_step(stmt) != SQLITE_DONE) {
            status = DAO_ERROR_EXECUTE;
            break;
        }

        *out_new_id = (int) sqlite3_last_insert_rowid(db);
        status = DAO_SUCCESS;
    } while (0);

    if (stmt) {
        sqlite3_finalize(stmt);
    }

    return status;
}


