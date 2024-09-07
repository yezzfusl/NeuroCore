#ifndef VM_H
#define VM_H

#include <stdint.h>
#include <stddef.h>

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

// Assembly function declarations
extern void asm_init_cpu(uint64_t *registers, uint64_t *pc, uint64_t *sp, uint64_t *bp);
extern void asm_reset_memory(uint8_t *memory, size_t size);

#endif // VM_H

