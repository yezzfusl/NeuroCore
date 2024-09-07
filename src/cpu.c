#include "cpu.h"
#include <stdlib.h>
#include <string.h>

#define FLAG_ZERO 0x01
#define FLAG_CARRY 0x02
#define FLAG_OVERFLOW 0x04
#define FLAG_NEGATIVE 0x08

CPU* cpu_create() {
    CPU *cpu = (CPU*)malloc(sizeof(CPU));
    if (cpu) {
        cpu_reset(cpu);
    }
    return cpu;
}

void cpu_destroy(CPU *cpu) {
    free(cpu);
}

void cpu_reset(CPU *cpu) {
    memset(cpu->registers, 0, sizeof(cpu->registers));
    cpu->program_counter = 0;
    cpu->stack_pointer = 0xFFFFFFFF; // Assuming 32-bit address space
    cpu->base_pointer = 0xFFFFFFFF;
    cpu->flags = 0;
}

int cpu_execute_instruction(CPU *cpu, MemorySystem *memory) {
    (void)memory; // Cast to void to explicitly ignore the parameter

    // This is a placeholder that just increments R0
    uint64_t r0_value = cpu_get_register(cpu, R0);
    cpu_set_register(cpu, R0, r0_value + 1);

    // Always return 1 to indicate successful execution
    return 1;
}

void cpu_set_flag(CPU *cpu, uint8_t flag) {
    cpu->flags |= flag;
}

void cpu_clear_flag(CPU *cpu, uint8_t flag) {
    cpu->flags &= ~flag;
}

int cpu_get_flag(CPU *cpu, uint8_t flag) {
    return (cpu->flags & flag) != 0;
}

uint64_t cpu_get_register(CPU *cpu, Register reg) {
    return cpu->registers[reg];
}

void cpu_set_register(CPU *cpu, Register reg, uint64_t value) {
    cpu->registers[reg] = value;
}

