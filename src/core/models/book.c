#include "book.h"
#include "author.h"
#include "publisher.h"

#include "string.h"
#include <stdio.h>
#include <stdlib.h>

Book *create_book(const int isbn13, const int isbn10, const char *bookName, const char *publicationDate, const int pages) {
    Book b = { 0 };
    b.isbn13 = isbn13;
    b.isbn10 = isbn10;

    strncpy(b.book_name, bookName, sizeof b.book_name - 1);
    strncpy(b.publication_date, publicationDate, sizeof b.publication_date - 1);
    b.pages = pages;

    b.publisher_id = 0;
    b.authors = NULL;
    b.author_count = 0;

    return b;
}

Book* book_create_in_arena(
    Arena *arena,
    int isbn13,
    int isbn10,
    char *book_name,
    const char publication_date[11],
    int pages,
    int publisher_id,
    Author *authors,
    int author_count
) {
    Book *b = (Book *) arena_alloc(arena, sizeof(Book));
    if (!b) return NULL;
    b->isbn13 = isbn13;
    b->isbn10 = isbn10;
    b->book_name = book_name;
    memcpy(b->publication_date, publication_date, 11);
    b->pages = pages;
    b->publisher_id = publisher_id;
    b->authors = authors;
    b->author_count = author_count;

    if (!b->isbn13 && !b->isbn10 && !b->book_name && !b->pages && !b->publisher_id && !b->authors && !b->author_count) {
        return NULL;
    }

    return b;
}

void book_set_publisher(Book *b, const Publisher *p) {
    b->publisher_id = p->id;
}

void clear_all_authors(Book *b) {
    free(b->authors);
    b->authors = NULL;
    b->author_count = 0;
}

void book_add_author(Book *b, const Author *author) {
    b->authors[b->author_count++] = *author;
}

void print_book(Book *book) {
    printf("ISBN-13: %d", book->isbn13);

    printf("\nName: %s\n", book->book_name);
    printf("Pages: %d\n", book->pages);

    if (book->publisher_id)
        printf("Publisher: %d\n", book->publisher_id);
    else
        puts("Publisher: (none)");

    printf("Authors (%d):\n", book->author_count);
    for (int i = 0; i < book->author_count; i++) {
        printf("  %s %s\n",
               book->authors[i].name,
               book->authors[i].surname);
    }
}