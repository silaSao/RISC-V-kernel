#include <stdbool.h>
#include "allocator.h"

static char heap[2048 * 2048];
static bool initalized = false;
static memory_block* free_list;

void init_heap() {
    if (initalized) return;

    free_list = (memory_block*)heap;
    free_list->size = sizeof(heap) - sizeof(memory_block);
    free_list->is_free = true;
    free_list->next = NULL;

    initalized = true;
}

void* k_malloc(size_t size_requested) {
    memory_block* current = free_list;
    while (current != NULL) {
        if (current->is_free && current->size >= size_requested) {
            memory_block* node = (memory_block*)((char*)(current + 1) + size_requested);
            node->size = current->size - sizeof(memory_block) - size_requested;
            node->is_free = true;
            node->next = current->next;

            current->is_free = false;
            current->size = size_requested;
            current->next = node;

            return (void*)(current + 1);
        }
        current = current->next;
    }
    return NULL;
}

void k_free(void* ptr) {
    if (ptr == NULL) return;
    memory_block* block_data = (memory_block*)(ptr)-1;
    block_data->is_free = true;

    while (block_data->next != NULL && block_data->next->is_free) {
        block_data->size += sizeof(memory_block) + block_data->next->size;
        block_data->next = block_data->next->next;
    }
}
