#include "vm.h"
#include <stdlib.h>
#include <string.h>

VM* vm_create(size_t memory_size) {
    VM *vm = (VM*)malloc(sizeof(VM));
    if (!vm) return NULL;

    vm->memory = memory_create(memory_size);
    if (!vm->memory) {
        free(vm);
        return NULL;
    }

    vm_reset(vm);
    return vm;
}

void vm_destroy(VM *vm) {
    if (vm) {
        memory_destroy(vm->memory);
        free(vm);
    }
}

void vm_reset(VM *vm) {
    // Reset memory (this is now handled by memory_create)
    asm_init_cpu(vm->registers, &vm->program_counter, &vm->stack_pointer, &vm->base_pointer);
    vm->flags = 0;
}

int vm_execute(VM *vm) {
    (void)vm; // Suppress unused parameter warning
    // TODO: Implement instruction fetch-decode-execute cycle
    return 0;
}

