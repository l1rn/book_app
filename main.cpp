#include <QApplication>
#include <QPushButton>

#include "ui/mainwindow.h"

extern "C" {
#include "models/author.h"
#include "models/book.h"
}

int main(int argc, char *argv[]) {
    Author a = createAuthor("Brian", "Kelly");
    printAuthor(&a);
    Book book = createBook(123, 123, "Game of Thrones", "22.10.2004", 333);
    printBook(&book);
    return 0;
}
