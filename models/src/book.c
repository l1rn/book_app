#include "book.h"
#include "author.h"
#include "publisher.h"

#include "string.h"
#include <stdio.h>
#include <stdlib.h>

Book create_book(const int isbn13, const int isbn10, const char *bookName, const char *publicationDate, const int pages) {
    Book b = { 0 };
    b.isbn13 = isbn13;
    b.isbn10 = isbn10;

    strncpy(b.bookName, bookName, sizeof b.bookName - 1);
    strncpy(b.publicationDate, publicationDate, sizeof b.publicationDate - 1);
    b.pages = pages;

    b.publisherId = 0;
    b.authors = NULL;
    b.authorCount = 0;

    return b;
}

void book_set_publisher(Book *b, const Publisher *p) {
    b->publisherId = p->id;
}

void clear_all_authors(Book *b) {
    free(b->authors);
    b->authors = NULL;
    b->authorCount = 0;
    b->authorCapacity = 0;
}

void book_add_author(Book *b, const Author *author) {
    if (b->authorCount >= b->authorCapacity) {
        const int newCapacity = b->authorCapacity == 0 ? 2 : b->authorCapacity * 2;
        Author *tmp = realloc(b->authors, newCapacity * sizeof(Author));
        if (!tmp) {
            perror("Failed to expand authors array");
            return;
        }
        b->authors = tmp;
        b->authorCapacity = newCapacity;
    }

    b->authors[b->authorCount++] = *author;
}

void print_book(Book *book) {
    printf("ISBN-13: %d", book->isbn13);

    printf("\nName: %s\n", book->bookName);
    printf("Pages: %d\n", book->pages);

    if (book->publisherId)
        printf("Publisher: %d\n", book->publisherId);
    else
        puts("Publisher: (none)");

    printf("Authors (%d):\n", book->authorCount);
    for (int i = 0; i < book->authorCount; i++) {
        printf("  %s %s\n",
               book->authors[i].name,
               book->authors[i].surname);
    }
}