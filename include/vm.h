#ifndef VM_H
#define VM_H

#include <stdint.h>
#include <stddef.h>
#include "memory.h"
#include "cpu.h"

typedef struct {
    MemorySystem *memory;
    CPU *cpu;
} VM;

VM* vm_create(size_t memory_size);
void vm_destroy(VM *vm);
void vm_reset(VM *vm);
int vm_execute(VM *vm);

CPU* vm_get_cpu(VM *vm);
MemorySystem* vm_get_memory(VM *vm);

#endif // VM_H

