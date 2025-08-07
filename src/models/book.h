
#ifndef BOOK_H
#define BOOK_H
#include "author.h"

struct Publisher;

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

Book create_book(int isbn13,
                int isbn10,
                const char *bookName,
                const char *publicationDate,
                int pages);
void book_set_publisher(Book *b, const struct Publisher *p);

void book_add_author(Book *b, const Author *author);
void clear_all_authors(Book *b);

void print_book(Book *book);

#endif
