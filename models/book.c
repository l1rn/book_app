#include "book.h"
#include "author.h"
#include "string.h"
#include <stdio.h>

Book createBook(const int isbn13, const int isbn10, const char *bookName, const char *publicationDate, const int pages) {
    Book b = { 0 };
    b.isbn13 = isbn13;
    b.isbn10 = isbn10;

    strncpy(b.bookName, bookName, sizeof b.bookName - 1);
    strncpy(b.publicationDate, publicationDate, sizeof b.publicationDate - 1);
    b.pages = pages;

    b.publisher = NULL;
    b.authors = NULL;
    b.authorCount = 0;

    return b;
}

// void bookSetPublisher(Book *b, Publisher *p) {
//     b->publisher = p;
// }
//
// void bookSetAuthors(Book *b, Author *authors, int count) {
//     b->authors = authors;
//     b->authorCount = count;
// }

void printBook(Book *book) {
    printf("ISBN-13: %d", book->isbn13);

    printf("\nName: %s\n", book->bookName);
    printf("Pages: %d\n", book->pages);

    if (book->publisher)
        printf("Publisher: %s\n", book->publisher->company_name);
    else
        puts("Publisher: (none)");

    printf("Authors (%d):\n", book->authorCount);
    for (int i = 0; i < book->authorCount; i++) {
        printf("  %s %s\n",
               book->authors[i].name,
               book->authors[i].surname);
    }
}