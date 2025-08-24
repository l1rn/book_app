#ifndef PUBLISHER_H
#define PUBLISHER_H

struct Book;

typedef struct Publisher{
    int id;
    struct Book *books;
    int bookCount;
    int bookCapacity;
    char* companyName;
} Publisher;

Publisher create_publisher(const char* name);
void print_publisher(const Publisher *publisher);
void clear_publisher_books(Publisher *p);
void free_publisher(Publisher *p);

#endif
