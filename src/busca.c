#include "busca.h"
#include "main.h"


BuscaResultado busca_linear(u32 *vetor, size_t tamanho, u32 alvo) {
    // atribuindo valores padroes
    BuscaResultado br = {.pos = -1, .val = -1, .ender = NULL, .n_comp=0, .alvo=alvo};

    for (size_t i = 0; i < tamanho; i++) {
        // 1 comparacao = 1 uma posicao do vetor verificada
        br.n_comp++;
        if (vetor[i] == alvo) {
            br.pos = i;
            br.val = vetor[i];
            br.ender = &vetor[i];
            
            return br;
        }
    } 


    return br;
}

BuscaResultado busca_binaria(u32 *vetor, size_t tamanho, u32 alvo) {
    // obs: busca assume uma lista ordenada
    BuscaResultado br = {.pos = -1, .val = -1, .ender = NULL, .n_comp = 0, .alvo=alvo};

    i64 low = 0;
    i64 high = tamanho-1;

    while (low <= high) {
        // 1 comparacao = 1 uma posicao do vetor verificada
        int mid = low + (high - low) / 2;
       
        br.n_comp++;
        if (vetor[mid] == alvo) {
            br.pos = mid;
            br.val = vetor[mid];
            br.ender = &vetor[mid];
            
            return br;
        }

        if (vetor[mid] > alvo) {
            high = mid - 1; // subtrair 1 pra n contar o espaco atual
        } else {
            low = mid + 1;
        }
    }

    return br;
}
