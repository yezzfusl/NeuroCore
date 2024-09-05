#include "cpu_arch.h"
#include <stdlib.h>

#define FETCH_BYTE(addr) (*(uint8_t*)(addr))
#define FETCH_WORD(addr) (*(uint16_t*)(addr))
#define FETCH_DWORD(addr) (*(uint32_t*)(addr))
#define FETCH_QWORD(addr) (*(uint64_t*)(addr))

static inline uint64_t decode_instruction(uint64_t raw_instr) {
    return ROTATE_LEFT(raw_instr ^ 0xDEADBEEFCAFEBABE, 17);
}

static void execute_instruction(cpu_state_t *cpu, uint64_t instr) {
    uint8_t opcode = EXTRACT_BITS(instr, 56, 8);
    uint8_t dest = EXTRACT_BITS(instr, 52, 4);
    uint8_t src1 = EXTRACT_BITS(instr, 48, 4);
    uint8_t src2 = EXTRACT_BITS(instr, 44, 4);
    // uint64_t imm = EXTRACT_BITS(instr, 0, 44);  // Comment out this line for now

    switch (opcode) {
        case 0x01: // ADD
            REG(dest) = REG(src1) + REG(src2);
            SET_FLAG(0);
            break;
        case 0x02: // SUB
            REG(dest) = REG(src1) - REG(src2);
            SET_FLAG(1);
            break;
        // ... more instructions ...
        default:
            // Handle unknown instruction
            break;
    }
}


void cpu_cycle(cpu_state_t *cpu, uint8_t *memory) {
    uint64_t raw_instr = FETCH_QWORD(&memory[PC]);
    uint64_t instr = decode_instruction(raw_instr);
    execute_instruction(cpu, instr);
    PC += 8;
}

cpu_state_t *cpu_init() {
    cpu_state_t *cpu = (cpu_state_t*)malloc(sizeof(cpu_state_t));
    if (!cpu) return NULL;

    for (int i = 0; i < REG_COUNT; i++) {
        REG(i) = 0;
    }
    for (int i = 0; i < FLAG_COUNT; i++) {
        FLAG(i) = 0;
    }
    PC = 0;
    SP = 0xFFFFFFFFFFFFFFFF;

    return cpu;
}

void cpu_destroy(cpu_state_t *cpu) {
    free(cpu);
}

