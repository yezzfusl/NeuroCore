#include "cpu_arch.h"
#include "cpu/instruction_set.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MEMORY_SIZE (1024 * 1024 * 1024)  // 1 GB of memory

static void init_memory(memory_context_t *ctx) {
    if (!ctx) {
        printf("Error: NULL memory context in init_memory\n");
        return;
    }

    uint64_t addr = 0;
    
    printf("Writing ADD instruction\n");
    memory_write_byte(ctx, addr++, OPCODE_ADD);
    memory_write_byte(ctx, addr++, (1 << 4) | 2);
    memory_write_byte(ctx, addr++, 3 << 4);
    addr += 5; // Padding
    
    printf("Writing SUB instruction\n");
    memory_write_byte(ctx, addr++, OPCODE_SUB);
    memory_write_byte(ctx, addr++, (4 << 4) | 5);
    memory_write_byte(ctx, addr++, 6 << 4);
    addr += 5; // Padding
    
    printf("Writing MUL instruction\n");
    memory_write_byte(ctx, addr++, OPCODE_MUL);
    memory_write_byte(ctx, addr++, (7 << 4) | 8);
    memory_write_byte(ctx, addr++, 9 << 4);
    addr += 5; // Padding
    
    printf("Writing LOAD instruction\n");
    memory_write_byte(ctx, addr++, OPCODE_LOAD);
    memory_write_byte(ctx, addr++, 10 << 4);
    memory_write_byte(ctx, addr++, 42);
    addr += 5; // Padding

    printf("Memory initialized\n");
}

int main() {
    printf("Starting CPU initialization\n");
    cpu_state_t *cpu = cpu_init(MEMORY_SIZE);
    if (!cpu) {
        fprintf(stderr, "Failed to initialize CPU\n");
        return 1;
    }
    printf("CPU initialized successfully\n");

    if (!cpu->memory_ctx) {
        fprintf(stderr, "Error: NULL memory context after CPU initialization\n");
        cpu_destroy(cpu);
        return 1;
    }

    printf("Initializing memory\n");
    init_memory(cpu->memory_ctx);

    printf("Starting CPU cycles\n");
    // Run 4 CPU cycles to execute the instructions
    for (int i = 0; i < 4; i++) {
        printf("Cycle %d\n", i+1);
        cpu_cycle(cpu);
    }

    printf("CPU executed 4 cycles\n");
    printf("R1: 0x%016lx\n", cpu->r[1]);
    printf("R4: 0x%016lx\n", cpu->r[4]);
    printf("R7: 0x%016lx\n", cpu->r[7]);
    printf("R10: 0x%016lx\n", cpu->r[10]);

    cpu_destroy(cpu);
    printf("CPU destroyed\n");

    return 0;
}

