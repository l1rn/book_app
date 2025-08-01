#include "../include/author.h"
#include <string.h>
#include <stdio.h>

Author createAuthor(const char *name, const char *surname){
    Author a = { 0 };
    if (name) {
        strncpy(a.name, name, sizeof(a.name)-1);
        a.name[sizeof(a.name) - 1] = '\0';
    }
    if (surname) {
        strncpy(a.surname, surname, sizeof(a.surname)-1);
        a.surname[sizeof(a.surname) - 1] = '\0';
    }
    return a;
}

void printAuthor(const Author *author) {
    if (author) {
        printf("Author: %s %s\n", author->name, author->surname);
    }
}