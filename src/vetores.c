#include "vetores.h"


u32 *criar_vetor_aleatorio(u32 tamanho) {
    srand(RAND_SEED);
    u32 max = INT32_MAX;

    u32 *v = malloc(sizeof(u32) * tamanho);
    for (u32 i = 0; i < tamanho; i++) {
        v[i] = rand() % max;
    }

    return v;
}


void print_vetor(u32 *valores, u32 tamanho) {
    for (u32 i = 0; i < tamanho; i++) {
        printf("(%d) %d\n", i+1, valores[i]);
    }
    printf("\n");

}


