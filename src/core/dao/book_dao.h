#ifndef BOOK_DAO_H
#define BOOK_DAO_H

#include "core/models/book.h"
#include "core/db/db.h"
#include "core/models/enum.h"

dao_status book_dao_create(
    DAOContext *ctx,
    const char isbn13[14],
    const char isbn10[11],
    const char *book_name,
    const char publication_date[11],
    int pages,
    int publisher_id
);

BookAuthor **book_and_author_find_all(DAOContext *context, Arena *a, int *out_count);

Book **book_dao_find_all(DAOContext *ctx, Arena *a, int *out_count);
#endif //BOOK_DAO_H
