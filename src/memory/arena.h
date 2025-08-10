#ifndef ARENA_H
#define ARENA_H
#include <stddef.h>

#define ARENA_DEFAULT_BLOCK_SIZE 4096

typedef struct MemoryBlock {
    char* memory;
    size_t total_size;
    size_t used_size;
    struct MemoryBlock* next;
} MemoryBlock;

typedef struct Arena {
    MemoryBlock* first_block;
    MemoryBlock* current_block;
} Arena;

Arena* create_create();
void arena_destroy(Arena* arena);
void* arena_alloc(Arena* arena, size_t size);
void arena_reset(Arena* arena);
#endif //ARENA_H
