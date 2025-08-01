
#ifndef BOOK_H
#define BOOK_H
#include "author.h"

typedef struct Publisher;

typedef struct Book {
    int     isbn13;
    int     isbn10;
    char    bookName[500];
    char    publicationDate[11];
    int     pages;
    int     publisherId;
    Author  *authors;
    int     authorCount;
    int     authorCapacity;
} Book;

Book createBook(int isbn13,
                int isbn10,
                const char *bookName,
                const char *publicationDate,
                int pages);
void bookSetPublisher(Book *b, const struct Publisher *p);

void bookAddAuthor(Book *b, const Author *author);
void clearAllAuthors(Book *b);

void printBook(Book *book);

#endif
