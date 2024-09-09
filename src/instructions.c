#include "instructions.h"
#include "alu.h"

void execute_instruction(CPU *cpu, MemorySystem *memory, Instruction *instr) {
    uint64_t op1, op2, result;

    switch (instr->opcode) {
        case OP_NOP:
            // Do nothing
            break;
        case OP_MOV:
            op1 = cpu_get_register(cpu, instr->operand1);
            cpu_set_register(cpu, instr->operand2, op1);
            break;
        case OP_ADD:
            op1 = cpu_get_register(cpu, instr->operand1);
            op2 = cpu_get_register(cpu, instr->operand2);
            result = alu_add(cpu, op1, op2);
            cpu_set_register(cpu, instr->operand1, result);
            break;
        case OP_SUB:
            op1 = cpu_get_register(cpu, instr->operand1);
            op2 = cpu_get_register(cpu, instr->operand2);
            result = alu_sub(cpu, op1, op2);
            cpu_set_register(cpu, instr->operand1, result);
            break;
        case OP_MUL:
            op1 = cpu_get_register(cpu, instr->operand1);
            op2 = cpu_get_register(cpu, instr->operand2);
            result = alu_mul(cpu, op1, op2);
            cpu_set_register(cpu, instr->operand1, result);
            break;
        case OP_DIV:
            op1 = cpu_get_register(cpu, instr->operand1);
            op2 = cpu_get_register(cpu, instr->operand2);
            result = alu_div(cpu, op1, op2);
            cpu_set_register(cpu, instr->operand1, result);
            break;
        case OP_AND:
            op1 = cpu_get_register(cpu, instr->operand1);
            op2 = cpu_get_register(cpu, instr->operand2);
            result = alu_and(cpu, op1, op2);
            cpu_set_register(cpu, instr->operand1, result);
            break;
        case OP_OR:
            op1 = cpu_get_register(cpu, instr->operand1);
            op2 = cpu_get_register(cpu, instr->operand2);
            result = alu_or(cpu, op1, op2);
            cpu_set_register(cpu, instr->operand1, result);
            break;
        case OP_XOR:
            op1 = cpu_get_register(cpu, instr->operand1);
            op2 = cpu_get_register(cpu, instr->operand2);
            result = alu_xor(cpu, op1, op2);
            cpu_set_register(cpu, instr->operand1, result);
            break;
        case OP_JMP:
            cpu->program_counter = instr->immediate;
            break;
        case OP_JZ:
            if (cpu_get_flag(cpu, FLAG_ZERO)) {
                cpu->program_counter = instr->immediate;
            }
            break;
        case OP_JNZ:
            if (!cpu_get_flag(cpu, FLAG_ZERO)) {
                cpu->program_counter = instr->immediate;
            }
            break;
        case OP_PUSH:
            op1 = cpu_get_register(cpu, instr->operand1);
            cpu->stack_pointer -= 8;
            memory_write_word(memory, cpu->stack_pointer, op1);
            break;
        case OP_POP:
            memory_read_word(memory, cpu->stack_pointer, &result);
            cpu_set_register(cpu, instr->operand1, result);
            cpu->stack_pointer += 8;
            break;
        case OP_CALL:
            cpu->stack_pointer -= 8;
            memory_write_word(memory, cpu->stack_pointer, cpu->program_counter);
            cpu->program_counter = instr->immediate;
            break;
        case OP_RET:
            memory_read_word(memory, cpu->stack_pointer, &result);
            cpu->program_counter = result;
            cpu->stack_pointer += 8;
            break;
        case OP_HLT:
            // Halt the CPU
            break;
    }
}

