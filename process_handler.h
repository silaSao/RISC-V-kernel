#ifndef PROCESS_HANDLER_H
#define PROCESS_HANDLER_H

#include <stdint.h>

#define MAX_PROCESS_COUNT 10

typedef enum {
    PROCESS_READY,
    PROCESS_ACTIVE,
    PROCESS_BLOCKED,
} Process_Status;

typedef struct {
    uint64_t registers[32];
    char* stack_memory_ptr;
    Process_Status status;
} Process;

void create_process(void (*entry_point)());
void yield();
extern void switch_context(Process* old_process, Process* new_process);

#endif