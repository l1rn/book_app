#include <QApplication>
#include <QPushButton>

#include "ui/mainwindow.h"

extern "C" {
#include "models/include/author.h"
#include "models/include/book.h"
#include "models/include/publisher.h"
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
    return 0;
}
