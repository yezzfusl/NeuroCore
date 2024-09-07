#ifndef VM_H
#define VM_H

#include <stdint.h>

#define VM_MEMORY_SIZE 1048576 // 1 MB of memory

typedef struct {
    uint8_t *memory;
    uint64_t registers[16];
    uint64_t program_counter;
    uint64_t stack_pointer;
    uint64_t base_pointer;
    uint8_t flags;
} VM;

VM* vm_create();
void vm_destroy(VM *vm);
void vm_reset(VM *vm);
int vm_execute(VM *vm);

#endif // VM_H

