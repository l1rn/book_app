#include "author.h"
#include <string.h>
#include <stdio.h>

Author create_author(const char *name, const char *surname){
    Author a;
    strncpy(a.name, name, sizeof(a.name)-1);
    strncpy(a.surname, surname, sizeof(a.surname)-1);
    return a;
}

void print_author(const Author *author) {
    printf("Author: %s %s\n", author->name, author->surname);
}