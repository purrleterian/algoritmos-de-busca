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

static Medida medidas[MAX_TESTS];
static int n_medidas = 0;

// TODO: REFACTOR structure, new file

static void create_csv(const char *filename, const Medida medidas[MAX_TESTS]) {
    FILE *fp = fopen(filename, "w");
    if (fp == NULL) {
        fprintf(stderr, "Error opening file: %s\n", filename);
        return;
    }

    fprintf(fp, "ID,NOME,TEMPO (SEG),MEDIA\n");
    for (int i = 0; i < n_medidas; i++) {
        fprintf(fp, "%d,%s,%.8f,%.8f\n", medidas[i].count, medidas[i].label,
                medidas[i].tempo, 0.0f);
    }

    fclose(fp);
    printf("CSV Created.\n");
}

static void print_resultado(BuscaResultado r) {
    bool successo = (r.pos != -1 && r.val != -1);
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

static void exec_testes(u32 tamanho, u32 alvo_index, u16 n_testes,
                        bool print_v) {
    u32 *vetor;
    vetor = criar_vetor_aleatorio(tamanho);
    u32 alvo = vetor[alvo_index];

    printf("Ordenando lista...\n");
    TEMPO_FUNC("Quick Sort", quick_sort(vetor, tamanho));
    LINE(50);
    for (int i = 0; i < n_testes; i++) {

        if (print_v)
            print_vetor(vetor, tamanho, 10);

        BuscaResultado resultado_linear;

        printf("Teste numero: (%d)\n", i + 1);
        TEMPO_FUNC("Busca linear",
                   resultado_linear = busca_linear(vetor, tamanho, alvo));
        print_resultado(resultado_linear);
    }

    for (int i = 0; i < n_testes; i++) {
        if (print_v)
            print_vetor(vetor, tamanho, 10);

        BuscaResultado resultado_binario;
        TEMPO_FUNC("Busca Binaria",
                   resultado_binario = busca_binaria(vetor, tamanho, alvo));
        print_resultado(resultado_binario);

        LINE(50);
    }
    printf(">[%d] Testes finalizados.\n", n_testes);

    free(vetor);
}

int main(int argc, char **argv) {

    const u32 testes = 5;
    u32 tamanho, alvo_index;
    if (argc >= 2) {
        tamanho = atol(argv[1]);

        srand(time(NULL)); // Usando seed de tempo so pra escolher o alvo
        alvo_index = rand() % tamanho; // ultimo elemento;
        if (argc >= 3) {
            alvo_index = atol(argv[2]); // ultimo elemento;
        }

        exec_testes(tamanho, alvo_index, testes, true);

    } else {
        tamanho = 1000;

        srand(time(NULL)); // Usando seed de tempo so pra escolher o alvo
        exec_testes(tamanho, (rand() % tamanho), testes, true);
    }

    create_csv("medidas_alg.csv", medidas);

    return 0;
}
