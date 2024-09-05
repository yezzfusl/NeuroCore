#include "memory_management.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

static inline uint64_t get_page_directory_index(uint64_t virtual_address) {
    return (virtual_address >> 22) & 0x3FF;
}

static inline uint64_t get_page_table_index(uint64_t virtual_address) {
    return (virtual_address >> 12) & 0x3FF;
}

static inline uint64_t get_page_offset(uint64_t virtual_address) {
    return virtual_address & 0xFFF;
}

memory_context_t* memory_init(uint64_t physical_memory_size) {
    memory_context_t *ctx = (memory_context_t*)malloc(sizeof(memory_context_t));
    if (!ctx) return NULL;

    ctx->physical_memory = (uint8_t*)malloc(physical_memory_size);
    if (!ctx->physical_memory) {
        free(ctx);
        return NULL;
    }

    ctx->physical_memory_size = physical_memory_size;
    ctx->page_directory = (page_table_t*)calloc(1, sizeof(page_table_t));
    if (!ctx->page_directory) {
        free(ctx->physical_memory);
        free(ctx);
        return NULL;
    }

    // Initialize the page directory with identity mapping
    for (uint64_t i = 0; i < PAGE_TABLE_ENTRIES; i++) {
        ctx->page_directory->entries[i] = (i << 22) | PDE_PRESENT | PDE_WRITABLE | PDE_USER;
    }

    // Initialize segments
    for (int i = 0; i < SEGMENT_COUNT; i++) {
        ctx->segments[i].base = 0;
        ctx->segments[i].limit = 0xFFFFFFFFFFFFFFFF;
        ctx->segments[i].flags = SEGMENT_PRESENT | SEGMENT_WRITABLE | SEGMENT_EXECUTABLE;
    }

    printf("Memory initialized: size=%lu bytes\n", physical_memory_size);
    return ctx;
}

void memory_destroy(memory_context_t *ctx) {
    if (ctx) {
        free(ctx->physical_memory);
        free(ctx->page_directory);
        free(ctx);
    }
}

uint64_t memory_translate(memory_context_t *ctx, uint64_t virtual_address) {
    if (!ctx || !ctx->page_directory) {
        printf("Error: Invalid memory context or page directory\n");
        return (uint64_t)-1;
    }

    uint64_t pde_index = get_page_directory_index(virtual_address);
    uint64_t pte_index = get_page_table_index(virtual_address);
    uint64_t offset = get_page_offset(virtual_address);

    uint64_t pde = ctx->page_directory->entries[pde_index];
    if (!(pde & PDE_PRESENT)) {
        printf("Page fault: page directory entry not present. Virtual address: %lx\n", virtual_address);
        return (uint64_t)-1;
    }

    page_table_t *page_table = (page_table_t*)(pde & ~0xFFF);
    if (!page_table) {
        printf("Error: NULL page table for PDE index %lu\n", pde_index);
        return (uint64_t)-1;
    }

    uint64_t pte = page_table->entries[pte_index];
    if (!(pte & PTE_PRESENT)) {
        printf("Page fault: page table entry not present. Virtual address: %lx\n", virtual_address);
        return (uint64_t)-1;
    }

    return (pte & ~0xFFF) | offset;
}

uint8_t memory_read_byte(memory_context_t *ctx, uint64_t virtual_address) {
    if (!ctx) {
        printf("Error: NULL memory context in memory_read_byte\n");
        return 0;
    }
    
    uint64_t physical_address = memory_translate(ctx, virtual_address);
    if (physical_address == (uint64_t)-1) {
        printf("Error: Invalid physical address translation for VA=%lx\n", virtual_address);
        return 0;
    }
    
    if (physical_address >= ctx->physical_memory_size) {
        printf("Error: Physical address out of bounds: PA=%lx, Size=%lu\n", physical_address, ctx->physical_memory_size);
        return 0;
    }
    
    return ctx->physical_memory[physical_address];
}

void memory_write_byte(memory_context_t *ctx, uint64_t virtual_address, uint8_t value) {
    if (!ctx) {
        printf("Error: NULL memory context in memory_write_byte\n");
        return;
    }
    
    uint64_t physical_address = memory_translate(ctx, virtual_address);
    if (physical_address == (uint64_t)-1) {
        printf("Error: Invalid physical address translation for VA=%lx\n", virtual_address);
        return;
    }
    
    if (physical_address >= ctx->physical_memory_size) {
        printf("Error: Physical address out of bounds: PA=%lx, Size=%lu\n", physical_address, ctx->physical_memory_size);
        return;
    }
    
    ctx->physical_memory[physical_address] = value;
    printf("Wrote byte %02x to PA=%lx (VA=%lx)\n", value, physical_address, virtual_address);
}


