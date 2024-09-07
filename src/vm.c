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
    memset(vm->memory, 0, VM_MEMORY_SIZE);
    memset(vm->registers, 0, sizeof(vm->registers));
    vm->program_counter = 0;
    vm->stack_pointer = VM_MEMORY_SIZE - 1;
    vm->base_pointer = VM_MEMORY_SIZE - 1;
    vm->flags = 0;
}

int vm_execute(VM *vm) {
    // TODO: Implement instruction fetch-decode-execute cycle
    return 0;
}

