#include "author.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

Author* author_create_model(const char *name, const char *surname){
    Author *author = (Author*) malloc(sizeof(Author));
    if (!author) return NULL;

    author->name = name ? strdup(name) : NULL;
    if (!author->name && name) {
        free(author);
        return NULL;
    }

    author->surname = surname ? strdup(name) : NULL;
    if (!author->surname && surname) {
        free(author->name);
        free(author);
        return NULL;
    }
    return author;
}

void free_author(Author *author) {
    if (author) {
        free(author->name);
        free(author->surname);
        free(author);
    }
}

void print_author(const Author *author) {
    if (author) {
        printf("Author: %s %s\n", author->name, author->surname);
    }
}