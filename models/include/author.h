
#ifndef AUTHOR_H
#define AUTHOR_H


typedef struct {
    int id;
    char surname[50];
    char name[50];
} Author;

Author createAuthor(const char *name, const char *surname);
void printAuthor(const Author *author);

#endif
