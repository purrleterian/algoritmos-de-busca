#ifndef MAIN_H
#define MAIN_H

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef int8_t i8;
typedef int16_t i16;
typedef int32_t i32;
typedef int64_t i64;
typedef uint8_t u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;

typedef float f32;
typedef double f64;

#define RAND_SEED 107

#define TEMPO_FUNC(func)                                                       \
    do {                                                                       \
        clock_t inicio = clock();                                              \
        func;                                                                  \
        clock_t fim = clock();                                                 \
        double tempo = (double)(fim - inicio) / CLOCKS_PER_SEC;                \
        printf("Tempo para executar~\n[%s]:\n->%.8f (seg)\n", #func, tempo);             \
    } while (0)

#define LINE(n) for (int i = 0; i < n; i++) { printf("-"); } printf("\n")

typedef struct {
    u32 pos;
    u32 val;
    u32 *ender;
    u16 n_comp;
} BuscaResultado;

#endif
