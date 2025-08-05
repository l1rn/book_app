
#ifndef AUTHOR_H
#define AUTHOR_H

typedef struct {
    int id;
    char* name;
    char* surname;
} Author;

Author create_author(const char *name, const char *surname);
void print_author(const Author *author);

#endif
