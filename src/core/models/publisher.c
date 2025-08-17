#include "publisher.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Publisher create_publisher(const char* name) {
    Publisher p = { 0 };
    strncpy(p.companyName, name, sizeof p.companyName-1);
    p.bookCount = 0;
    p.books = NULL;

    return p;
}

void print_publisher(const Publisher *publisher) {
    if (publisher) {
        printf("Publisher: %s (ID: %d, Books: %d)\n", publisher->companyName, publisher->id, publisher->bookCount);
        for (int i = 0; i < publisher->bookCount; i++) {
            printf("    Book %d:", i + 1);
        }
    }
}

void free_publisher(Publisher *p) {
    if (p) {
        if (p->companyName) {
            free(p->companyName);
            p->companyName = NULL;
        }
        if (p->books) {
            free(p->books);
        }
    }
}