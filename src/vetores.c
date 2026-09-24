#include "vetores.h"

u32 *criar_vetor_aleatorio(u32 tamanho) {
    srand(RAND_SEED);

    u32 *v = malloc(sizeof(u32) * tamanho);
    // verificacao de erro
    if (v == NULL) {
        fprintf(stderr, "Erro criando vetor\n");
        exit(1);
    }
    for (u32 i = 0; i < tamanho; i++) {
        v[i] = rand();
    }

    return v;
}

void print_vetor(u32 *valores, u32 tamanho, u32 display_t) {
    for (u32 i = 0; i < tamanho; i++) {
        printf("(%d) %d\n", i, valores[i]);
        if (i == display_t) {
            printf("[... %u]\n", tamanho);
            break;
        }
    }
    printf("\n");
}
