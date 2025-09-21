//
// Created by l1rn
//

#ifndef BOOKSERVICE_H
#define BOOKSERVICE_H
#include <vector>

extern "C" {
#include    "core/db/db.h"
#include    "core/memory/arena_api.h"
#include    "core/models/book.h"
#include    "core/dao/book_dao.h"
#include <string.h>
}

#include "string"

class BookService {
public:
    BookService(DAOContext *ctx, Arena *a);

    Book createBook(
        std::string isbn13,
        std::string isbn10,
        std::string bookName,
        std::string publicationDate,
        int pages,
        int publisherId
    );

    void getAllBooks(std::vector<Book>& books);
    void printAllBooks();
private:
    DAOContext *_ctx;
    Arena *_a;
};



#endif //BOOKSERVICE_H
