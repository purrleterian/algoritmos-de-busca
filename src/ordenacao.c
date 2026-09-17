#include "ordenacao.h"


void selection_sort(u32 *vetor, size_t tamanho) {
    for (u32 i = 0; i < tamanho - 1; i++) {
        u32 min_i = i;

        for (u32 j = i + 1; j < tamanho; j++) {
            if (vetor[j] < vetor[min_i]) {
                min_i = j;
            }
        }

        int temp = vetor[i];
        vetor[i] = vetor[min_i];
        vetor[min_i] = temp;
    }
}

void insertion_sort(u32 *vetor, size_t tamanho) {
    for (u32 i = 0; i < tamanho; i++) {
        int key = vetor[i]; // numero sendo comparado 

        int j = i - 1;
        while (j >= 0 && vetor[j] > key) {
            vetor[j + 1] = vetor[j];
            j--;

        }

        vetor[j + 1] = key;
    }
}
