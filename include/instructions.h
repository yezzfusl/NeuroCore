#ifndef INSTRUCTIONS_H
#define INSTRUCTIONS_H

#include <stdint.h>
#include "cpu.h"
#include "memory.h"

typedef enum {
    OP_NOP,
    OP_MOV,
    OP_ADD,
    OP_SUB,
    OP_MUL,
    OP_DIV,
    OP_AND,
    OP_OR,
    OP_XOR,
    OP_JMP,
    OP_JZ,
    OP_JNZ,
    OP_PUSH,
    OP_POP,
    OP_CALL,
    OP_RET,
    OP_HLT
} Opcode;

typedef struct {
    Opcode opcode;
    uint8_t operand1;
    uint8_t operand2;
    uint32_t immediate;
} Instruction;

void execute_instruction(CPU *cpu, MemorySystem *memory, Instruction *instr);

#endif // INSTRUCTIONS_H

