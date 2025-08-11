#include "arena.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Arena* arena_create(size_t capacity) {
    Arena *a = malloc(sizeof(Arena));
    if (!a) return NULL;
    a->buffer = malloc(capacity);
    if (!a->buffer) { free(a); return NULL;}
    a->capacity = capacity;
    a->offset = 0;
    return a;
}

void arena_destroy(Arena *a) {
    if (!a) return;
    free(a->buffer);
    free(a);
    printf("System: Arena destroyed and all memory freed. \n");
}

void* arena_alloc(Arena *a, size_t size) {
    if (!a) return NULL;
    size = ALIGN_UP(size, sizeof(void*));
    if (a->offset + size > a->capacity) return NULL;
    void *p = a->buffer + a->offset;
    a->offset += size;
    return p;
}

void arena_reset(Arena *a) {
    if (!a) return;
    a->offset = 0;
}

char* arena_strdup(Arena *a, const unsigned char *s) {
    if (!a || !s) return NULL;
    size_t len = strlen((const char *)s) + 1;
    char *dst = (char *) arena_alloc(a, len);
    if (!dst) return NULL;
    memcpy(dst, s, len);
    return dst;
}