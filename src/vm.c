#include "vm.h"
#include <stdlib.h>

VM* vm_create(size_t memory_size) {
    VM *vm = (VM*)malloc(sizeof(VM));
    if (!vm) return NULL;

    vm->memory = memory_create(memory_size);
    if (!vm->memory) {
        free(vm);
        return NULL;
    }

    vm->cpu = cpu_create();
    if (!vm->cpu) {
        memory_destroy(vm->memory);
        free(vm);
        return NULL;
    }

    vm_reset(vm);
    return vm;
}

void vm_destroy(VM *vm) {
    if (vm) {
        memory_destroy(vm->memory);
        cpu_destroy(vm->cpu);
        free(vm);
    }
}

void vm_reset(VM *vm) {
    cpu_reset(vm->cpu);
    // Memory reset is handled by memory_create
}

int vm_execute(VM *vm) {
    int result = 1;
    while (result) {
        result = cpu_execute_instruction(vm->cpu, vm->memory);
    }
    return result;
}

CPU* vm_get_cpu(VM *vm) {
    return vm->cpu;
}

MemorySystem* vm_get_memory(VM *vm) {
    return vm->memory;
}

