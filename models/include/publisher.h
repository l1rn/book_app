#ifndef PUBLISHER_H
#define PUBLISHER_H

struct Book;

typedef struct Publisher{
    struct Book *books;
    int bookCount;
    char company_name[120];
} Publisher;

Publisher createPublisher(const char* name);
#endif
