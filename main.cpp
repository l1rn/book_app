#include <iostream>
#include <QApplication>

extern "C" {
#include "models/include/author.h"
#include "models/include/book.h"
#include "models/include/publisher.h"
#include "data/db.h"
}

int main(int argc, char *argv[]) {
    Author a = createAuthor("Brian", "Kelly");
    printAuthor(&a);

    Book book = createBook(123, 123, "Game of Thrones", "22.10.2004", 333);
    Publisher publisher = createPublisher("Super book publisher");
    bookSetPublisher(&book, &publisher);
    bookAddAuthor(&book, &a);
    bookAddAuthor(&book, &a);
    bookAddAuthor(&book, &a);
    printBook(&book);
    clearAllAuthors(&book);
    printBook(&book);

    if (dbInit("/home/lirn/CLionProjects/book_app/data/schemes/001_init.sql") != 0) {
        std::cerr << "Database schema init failed.\n";
        dbClose();
        return 1;
    }

    std::cout << "Database ready!\n";

    dbClose();
    return 0;
}
