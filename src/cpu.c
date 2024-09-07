#include "cpu.h"
#include "instructions.h"
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
    uint32_t instr_word = cpu_fetch_instruction(cpu, memory);
    Instruction instr = {
        .opcode = (instr_word >> 24) & 0xFF,
        .operand1 = (instr_word >> 16) & 0xFF,
        .operand2 = (instr_word >> 8) & 0xFF,
        .immediate = instr_word & 0xFF
    };

    execute_instruction(cpu, memory, &instr);

    return (instr.opcode != OP_HLT);
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

uint32_t cpu_fetch_instruction(CPU *cpu, MemorySystem *memory) {
    uint32_t instruction;
    memory_read_word(memory, cpu->program_counter, &instruction);
    cpu->program_counter += 4;
    return instruction;
}

