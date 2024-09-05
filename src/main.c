#include "cpu_arch.h"
#include <stdio.h>
#include <stdlib.h>

extern cpu_state_t *cpu_init();
extern void cpu_cycle(cpu_state_t *cpu, uint8_t *memory);
extern void cpu_destroy(cpu_state_t *cpu);

#define MEMORY_SIZE 1024 * 1024  // 1 MB of memory

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

    // Example: Run 100 CPU cycles
    for (int i = 0; i < 100; i++) {
        cpu_cycle(cpu, memory);
    }

    printf("CPU executed 100 cycles\n");

    cpu_destroy(cpu);
    free(memory);

    return 0;
}

