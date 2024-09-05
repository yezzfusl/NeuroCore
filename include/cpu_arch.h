#ifndef CPU_ARCH_H
#define CPU_ARCH_H

#include <stdint.h>

#define REG_COUNT 16
#define FLAG_COUNT 8

typedef uint64_t reg_t;
typedef uint8_t flag_t;

typedef struct {
    reg_t r[REG_COUNT];
    flag_t f[FLAG_COUNT];
    reg_t pc;
    reg_t sp;
} cpu_state_t;

#define REG(x) (cpu->r[(x)])
#define FLAG(x) (cpu->f[(x)])
#define PC (cpu->pc)
#define SP (cpu->sp)

#define SET_FLAG(x) (FLAG(x) = 1)
#define CLEAR_FLAG(x) (FLAG(x) = 0)
#define TEST_FLAG(x) (FLAG(x) != 0)

#define SIGN_BIT(x) ((x) >> 63)
#define EXTRACT_BITS(x, start, len) (((x) >> (start)) & ((1ULL << (len)) - 1))
#define INSERT_BITS(x, y, start, len) ((x) = ((x) & ~(((1ULL << (len)) - 1) << (start))) | (((y) & ((1ULL << (len)) - 1)) << (start)))

#define ROTATE_LEFT(x, n) (((x) << (n)) | ((x) >> (64 - (n))))
#define ROTATE_RIGHT(x, n) (((x) >> (n)) | ((x) << (64 - (n))))

#endif // CPU_ARCH_H

