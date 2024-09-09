#ifndef ALU_H
#define ALU_H

#include <stdint.h>
#include "cpu.h"

uint64_t alu_add(CPU *cpu, uint64_t a, uint64_t b);
uint64_t alu_sub(CPU *cpu, uint64_t a, uint64_t b);
uint64_t alu_mul(CPU *cpu, uint64_t a, uint64_t b);
uint64_t alu_div(CPU *cpu, uint64_t a, uint64_t b);
uint64_t alu_and(CPU *cpu, uint64_t a, uint64_t b);
uint64_t alu_or(CPU *cpu, uint64_t a, uint64_t b);
uint64_t alu_xor(CPU *cpu, uint64_t a, uint64_t b);
uint64_t alu_shl(CPU *cpu, uint64_t a, uint64_t b);
uint64_t alu_shr(CPU *cpu, uint64_t a, uint64_t b);

#endif // ALU_H

