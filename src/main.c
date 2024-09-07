#include <stdio.h>
#include "vm.h"

int main(void) {
    printf("Virtual Machine Initialization\n");

    VM *vm = vm_create();
    if (!vm) {
        fprintf(stderr, "Failed to create VM\n");
        return 1;
    }

    printf("VM created successfully\n");

    // TODO: Load program into VM memory

    int result = vm_execute(vm);

    printf("VM execution completed with result: %d\n", result);

    vm_destroy(vm);

    return 0;
}

