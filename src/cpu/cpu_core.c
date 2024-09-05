#include "cpu_arch.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

static inline uint64_t decode_instruction(uint64_t raw_instr) {
    return ROTATE_LEFT(raw_instr ^ 0xDEADBEEFCAFEBABE, 17);
}

static uint64_t fetch_instruction(cpu_state_t *cpu) {
    uint64_t addr = cpu->pc;
    uint64_t index = CACHE_INDEX(addr);
    uint64_t tag = CACHE_TAG(addr);

    if (cpu->cache_tag[index] == tag) {
        return cpu->instr_cache[index];
    }

    uint64_t raw_instr = 0;
    for (int i = 0; i < 8; i++) {
        raw_instr |= (uint64_t)memory_read_byte(cpu->memory_ctx, addr + i) << (i * 8);
    }
    cpu->instr_cache[index] = raw_instr;
    cpu->cache_tag[index] = tag;

    return raw_instr;
}

static void execute_instruction(cpu_state_t *cpu, uint64_t instr) {
    uint8_t opcode = EXTRACT_BITS(instr, 56, 8);
    uint8_t dest = EXTRACT_BITS(instr, 52, 4);
    uint8_t src1 = EXTRACT_BITS(instr, 48, 4);
    uint8_t src2 = EXTRACT_BITS(instr, 44, 4);
    uint64_t imm = EXTRACT_BITS(instr, 0, 44);

    printf("Executing instruction: opcode=%02x, dest=%d, src1=%d, src2=%d, imm=%lx\n", 
           opcode, dest, src1, src2, imm);

    switch (opcode) {
        case 0x01: // ADD
            cpu->r[dest] = cpu->r[src1] + cpu->r[src2];
            SET_FLAG(0);
            break;
        case 0x02: // SUB
            cpu->r[dest] = cpu->r[src1] - cpu->r[src2];
            SET_FLAG(1);
            break;
        case 0x03: // MUL
            cpu->r[dest] = cpu->r[src1] * cpu->r[src2];
            SET_FLAG(2);
            break;
        case 0x04: // DIV
            if (cpu->r[src2] != 0) {
                cpu->r[dest] = cpu->r[src1] / cpu->r[src2];
                SET_FLAG(3);
            } else {
                SET_FLAG(7); // Division by zero flag
            }
            break;
        case 0x05: // AND
            cpu->r[dest] = cpu->r[src1] & cpu->r[src2];
            SET_FLAG(4);
            break;
        case 0x06: // OR
            cpu->r[dest] = cpu->r[src1] | cpu->r[src2];
            SET_FLAG(5);
            break;
        case 0x07: // XOR
            cpu->r[dest] = cpu->r[src1] ^ cpu->r[src2];
            SET_FLAG(6);
            break;
        case 0x08: // LOAD
            cpu->r[dest] = imm;
            break;
        default:
            printf("Unknown opcode: %02x\n", opcode);
            break;
    }
}

void cpu_cycle(cpu_state_t *cpu) {
    printf("CPU Cycle: PC = %lx\n", cpu->pc);
    uint64_t raw_instr = fetch_instruction(cpu);
    uint64_t instr = decode_instruction(raw_instr);
    execute_instruction(cpu, instr);
    cpu->pc += 8;
}

cpu_state_t *cpu_init(uint64_t memory_size) {
    cpu_state_t *cpu = (cpu_state_t*)malloc(sizeof(cpu_state_t));
    if (!cpu) {
        printf("Failed to allocate CPU state\n");
        return NULL;
    }

    memset(cpu, 0, sizeof(cpu_state_t));
    cpu->sp = 0xFFFFFFFFFFFFFFFF;
    cpu->pc = 0;  // Initialize PC to 0

    // Initialize registers with some values
    for (int i = 0; i < REG_COUNT; i++) {
        cpu->r[i] = i * 100;
    }

    cpu->memory_ctx = memory_init(memory_size);
    if (!cpu->memory_ctx) {
        printf("Failed to initialize memory context\n");
        free(cpu);
        return NULL;
    }

    printf("CPU state initialized: PC=%lx, SP=%lx\n", cpu->pc, cpu->sp);
    return cpu;
}

void cpu_destroy(cpu_state_t *cpu) {
    if (cpu) {
        memory_destroy(cpu->memory_ctx);
        free(cpu);
    }
}

