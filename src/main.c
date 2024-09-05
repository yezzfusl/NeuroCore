#include "cpu_arch.h"
#include "cpu/instruction_set.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

extern cpu_state_t *cpu_init();
extern void cpu_cycle(cpu_state_t *cpu, uint8_t *memory);
extern void cpu_destroy(cpu_state_t *cpu);

#define MEMORY_SIZE 1024 * 1024  // 1 MB of memory

static void init_memory(uint8_t *memory) {
    uint64_t *instr = (uint64_t *)memory;
    
    // ADD R1, R2, R3
    instr[0] = (uint64_t)OPCODE_ADD << 56 | 1 << 52 | 2 << 48 | 3 << 44;
    
    // SUB R4, R5, R6
    instr[1] = (uint64_t)OPCODE_SUB << 56 | 4 << 52 | 5 << 48 | 6 << 44;
    
    // MUL R7, R8, R9
    instr[2] = (uint64_t)OPCODE_MUL << 56 | 7 << 52 | 8 << 48 | 9 << 44;
    
    // LOAD R10, 42
    instr[3] = (uint64_t)OPCODE_LOAD << 56 | 10 << 52 | 42;
}

int main() {
    cpu_state_t *cpu = cpu_init();
    if (!cpu) {
        fprintf(stderr, "Failed to initialize CPU\n");
        return 1;
    }

    uint8_t *memory = (uint8_t *)calloc(MEMORY_SIZE, sizeof(uint8_t));
    if (!memory) {
        fprintf(stderr, "Failed to allocate memory\n");
        cpu_destroy(cpu);
        return 1;
    }

    init_memory(memory);

    // Run 4 CPU cycles to execute the instructions
    for (int i = 0; i < 4; i++) {
        cpu_cycle(cpu, memory);
    }

    printf("CPU executed 4 cycles\n");
    printf("R1: 0x%016lx\n", cpu->r[1]);
    printf("R4: 0x%016lx\n", cpu->r[4]);
    printf("R7: 0x%016lx\n", cpu->r[7]);
    printf("R10: 0x%016lx\n", cpu->r[10]);

    cpu_destroy(cpu);
    free(memory);

    return 0;
}

