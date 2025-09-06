#include "book_dao.h"
#include <stdlib.h>
#include <stdio.h>

int book_dao_count(sqlite3 *db) {
    sqlite3_stmt *stmt = NULL;
    const char *sql = "SELECT COUNT(*) FROM Book;";
    int count = 0;
    if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) != SQLITE_OK) {
        return -1;
    }

    int rc = sqlite3_step(stmt);
    if (rc == SQLITE_ROW) {
        count = sqlite3_column_int(stmt, 0);
    }

    if (stmt) {
        sqlite3_finalize(stmt);
    }
    return count;
}

int book_and_author_dao_count(sqlite3 *db) {
    sqlite3_stmt *stmt = NULL;
    const char *sql = "SELECT COUNT(*) FROM BookAuthor";
    int count = 0;
    if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) != SQLITE_OK) {
        return -1;
    }

    int rc = sqlite3_step(stmt);
    if (rc == SQLITE_ROW) {
        count = sqlite3_column_int(stmt, 0);
    }

    if (sqlite3_step(stmt) != SQLITE_DONE) {
        return -1;
    }

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

BookAuthor **book_and_author_dao_find_all(DAOContext *ctx, Arena *a, int *out_count) {
    if (!ctx || !a) return NULL;

    sqlite3 *db = db_get_handle(ctx);
    if (!db) return NULL;
    sqlite3_stmt *stmt = NULL;

    int linked_book_count = book_and_author_dao_count(db);
    if (linked_book_count == 0) {
        return NULL;
    }

    const char *sql = "SELECT isbn13, author_id FROM BookAuthor;";
    if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) != SQLITE_OK) {
        goto fail;
    }

    BookAuthor **books_authors = (BookAuthor **) malloc(sizeof(BookAuthor *) * linked_book_count);
    if (!books_authors) {
        goto fail;
    }

    int rc, i = 0;

    while ((rc = sqlite3_step(stmt)) == SQLITE_ROW) {
        BookAuthor *ba = book_author_create_in_arena(
            a,
            (const char*) sqlite3_column_text(stmt, 0),
            sqlite3_column_int(stmt, 1)
        );
        if (!ba) return NULL;
        books_authors[i++] = ba;
    }

    if (rc != SQLITE_DONE) {
        goto fail;
    }

    if (stmt) {
        sqlite3_finalize(stmt);
    }
    if (out_count) *out_count = i;

    return books_authors;
    fail:
        if (stmt) sqlite3_finalize(stmt);
        arena_reset(a);
        arena_destroy(a);
        free(books_authors);
        return NULL;
}

Book **book_dao_find_all(DAOContext *ctx, Arena *a, int *out_count) {
    if (!ctx || !a) return NULL;

    sqlite3 *db = db_get_handle(ctx);
    if (!db) return NULL;

    int book_count = book_dao_count(db);

    if (book_count == 0) {
        return NULL;
    }

    Book **books = (Book**) malloc(sizeof(Book *) * book_count);
    if (!books) goto fail;

    sqlite3_stmt *stmt = NULL;
    const char *sql = "SELECT isbn13, isbn10, book_name, publication_date, pages, publisher_id FROM Book;";
    int rc, i = 0;

    if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) != SQLITE_OK) {
        goto fail;
    }

    while ((rc = sqlite3_step(stmt)) == SQLITE_ROW) {
        Book *b = book_create_in_arena(
            a,
            (const char*)sqlite3_column_text(stmt, 1),
            (const char*)sqlite3_column_text(stmt, 2),
            (char*)sqlite3_column_text(stmt, 3),
            (const char*)sqlite3_column_text(stmt, 4),
            sqlite3_column_int(stmt, 5),
            sqlite3_column_int(stmt, 6),
            NULL,
            0
        );
        if (!b) {
            return NULL;
        }
        books[i++] = b;
    }

    if (rc != SQLITE_DONE) {
        goto fail;
    }
    if (stmt) sqlite3_finalize(stmt);

    if (out_count) *out_count = i;
    return books;
    fail:
        if (stmt) sqlite3_finalize(stmt);
        arena_reset(a);
        arena_destroy(a);
        free(books);
        return NULL;
}