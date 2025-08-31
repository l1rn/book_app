#include "publisher.h"
#include <string.h>

Publisher *create_publisher_in_arena(Arena *arena, const char *name) {
    Publisher *p = arena_alloc(arena, sizeof(Publisher));

}

Publisher create_publisher(const char* name) {
    Publisher p = { 0 };
    strncpy(p.company_name, name, sizeof p.company_name-1);
    p.book_count = 0;
    p.books = NULL;

    return p;
}
