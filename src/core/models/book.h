
#ifndef BOOK_H
#define BOOK_H
#include "author.h"

struct Publisher;
typedef struct BookAuthor {
    char        isbn13[14];
    int         author_id;
} BookAuthor;

typedef struct Book {
    char        isbn13[14];
    char        isbn10[11];
    char        *book_name;
    char        publication_date[11];
    int         pages;
    int         publisher_id;
    Author      *authors;
    int         author_count;
} Book;

// Book *create_book(
//     int isbn13,
//     int isbn10,
//     const char *book_name,
//     const char *publication_date,
//     int pages,
//     int publisher_id,
//     Author *authors,
//     int author_count
// );

Book* book_create_in_arena(
    Arena *arena,
    const char isbn13[14],
    const char isbn10[11],
    char *book_name,
    const char publication_date[11],
    int pages,
    int publisher_id,
    Author *authors,
    int author_count
);

BookAuthor *book_author_create_in_arena(
    Arena      *a,
    const char isbn[14],
    int        author_id
);

void book_set_publisher(Book *b, const struct Publisher *p);

void book_add_author(Book *b, const Author *author);
void clear_all_authors(Book *b);

void print_book(Book *book);

#endif
