#include "author.h"
#include "arena.h"

#include <string.h>
#include <stdio.h>
#include <stdlib.h>

static char* arena_strdup(Arena* arena, const unsigned char* s) {
    if (!s) return NULL;
    size_t len = strlen((const char *)s) + 1;
    char* new_str = (char *) arena_alloc(arena, len);
    if (new_str) {
        memcpy(new_str, s, len);
    }
    return new_str;
}

Author* author_create_in_arena(Arena* arena, const unsigned char* name, const unsigned char* surname) {
    Author* author = (Author*) arena_alloc(arena, sizeof(Author));
    if (!author) return NULL;
    author->name = arena_strdup(arena, name);
    author->surname = arena_strdup(arena, surname);

    if ((name && ! author->name) || (surname && !author->surname)) {
        return NULL;
    }
    return author;
}

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