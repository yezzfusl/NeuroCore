#ifndef MEMORY_MANAGEMENT_H
#define MEMORY_MANAGEMENT_H

#include <stdint.h>

#define PAGE_SIZE 4096
#define PAGE_TABLE_ENTRIES 1024
#define SEGMENT_COUNT 16

// Page Directory Entry flags
#define PDE_PRESENT  0x001
#define PDE_WRITABLE 0x002
#define PDE_USER     0x004

// Page Table Entry flags
#define PTE_PRESENT  0x001
#define PTE_WRITABLE 0x002
#define PTE_USER     0x004

// Segment flags
#define SEGMENT_PRESENT    0x80
#define SEGMENT_WRITABLE   0x02
#define SEGMENT_EXECUTABLE 0x08

typedef struct {
    uint64_t base;
    uint64_t limit;
    uint8_t flags;
} segment_descriptor_t;

typedef struct {
    uint64_t entries[PAGE_TABLE_ENTRIES];
} page_table_t;

typedef struct {
    page_table_t *page_directory;
    segment_descriptor_t segments[SEGMENT_COUNT];
    uint8_t *physical_memory;
    uint64_t physical_memory_size;
} memory_context_t;

memory_context_t* memory_init(uint64_t physical_memory_size);
void memory_destroy(memory_context_t *ctx);
uint64_t memory_translate(memory_context_t *ctx, uint64_t virtual_address);
uint8_t memory_read_byte(memory_context_t *ctx, uint64_t virtual_address);
void memory_write_byte(memory_context_t *ctx, uint64_t virtual_address, uint8_t value);

#endif // MEMORY_MANAGEMENT_H

