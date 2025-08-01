#ifndef PUBLISHER_H
#define PUBLISHER_H

struct Book;

typedef struct Publisher{
    int id;
    struct Book *books;
    int bookCount;
    int bookCapacity;
    char companyName[120];
} Publisher;

Publisher createPublisher(const char* name);
void printPublisher(const Publisher *publisher);
void clearPublisherBooks(Publisher *p);
#endif
