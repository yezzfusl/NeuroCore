#include "vm.h"
#include <stdlib.h>
#include <string.h>

VM* vm_create() {
    VM *vm = (VM*)malloc(sizeof(VM));
    if (!vm) return NULL;

    vm->memory = (uint8_t*)malloc(VM_MEMORY_SIZE);
    if (!vm->memory) {
        free(vm);
        return NULL;
    }

    vm_reset(vm);
    return vm;
}

void vm_destroy(VM *vm) {
    if (vm) {
        free(vm->memory);
        free(vm);
    }
}

void vm_reset(VM *vm) {
    asm_reset_memory(vm->memory, VM_MEMORY_SIZE);
    asm_init_cpu(vm->registers, &vm->program_counter, &vm->stack_pointer, &vm->base_pointer);
    vm->flags = 0;
}

int vm_execute(VM *vm) {
    // TODO: Implement instruction fetch-decode-execute cycle
    return 0;
}

