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
        author->name = NULL;
        free(author->name);
        author->surname = NULL;
        free(author->surname);
        free(author);
    }
}

void free_authors(Author** authors) {

}

void print_author(const Author *author) {
    if (author) {
        printf("Author: %s %s\n", author->name, author->surname);
    }
}