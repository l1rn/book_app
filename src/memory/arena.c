#include "arena.h"

#include <stdio.h>
#include <stdlib.h>

static void arena_grow(Arena* arena, size_t min_size) {
    size_t new_size = (min_size > ARENA_DEFAULT_BLOCK_SIZE) ? min_size : ARENA_DEFAULT_BLOCK_SIZE;

    MemoryBlock* new_block = (MemoryBlock*) malloc(sizeof(MemoryBlock));
    if (!new_block) {
        perror("Failed to allocate new MemoryBlock controller");
        return;
    }

    new_block->memory = (char*)malloc(new_size);
    if (!new_block->memory) {
        perror("Failed to allocate memory for new block in arena");
        free(new_block);
        return;
    }

    new_block->total_size = new_size;
    new_block->used_size = 0;
    new_block->next = NULL;
    if (arena->current_block) {
        arena->current_block->next = new_block;
    }

    arena->current_block = new_block;

    if (!arena->first_block) {
        arena->first_block = new_block;
    }
    printf("System: Arena grew. New block of size %zu bytes allocated.\n", new_size);
}

Arena* arena_create() {
    Arena* arena = (Arena*) malloc(sizeof(Arena));
    if (!arena) {
        perror("Failed to allocate arena");
        return NULL;
    }

    arena->first_block = NULL;
    arena->current_block = NULL;

    arena_grow(arena, ARENA_DEFAULT_BLOCK_SIZE);
    printf("System: arena created successfully");
    return arena;
}

void arena_destroy(Arena* arena) {
    if (!arena) return;

    MemoryBlock* current = arena->first_block;
    while (current) {
        MemoryBlock* next = current->next;
        free(current->memory);
        free(current);
        current = next;
    }

    free(arena);
    printf("System: Arena destroyed and all memory freed. \n");
}

void* arena_alloc(Arena* arena, size_t size) {
    if (!arena) return NULL;

    if (!arena->current_block || arena->current_block->used_size + size > arena->current_block->total_size) {
        arena_grow(arena, size);
    }

    if (!arena->current_block || arena->current_block->used_size + size > arena->current_block->total_size) {
        fprintf(stderr, "Error: Arena allocation failed, likely out of system memory. \n");
        return NULL;
    }

    void* ptr = arena->current_block->memory + arena->current_block->used_size;
    arena->current_block->total_size += size;
    return ptr;
}

void arena_reset(Arena* arena) {
    if (!arena) return;
    MemoryBlock* current = arena->current_block;
    while (current) {
        current->used_size = 0;
        current = current->next;
    }

    arena->current_block = arena->first_block;
    printf("System: Arena has been reset. \n");
}