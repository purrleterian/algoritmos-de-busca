#include "ordenacao.h"

bool esta_ordenado(u32 *vetor, size_t tamanho) {
    for (size_t i = 1; i < tamanho; i++) {
        if (vetor[i] < vetor[i-1]) return false;
    }

    return true;
}

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

static void swap(u32 *x, u32 *y) {
    u32 temp = *x;
    *x = *y;
    *y = temp;
}

static u32 partition(u32 *vetor, i32 low, i32 high) {
    u32 pivo_value = vetor[high]; 
    u32 i = low;
    for (u32 j = low; j < high; j++) {
        if (vetor[j] <= pivo_value) {
            swap(&vetor[i], &vetor[j]);
            i++;
        }
    }
    
    swap(&vetor[i], &vetor[high]);
    return i;
}


static void quick_sort_recurs(u32 *vetor, i32 low, i32 high) {
    if (low < high) {
        u32 pivo_index = partition(vetor, low, high);
        quick_sort_recurs(vetor, low, pivo_index - 1);
        quick_sort_recurs(vetor, pivo_index + 1, high);
    }
}

// quick sort
void quick_sort(u32 *vetor, size_t tamanho) {
    quick_sort_recurs(vetor, 0, tamanho - 1);
}
