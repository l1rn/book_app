
#ifndef BOOK_H
#define BOOK_H
#include "author.h"

struct Publisher;

typedef struct Book {
    int     isbn13;
    int     isbn10;
    char    *book_name;
    char    publication_date[11];
    int     pages;
    int     publisher_id;
    Author  *authors;
    int     author_count;
} Book;

Book *create_book(
    int isbn13,
    int isbn10,
    const char *book_name,
    const char *publication_date,
    int pages,
    int publisher_id,
    Author *authors,
    int author_count
);

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
);

void book_set_publisher(Book *b, const struct Publisher *p);

void book_add_author(Book *b, const Author *author);
void clear_all_authors(Book *b);

void print_book(Book *book);

#endif
