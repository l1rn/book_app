#ifndef PUBLISHER_H
#define PUBLISHER_H

#include "core/memory/arena_api.h"

struct Book;

typedef struct Publisher{
    int id;
    int book_count;
    char* company_name;
    struct Book *books;
} Publisher;

Publisher publisher_create_in_arena(Arena *arena, const char *name);
Publisher create_publisher(const char* name);
#endif
