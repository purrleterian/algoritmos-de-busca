/*

Comparacao de algoritmos de busca (Linear X Binaria)

1. Funcionalidade de geracao de vetor de numeros aleatorios
2. Determinar tempo de exec com clock()
3. Realizar 4 execucoes dos algoritmos com vetores de 100.000, 200.000 e 300.000
elementos
4. No final, estimar qual seria o tempo de execucao para um vetor contendo
500.000 elementos
5. Realizar a ordenacao dos vetores (necessario pra busca binaria) e medir o
tempo de execucao. Apresentar evidencia de ordenacao (print vetor)


*/
#include "main.h"
#include "busca.h"
#include "ordenacao.h"
#include "vetores.h"

static void print_resultado(BuscaResultado r) {
    bool successo = (r.pos > 0);
    printf("----------------------\n");
    printf("Resultado da busca: %s\n", successo ? "SUCESSO" : "FALHA");
    if (!successo) {
        return;
    } else {
        printf("\t| Alvo: [%d]\n", r.val);
        printf("\t| Posicao: [%d]\n", r.pos);
        printf("\t| Endereco: [%p]\n", r.ender);
        printf("\t| Comparacoes: [%d]\n", r.n_comp);
    }
    printf("\n");
}

int main(int argc, char **argv) {

    u32 tamanho, alvo_a;
    u32 *vetor_a;
    if (argc != 3) {

        tamanho = 100000;
        vetor_a = criar_vetor_aleatorio(tamanho);
        alvo_a = vetor_a[rand() % tamanho]; // ultimo elemento;

    } else {
        tamanho = atol(argv[1]);
        vetor_a = criar_vetor_aleatorio(tamanho);
        alvo_a = atol(argv[2]);// ultimo elemento;
    }

    TEMPO_FUNC(insertion_sort(vetor_a, tamanho));

    // print_vetor(vetor_a, tamanho_a);

    BuscaResultado resultado;

    TEMPO_FUNC(resultado = busca_linear(vetor_a, tamanho, alvo_a));
    print_resultado(resultado);

    TEMPO_FUNC(resultado = busca_binaria(vetor_a, tamanho, alvo_a));
    print_resultado(resultado);

    free(vetor_a);
    return 0;
}
