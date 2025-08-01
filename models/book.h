
#ifndef BOOK_H
#define BOOK_H

typedef struct {
    int isbn13[13];
    int isbn10[10];
    char publicationDate[10];
    int pages;
    Publisher *publisher;
    Author *authors;
    int authorCount;
} Book;


#endif
