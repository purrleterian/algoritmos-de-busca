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

static void evidencia_ord(const char *filename, u32 *vetor, size_t tamanho) {
    FILE *fp = fopen(filename, "w");

    for (int i = 0; i < tamanho; i++) {
        fprintf(fp, "%d, %u\n", i, vetor[i]);
    }

    printf("Evidencia de ordenacao criada\n");
    fclose(fp);
}

static void create_csv(const char *filename, const Medida medidas[MAX_TESTS]) {
    FILE *fp = fopen(filename, "w");
    if (fp == NULL) {
        fprintf(stderr, "Error opening file: %s\n", filename);
        return;
    }

    fprintf(fp, "ID,NOME,TEMPO (SEG)\n");
    for (int i = 0; i < n_medidas; i++) {
        fprintf(fp, "%d,%s,%.10f\n", medidas[i].count, medidas[i].label,
                medidas[i].tempo);
    }

    fclose(fp);
    printf("CSV file created (%s).\n", filename);
}

static void print_resultado(BuscaResultado r) {
    bool successo = (r.pos != (u32)-1);
    printf("Resultado da busca: %s\n", successo ? "SUCESSO" : "FALHA");

    printf("\t| Alvo: [%u]\n", r.alvo);
    if (successo) {

        printf("\t| Posicao: [%u]\n", r.pos);
        printf("\t| Endereco: [%p]\n", r.ender);
    }

    printf("\t| Comparacoes: [%u]\n", r.n_comp);
    printf("\n");
}

static void exec_testes(u32 tamanho, u32 alvo_index, u16 n_testes,
                        bool alvo_ausente, bool print_v) {
    u32 *vetor;
    char tamanho_vetor_buffer[64];
    snprintf(tamanho_vetor_buffer, sizeof(tamanho_vetor_buffer),
             "Criar vetor <%u>", tamanho);

    // eu criei os Macros TEMPO_FUNC e TEMPO_REP para auxiliar no calculo de eficiencia de tempo
    TEMPO_FUNC(tamanho_vetor_buffer, vetor = criar_vetor_aleatorio(tamanho));
    printf("%s\n", tamanho_vetor_buffer);

    printf("Ordenando lista...\n");
    TEMPO_FUNC("Quick Sort", quick_sort(vetor, tamanho));
    bool resultado_ord = esta_ordenado(vetor, tamanho);
    printf("Resultado da ordenacao: %s\n", resultado_ord ? "SUCESSO" : "FALHA");
    u32 alvo = alvo_ausente ? (u32)RAND_MAX + 1 : vetor[alvo_index];

    LINE(50);
    for (int i = 0; i < n_testes; i++) {

        if (print_v)
            print_vetor(vetor, tamanho, 10);

        BuscaResultado resultado_linear;

        printf("Teste numero: (%d)\n", i + 1);
        TEMPO_REP("Busca linear",
                  resultado_linear = busca_linear(vetor, tamanho, alvo));
        print_resultado(resultado_linear);
    }

    for (int i = 0; i < n_testes; i++) {
        if (print_v)
            print_vetor(vetor, tamanho, 10);

        // busca resultado e o output das funcoes de busca para conseguir armazenar multiplas informacoes referentes a busca
        BuscaResultado resultado_binario;

        printf("Teste numero: (%d)\n", i + 1);
        TEMPO_REP("Busca Binaria",
                  resultado_binario = busca_binaria(vetor, tamanho, alvo));
        print_resultado(resultado_binario);

        LINE(50);
    }
    printf("> [%d] Testes finalizados.\n", n_testes);

    char evid_filename_buffer[64];
    snprintf(evid_filename_buffer, sizeof(evid_filename_buffer), "evidencia_ord_%u.csv",
             tamanho);


    evidencia_ord(evid_filename_buffer, vetor, tamanho);
    free(vetor);
}

static u32 get_input(char *prompt, u32 def) {
    char buffer[256];
    printf("%s", prompt);
    if (!fgets(buffer, sizeof(buffer), stdin))
        return def;

    buffer[strcspn(buffer, "\r\n")] = '\0';
    if (buffer[0] == '\0')
        return def;

    char *end;
    u64 v = strtoul(buffer, &end, 10);
    if (end == buffer)
        return def; // not a number

    return v;
}

int main(void) {
    u32 testes, alvo_index, tamanho, alvo_ausente;

    srand(time(NULL));

    tamanho = get_input("Tamanho (100000):\n>> ", 100000);
    if (tamanho == 0)
        tamanho = 100000;

    alvo_index =
        get_input("Indice do alvo apos ordenacao (rand () % tamanho):\n>> ",
                  rand() % tamanho);
    if (alvo_index >= tamanho)
        alvo_index = tamanho - 1;

    alvo_ausente =
        get_input("Buscar chave INEXISTENTE? 0 = nao, 1 = sim (0)\n>> ", 0);

    testes = get_input("Numero de testes: (4)\n>> ", 4);
    u32 max_testes = (MAX_TESTS - 1) / 2;
    if (testes > max_testes)
        testes = max_testes;

    exec_testes(tamanho, alvo_index, testes, alvo_ausente, true);

    char filename_buffer[64];
    if (alvo_ausente)
        snprintf(filename_buffer, sizeof(filename_buffer),
                 "./output/ausente-%u.csv", tamanho);
    else
        snprintf(filename_buffer, sizeof(filename_buffer), "./output/%u-%u.csv",
                 alvo_index, tamanho);

    create_csv(filename_buffer, medidas);

    return 0;
}
