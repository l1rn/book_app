#ifndef ARENA_H
#define ARENA_H
#include <stddef.h>

#define ARENA_MAX_SIZE (10 * 1024 * 1024)
#define ALIGN_UP(v, a) (((v) + ((a) - 1)) & ~((size_t)((a) - 1)))

typedef struct Arena {
    char *buffer;
    size_t capacity;
    size_t offset;
} Arena;

Arena* arena_create(size_t capacity);
void arena_destroy(Arena *a);
void* arena_alloc(Arena *a, size_t size);
void arena_reset(Arena *a);

char* arena_strdup(Arena *a, const unsigned char *s);
#endif //ARENA_H
