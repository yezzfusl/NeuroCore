#include <stdio.h>
#include <inttypes.h>
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

    // Execute 10 instructions
    for (int i = 0; i < 10; i++) {
        if (!vm_execute(vm)) {
            fprintf(stderr, "VM execution failed at instruction %d\n", i);
            vm_destroy(vm);
            return 1;
        }
    }

    printf("VM executed 10 instructions\n");
    printf("R0 value: %" PRIu64 "\n", cpu_get_register(vm_get_cpu(vm), R0));

    vm_destroy(vm);

    return 0;
}

