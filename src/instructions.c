#include "instructions.h"

void execute_instruction(CPU *cpu, MemorySystem *memory, Instruction *instr) {
    switch (instr->opcode) {
        case OP_NOP:
            // Do nothing
            break;
        case OP_MOV:
            // TODO: Implement MOV instruction
            break;
        case OP_ADD:
            // TODO: Implement ADD instruction
            break;
        case OP_SUB:
            // TODO: Implement SUB instruction
            break;
        case OP_MUL:
            // TODO: Implement MUL instruction
            break;
        case OP_DIV:
            // TODO: Implement DIV instruction
            break;
        case OP_AND:
            // TODO: Implement AND instruction
            break;
        case OP_OR:
            // TODO: Implement OR instruction
            break;
        case OP_XOR:
            // TODO: Implement XOR instruction
            break;
        case OP_JMP:
            // TODO: Implement JMP instruction
            break;
        case OP_JZ:
            // TODO: Implement JZ instruction
            break;
        case OP_JNZ:
            // TODO: Implement JNZ instruction
            break;
        case OP_PUSH:
            // TODO: Implement PUSH instruction
            break;
        case OP_POP:
            // TODO: Implement POP instruction
            break;
        case OP_CALL:
            // TODO: Implement CALL instruction
            break;
        case OP_RET:
            // TODO: Implement RET instruction
            break;
        case OP_HLT:
            // TODO: Implement HLT instruction
            break;
    }
}

