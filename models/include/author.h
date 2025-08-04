
#ifndef AUTHOR_H
#define AUTHOR_H


typedef struct {
    int id;
    char surname[50];
    char name[50];
} Author;

Author create_author(const char *name, const char *surname);
void print_author(const Author *author);

#endif
