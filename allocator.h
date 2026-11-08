#ifndef ALLOCATOR_H
#define ALLOCATOR_H

#include <stddef.h>
#include <stdbool.h>

typedef struct memory_block {
    size_t size;
    bool is_free;
    struct memory_block* next;
} memory_block;

void init_heap();
void* k_malloc(size_t size_requested);
void k_free(void* ptr);

#endif