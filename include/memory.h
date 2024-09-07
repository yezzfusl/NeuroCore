#ifndef MEMORY_H
#define MEMORY_H

#include <stdint.h>
#include <stddef.h>

#define PAGE_SIZE 4096
#define MAX_PAGES 256

typedef struct {
    uint8_t *data;
    uint32_t flags;
} MemoryPage;

typedef struct {
    MemoryPage pages[MAX_PAGES];
    size_t total_size;
} MemorySystem;

MemorySystem* memory_create(size_t size);
void memory_destroy(MemorySystem *mem);
int memory_read_byte(MemorySystem *mem, uint32_t address, uint8_t *value);
int memory_write_byte(MemorySystem *mem, uint32_t address, uint8_t value);
int memory_read_word(MemorySystem *mem, uint32_t address, uint32_t *value);
int memory_write_word(MemorySystem *mem, uint32_t address, uint32_t value);

#endif // MEMORY_H

