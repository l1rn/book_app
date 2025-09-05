#include "book_dao.h"
#include <stdio.h>

int book_dao_count(sqlite3 *db) {
    sqlite3_stmt *stmt = NULL;
    const char *sql = "SELECT COUNT(*) FROM Book;";
    int count = 0;
    if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) != SQLITE_OK) {
        return 0;
    }

    if (sqlite3_step(stmt) != SQLITE_DONE) {
        return 0;
    }
    count = sqlite3_column_int(stmt, 0);

    if (stmt) {
        sqlite3_finalize(stmt);
    }
    return count;
}

dao_status book_dao_create(
    DAOContext *ctx,
    const char isbn13[14],
    const char isbn10[11],
    const char *book_name,
    const char publication_date[11],
    int pages,
    int publisher_id
) {
    if (ctx == NULL) {
        return DAO_ERROR_INVALID_ARGS;
    }

    sqlite3 *db = db_get_handle(ctx);
    if (!db | !isbn13 | !isbn10 | !book_name | !publication_date | !pages | !publisher_id) {
        return DAO_ERROR_INVALID_ARGS;
    }

    sqlite3_stmt *stmt = NULL;
    const char *sql = "INSERT INTO Book (isbn13, isbn10, book_name, publication_date, pages, publisher_id)"
                      "VALUES(?, ?, ?, ?, ?, ?);";

    dao_status status = DAO_ERROR_UNKNOWN;
    do {
        if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) != SQLITE_OK) {
            status = DAO_ERROR_PREPARE;
            break;
        }

        if (sqlite3_bind_text(stmt, 1, isbn13, -1, SQLITE_STATIC) ||
            sqlite3_bind_text(stmt, 2, isbn10, -1, SQLITE_STATIC) ||
            sqlite3_bind_text(stmt, 3, book_name, -1, SQLITE_STATIC) ||
            sqlite3_bind_text(stmt, 4, publication_date, -1, SQLITE_STATIC) ||
            sqlite3_bind_int(stmt, 5, pages) ||
            sqlite3_bind_int(stmt, 6, publisher_id) != SQLITE_OK) {
            status = DAO_ERROR_BIND;
            break;
        }

        if (sqlite3_step(stmt) != SQLITE_DONE) {
            status = DAO_ERROR_EXECUTE;
            break;
        }

        status = DAO_SUCCESS;

    } while (0);

    if (stmt) {
        sqlite3_finalize(stmt);
    }
    return status;
}

Book *book_dao_find_all(DAOContext *ctx, Arena *a, int *out_count) {
    if (!ctx || !a) return NULL;

    sqlite3 *db = db_get_handle(ctx);
    if (!db) return NULL;

    printf("\ncounted books: %d\n", book_dao_count(db));

    sqlite3_stmt *stmt = NULL;

    return NULL;
}