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
    bool successo = (r.pos != -1 && r.val != -1);
    printf("------------------------------\n");
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
    if (argc >= 2) {
        tamanho = atol(argv[1]);
        vetor_a = criar_vetor_aleatorio(tamanho);
       
        srand(time(NULL)); // Usando seed de tempo so pra escolher o alvo
        alvo_a = vetor_a[rand() % tamanho]; // ultimo elemento;
        if (argc >= 3) {
            alvo_a = atol(argv[2]); // ultimo elemento;

        }


    } else {
        tamanho = 100000;
        vetor_a = criar_vetor_aleatorio(tamanho);
        
        srand(time(NULL)); // Usando seed de tempo so pra escolher o alvo
        alvo_a = vetor_a[rand() % tamanho]; // ultimo elemento;
    }

    TEMPO_FUNC(insertion_sort(vetor_a, tamanho));

    print_vetor(vetor_a, tamanho, 10);

    BuscaResultado resultado_linear;
    BuscaResultado resultado_binario;

    TEMPO_FUNC(resultado_linear = busca_linear(vetor_a, tamanho, alvo_a));
    print_resultado(resultado_linear);

    TEMPO_FUNC(resultado_binario = busca_binaria(vetor_a, tamanho, alvo_a));
    print_resultado(resultado_binario);

    free(vetor_a);
    return 0;
}
