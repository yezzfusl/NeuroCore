#ifndef VM_H
#define VM_H

#include <stdint.h>
#include <stddef.h>
#include "memory.h"

typedef struct {
    MemorySystem *memory;
    uint64_t registers[16];
    uint64_t program_counter;
    uint64_t stack_pointer;
    uint64_t base_pointer;
    uint8_t flags;
} VM;

VM* vm_create(size_t memory_size);
void vm_destroy(VM *vm);
void vm_reset(VM *vm);
int vm_execute(VM *vm);

// Assembly function declarations
extern void asm_init_cpu(uint64_t *registers, uint64_t *pc, uint64_t *sp, uint64_t *bp);

#endif // VM_H

