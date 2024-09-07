#include "memory.h"
#include <stdlib.h>
#include <string.h>

#define PAGE_PRESENT 0x1
#define PAGE_WRITABLE 0x2

MemorySystem* memory_create(size_t size) {
    MemorySystem *mem = (MemorySystem*)malloc(sizeof(MemorySystem));
    if (!mem) return NULL;

    mem->total_size = size;
    size_t num_pages = (size + PAGE_SIZE - 1) / PAGE_SIZE;

    for (size_t i = 0; i < num_pages; i++) {
        mem->pages[i].data = (uint8_t*)calloc(PAGE_SIZE, 1);
        if (!mem->pages[i].data) {
            memory_destroy(mem);
            return NULL;
        }
        mem->pages[i].flags = PAGE_PRESENT | PAGE_WRITABLE;
    }

    return mem;
}

void memory_destroy(MemorySystem *mem) {
    if (!mem) return;

    for (int i = 0; i < MAX_PAGES; i++) {
        free(mem->pages[i].data);
    }
    free(mem);
}

static int check_address(MemorySystem *mem, uint32_t address, size_t size) {
    return (address + size <= mem->total_size);
}

int memory_read_byte(MemorySystem *mem, uint32_t address, uint8_t *value) {
    if (!check_address(mem, address, 1)) return 0;

    uint32_t page_num = address / PAGE_SIZE;
    uint32_t page_offset = address % PAGE_SIZE;

    if (!(mem->pages[page_num].flags & PAGE_PRESENT)) return 0;

    *value = mem->pages[page_num].data[page_offset];
    return 1;
}

int memory_write_byte(MemorySystem *mem, uint32_t address, uint8_t value) {
    if (!check_address(mem, address, 1)) return 0;

    uint32_t page_num = address / PAGE_SIZE;
    uint32_t page_offset = address % PAGE_SIZE;

    if (!(mem->pages[page_num].flags & PAGE_PRESENT) ||
        !(mem->pages[page_num].flags & PAGE_WRITABLE)) return 0;

    mem->pages[page_num].data[page_offset] = value;
    return 1;
}

int memory_read_word(MemorySystem *mem, uint32_t address, uint32_t *value) {
    if (!check_address(mem, address, 4)) return 0;

    uint8_t bytes[4];
    for (int i = 0; i < 4; i++) {
        if (!memory_read_byte(mem, address + i, &bytes[i])) return 0;
    }

    *value = (bytes[3] << 24) | (bytes[2] << 16) | (bytes[1] << 8) | bytes[0];
    return 1;
}

int memory_write_word(MemorySystem *mem, uint32_t address, uint32_t value) {
    if (!check_address(mem, address, 4)) return 0;

    for (int i = 0; i < 4; i++) {
        if (!memory_write_byte(mem, address + i, (value >> (i * 8)) & 0xFF)) return 0;
    }

    return 1;
}

