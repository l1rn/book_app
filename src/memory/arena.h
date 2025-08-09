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
#endif //ARENA_H
