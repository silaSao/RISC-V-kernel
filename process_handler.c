#include <stdbool.h>
#include "process_handler.h"
#include "io.h"
#include "allocator.h"

static Process processes[MAX_PROCESS_COUNT];
static int process_count = 0;
static int current_process = 0;

void create_process(void (*entry_point)()) {
    if (process_count >= MAX_PROCESS_COUNT) {
        print("ERROR: MAX PROCESS COUNT");
        return;
    }
    Process* process = &processes[process_count];
    process_count++;
    process->stack_memory_ptr = k_malloc(4096);

    for (int i = 0; i < 32; i++) {
        process->registers[i] = 0;
    }
    process->registers[1] = (uint64_t)entry_point;
    process->registers[2] = (uint64_t)(process->stack_memory_ptr + 4096);

    process->status = PROCESS_READY;

    print("Created process ");
    print_int(process_count - 1);
    print("\n");
}

void kill_process(int process_id) {
    if (process_id >= process_count) {
        print("ERROR: INVALID PROCESS ID\n");
        return;
    }

    Process* process = &processes[process_id];
    k_free(process->stack_memory_ptr);
    process->status = PROCESS_BLOCKED;

    if (process_id == current_process) {
        yield();
    }
}

void yield() {
    int old = current_process;
    int next = (current_process + 1) % process_count;
    
    while (next != old && processes[next].status != PROCESS_READY) {
        next = (next + 1) % process_count;
    }
    
    if (processes[next].status != PROCESS_READY) {
        print("No processes ready! Hanging...\n");
        while (1);
    }
    
    current_process = next;
    switch_context(&processes[old], &processes[current_process]);
}
