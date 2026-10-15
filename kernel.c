#include <stdbool.h>
#include "allocator.h"
#include "io.h"
#include "process_handler.h"

#include <stdint.h>
#include "str.h"


void task_a() {
    while (1) {
        print("A");
        yield();
    }
}

void task_b() {
    while (1) {
        print("B");
        yield();
    }
}

void kernel_main() {
    init_heap();

    create_process(task_a);
    create_process(task_b);

    task_a();

    print("\nReached EOF, Hanging\n");
    while (1);
}