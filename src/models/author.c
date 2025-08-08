#include "author.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

Author* author_create_model(const unsigned char *name, const unsigned char *surname){
    Author *author = (Author*) malloc(sizeof(Author));
    if (!author) return NULL;

    author->name = name ? strdup((const char *)name) : NULL;

    author->surname = surname ? strdup((const char *)surname) : NULL;

    if (!author->name && !author->surname) {
        free_author(author);
        return NULL;
    }
    return author;
}

void free_author(Author *author) {
    if (author) {
        if (author->name) {
            free(author->name);
            author->name = NULL;
        }
        if (author->surname) {
            free(author->surname);
            author->surname = NULL;
        }
        free(author);
    }
}

void free_authors(Author** authors, int count) {
    if (authors) {
        for (int i = 0; i < count; i++) {
            free_author(authors[i]);
        }
        free(authors);
    }
}

void print_author(const Author *author) {
    if (author) {
        printf("Author: %s %s\n", author->name, author->surname);
    }
}