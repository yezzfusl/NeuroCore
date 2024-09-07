#ifndef CPU_H
#define CPU_H

#include <stdint.h>
#include "memory.h"

#define NUM_REGISTERS 16

typedef enum {
    R0, R1, R2, R3, R4, R5, R6, R7,
    R8, R9, R10, R11, R12, R13, R14, R15
} Register;

typedef struct {
    uint64_t registers[NUM_REGISTERS];
    uint64_t program_counter;
    uint64_t stack_pointer;
    uint64_t base_pointer;
    uint8_t flags;
} CPU;

CPU* cpu_create();
void cpu_destroy(CPU *cpu);
void cpu_reset(CPU *cpu);
int cpu_execute_instruction(CPU *cpu, MemorySystem *memory);

// Flag operations
void cpu_set_flag(CPU *cpu, uint8_t flag);
void cpu_clear_flag(CPU *cpu, uint8_t flag);
int cpu_get_flag(CPU *cpu, uint8_t flag);

// Register operations
uint64_t cpu_get_register(CPU *cpu, Register reg);
void cpu_set_register(CPU *cpu, Register reg, uint64_t value);

#endif // CPU_H

