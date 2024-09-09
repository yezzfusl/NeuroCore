#include "alu.h"
#include <limits.h>

uint64_t alu_add(CPU *cpu, uint64_t a, uint64_t b) {
    uint64_t result = a + b;
    
    // Set zero flag
    if (result == 0) {
        cpu_set_flag(cpu, FLAG_ZERO);
    } else {
        cpu_clear_flag(cpu, FLAG_ZERO);
    }
    
    // Set carry flag
    if (result < a) {
        cpu_set_flag(cpu, FLAG_CARRY);
    } else {
        cpu_clear_flag(cpu, FLAG_CARRY);
    }
    
    // Set overflow flag
    if ((a > 0 && b > 0 && result < 0) || (a < 0 && b < 0 && result > 0)) {
        cpu_set_flag(cpu, FLAG_OVERFLOW);
    } else {
        cpu_clear_flag(cpu, FLAG_OVERFLOW);
    }
    
    // Set negative flag
    if ((int64_t)result < 0) {
        cpu_set_flag(cpu, FLAG_NEGATIVE);
    } else {
        cpu_clear_flag(cpu, FLAG_NEGATIVE);
    }
    
    return result;
}

uint64_t alu_sub(CPU *cpu, uint64_t a, uint64_t b) {
    return alu_add(cpu, a, -b);
}

uint64_t alu_mul(CPU *cpu, uint64_t a, uint64_t b) {
    uint64_t result = a * b;
    
    // Set zero flag
    if (result == 0) {
        cpu_set_flag(cpu, FLAG_ZERO);
    } else {
        cpu_clear_flag(cpu, FLAG_ZERO);
    }
    
    // Set overflow flag
    if (a != 0 && (result / a) != b) {
        cpu_set_flag(cpu, FLAG_OVERFLOW);
    } else {
        cpu_clear_flag(cpu, FLAG_OVERFLOW);
    }
    
    // Set negative flag
    if ((int64_t)result < 0) {
        cpu_set_flag(cpu, FLAG_NEGATIVE);
    } else {
        cpu_clear_flag(cpu, FLAG_NEGATIVE);
    }
    
    return result;
}

uint64_t alu_div(CPU *cpu, uint64_t a, uint64_t b) {
    if (b == 0) {
        // Handle division by zero
        cpu_set_flag(cpu, FLAG_ZERO);
        return 0;
    }
    
    uint64_t result = a / b;
    
    // Set zero flag
    if (result == 0) {
        cpu_set_flag(cpu, FLAG_ZERO);
    } else {
        cpu_clear_flag(cpu, FLAG_ZERO);
    }
    
    // Set negative flag
    if ((int64_t)result < 0) {
        cpu_set_flag(cpu, FLAG_NEGATIVE);
    } else {
        cpu_clear_flag(cpu, FLAG_NEGATIVE);
    }
    
    return result;
}

uint64_t alu_and(CPU *cpu, uint64_t a, uint64_t b) {
    uint64_t result = a & b;
    
    // Set zero flag
    if (result == 0) {
        cpu_set_flag(cpu, FLAG_ZERO);
    } else {
        cpu_clear_flag(cpu, FLAG_ZERO);
    }
    
    // Set negative flag
    if ((int64_t)result < 0) {
        cpu_set_flag(cpu, FLAG_NEGATIVE);
    } else {
        cpu_clear_flag(cpu, FLAG_NEGATIVE);
    }
    
    return result;
}

uint64_t alu_or(CPU *cpu, uint64_t a, uint64_t b) {
    uint64_t result = a | b;
    
    // Set zero flag
    if (result == 0) {
        cpu_set_flag(cpu, FLAG_ZERO);
    } else {
        cpu_clear_flag(cpu, FLAG_ZERO);
    }
    
    // Set negative flag
    if ((int64_t)result < 0) {
        cpu_set_flag(cpu, FLAG_NEGATIVE);
    } else {
        cpu_clear_flag(cpu, FLAG_NEGATIVE);
    }
    
    return result;
}

uint64_t alu_xor(CPU *cpu, uint64_t a, uint64_t b) {
    uint64_t result = a ^ b;
    
    // Set zero flag
    if (result == 0) {
        cpu_set_flag(cpu, FLAG_ZERO);
    } else {
        cpu_clear_flag(cpu, FLAG_ZERO);
    }
    
    // Set negative flag
    if ((int64_t)result < 0) {
        cpu_set_flag(cpu, FLAG_NEGATIVE);
    } else {
        cpu_clear_flag(cpu, FLAG_NEGATIVE);
    }
    
    return result;
}

uint64_t alu_shl(CPU *cpu, uint64_t a, uint64_t b) {
    uint64_t result = a << b;
    
    // Set zero flag
    if (result == 0) {
        cpu_set_flag(cpu, FLAG_ZERO);
    } else {
        cpu_clear_flag(cpu, FLAG_ZERO);
    }
    
    // Set carry flag
    if (b > 0 && (a & (1ULL << (64 - b)))) {
        cpu_set_flag(cpu, FLAG_CARRY);
    } else {
        cpu_clear_flag(cpu, FLAG_CARRY);
    }
    
    // Set negative flag
    if ((int64_t)result < 0) {
        cpu_set_flag(cpu, FLAG_NEGATIVE);
    } else {
        cpu_clear_flag(cpu, FLAG_NEGATIVE);
    }
    
    return result;
}

uint64_t alu_shr(CPU *cpu, uint64_t a, uint64_t b) {
    uint64_t result = a >> b;
    
    // Set zero flag
    if (result == 0) {
        cpu_set_flag(cpu, FLAG_ZERO);
    } else {
        cpu_clear_flag(cpu, FLAG_ZERO);
    }
    
    // Set carry flag
    if (b > 0 && (a & (1ULL << (b - 1)))) {
        cpu_set_flag(cpu, FLAG_CARRY);
    } else {
        cpu_clear_flag(cpu, FLAG_CARRY);
    }
    
    // Set negative flag
    if ((int64_t)result < 0) {
        cpu_set_flag(cpu, FLAG_NEGATIVE);
    } else {
        cpu_clear_flag(cpu, FLAG_NEGATIVE);
    }
    
    return result;
}

