#include <stdio.h>
#include <inttypes.h>  // Add this include for PRIu64
#include "vm.h"
#include "cpu.h"

#define VM_MEMORY_SIZE 1048576 // 1 MB of memory

int main(void) {
    printf("Virtual Machine Initialization\n");

    VM *vm = vm_create(VM_MEMORY_SIZE);
    if (!vm) {
        fprintf(stderr, "Failed to create VM\n");
        return 1;
    }

    printf("VM created successfully\n");

    // Simple test: execute 10 instructions
    for (int i = 0; i < 10; i++) {
        if (!vm_execute(vm)) {
            fprintf(stderr, "VM execution failed\n");
            vm_destroy(vm);
            return 1;
        }
    }

    printf("VM executed 10 instructions\n");
    printf("R0 value: %" PRIu64 "\n", cpu_get_register(vm_get_cpu(vm), R0));

    vm_destroy(vm);

    return 0;
}

