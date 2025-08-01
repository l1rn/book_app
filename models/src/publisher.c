#include "../include/publisher.h"
#include <stdio.h>
#include <string.h>

Publisher createPublisher(const char* name) {
    Publisher p = { 0 };
    strncpy(p.companyName, name, sizeof p.companyName-1);
    p.bookCount = 0;
    p.books = NULL;

    return p;
}

void printPublisher(const Publisher *publisher) {
    if (publisher) {
        printf("Publisher: %s (ID: %d, Books: %d)\n", publisher->companyName, publisher->id, publisher->bookCount);
        for (int i = 0; i < publisher->bookCount; i++) {
            printf("    Book %d:", i + 1);
        }
    }
}