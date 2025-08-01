
#ifndef BOOK_H
#define BOOK_H
#include "author.h"

struct Publisher;

typedef struct {
    int     isbn13;
    int     isbn10;
    char    bookName[500];
    char    publicationDate[10];
    int     pages;
    struct Publisher *publisher;
    Author  *authors;
    int     authorCount;
} Book;
struct Publisher{
    Book *books;
    char company_name[120];
};

Book createBook(const int isbn13,
                const int isbn10,
                const char *bookName,
                const char *publicationDate,
                const int pages);
// void bookSetPublisher(Book *b, Publisher *p);
// void bookSetAuthors(Book *b, Author *authors, int count);
void printBook(Book *book);

#endif
