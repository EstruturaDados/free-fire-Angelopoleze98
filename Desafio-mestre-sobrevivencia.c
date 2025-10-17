#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Definicao da struct Componente, que representa um componente da torre.
// Contem nome, tipo e prioridade (1 a 10).
typedef struct {
    char nome[30];
    char tipo[20];
    int prioridade;
} Componente;

// Funcao para ler um componente do usuario.
// Usa fgets para capturar strings com seguranca, removendo newline.
void lerComponente(Componente* comp) {
    printf("Digite o nome do componente: ");
    fgets(comp->nome, 30, stdin);
    comp->nome[strcspn(comp->nome, "\n")] = 0; // Remove newline

    printf("Digite o tipo do componente: ");
    fgets(comp->tipo, 20, stdin);
    comp->tipo[strcspn(comp->tipo, "\n")] = 0; // Remove newline

    printf("Digite a prioridade (1-10): ");
    scanf("%d", &comp->prioridade);
    getchar(); // Consome newline apos scanf
}

// Funcao para mostrar todos os componentes.
// Percorre o array e imprime formatado.
// Complexidade: O(n).
void mostrarComponentes(Componente comps[], int n) {
    for (int i = 0; i < n; i++) {
        printf("Nome: %s, Tipo: %s, Prioridade: %d\n", comps[i].nome, comps[i].tipo, comps[i].prioridade);
    }
}

// Bubble Sort por nome (string).
// Ordena o array comparando strings com strcmp.
// Conta o numero de comparacoes.
// Complexidade: O(n^2) - bolhas elementos maiores para o final.
void bubbleSortNome(Componente comps[], int n, int* comparacoes) {
    *comparacoes = 0;
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            (*comparacoes)++;
            if (strcmp(comps[j].nome, comps[j + 1].nome) > 0) {
                Componente temp = comps[j];
                comps[j] = comps[j + 1];
                comps[j + 1] = temp;
            }
        }
    }
}

// Insertion Sort por tipo (string).
// Insere cada elemento na posicao correta na sublista ordenada.
// Conta o numero de comparacoes.
// Complexidade: O(n^2) - eficiente para listas quase ordenadas.
void insertionSortTipo(Componente comps[], int n, int* comparacoes) {
    *comparacoes = 0;
    for (int i = 1; i < n; i++) {
        Componente key = comps[i];
        int j = i - 1;
        while (j >= 0) {
            (*comparacoes)++;
            if (strcmp(comps[j].tipo, key.tipo) > 0) {
                comps[j + 1] = comps[j];
                j--;
            } else {
                break;
            }
        }
        comps[j + 1] = key;
    }
}

// Selection Sort por prioridade (int).
// Seleciona o menor elemento e troca com a posicao atual.
// Conta o numero de comparacoes.
// Complexidade: O(n^2) - sempre faz n^2 comparacoes.
void selectionSortPrioridade(Componente comps[], int n, int* comparacoes) {
    *comparacoes = 0;
    for (int i = 0; i < n - 1; i++) {
        int min_idx = i;
        for (int j = i + 1; j < n; j++) {
            (*comparacoes)++;
            if (comps[j].prioridade < comps[min_idx].prioridade) {
                min_idx = j;
            }
        }
        if (min_idx != i) {
            Componente temp = comps[i];
            comps[i] = comps[min_idx];
            comps[min_idx] = temp;
        }
    }
}

// Busca binaria por nome (requer array ordenado por nome).
// Conta o numero de comparacoes.
// Retorna indice se encontrado, -1 caso contrario.
// Complexidade: O(log n) - divide o espaco de busca pela metade a cada passo.
int buscaBinariaPorNome(Componente comps[], int n, char* nome, int* comparacoes) {
    *comparacoes = 0;
    int low = 0;
    int high = n - 1;
    while (low <= high) {
        (*comparacoes)++;
        int mid = (low + high) / 2;
        int cmp = strcmp(comps[mid].nome, nome);
        if (cmp == 0) {
            return mid;
        } else if (cmp < 0) {
            low = mid + 1;
        } else {
            high = mid - 1;
        }
    }
    return -1;
}

// Funcao para medir tempo e executar um algoritmo de ordenacao.
// Usa clock() para medir tempo em segundos.
// Chama a funcao de sort e imprime tempo e comparacoes.
void medirTempoOrdenacao(void (*algoritmo)(Componente[], int, int*), Componente comps[], int n, const char* nomeAlg) {
    int comparacoes;
    clock_t start = clock();
    algoritmo(comps, n, &comparacoes);
    clock_t end = clock();
    double tempo = (double)(end - start) / CLOCKS_PER_SEC;
    printf("Algoritmo %s: Tempo = %.6f s, Comparacoes = %d\n", nomeAlg, tempo, comparacoes);
}

// Funcao main: gerencia o menu e operacoes.
// Permite cadastrar componentes, escolher ordenacao, buscar e mostrar.
int main() {
    Componente componentes[20];
    int numComponentes = 0;
    int opcao;
    int ordenadoPorNome = 0; // Flag para verificar se esta ordenado por nome para busca binaria

    do {
        printf("\nMenu Principal:\n");
        printf("1. Cadastrar componente (max 20)\n");
        printf("2. Ordenar por nome (Bubble Sort)\n");
        printf("3. Ordenar por tipo (Insertion Sort)\n");
        printf("4. Ordenar por prioridade (Selection Sort)\n");
        printf("5. Buscar componente-chave por nome (Binaria - requer ordenacao por nome)\n");
        printf("6. Mostrar componentes\n");
        printf("0. Sair\n");
        printf("Escolha: ");
        scanf("%d", &opcao);
        getchar(); // Consome newline

        char nomeChave[30];
        int comparacoes;
        int resultado;

        switch (opcao) {
            case 1:
                if (numComponentes < 20) {
                    lerComponente(&componentes[numComponentes++]);
                    printf("Componente cadastrado.\n");
                    ordenadoPorNome = 0; // Reset flag apos insercao
                } else {
                    printf("Limite de componentes atingido.\n");
                }
                break;
            case 2:
                medirTempoOrdenacao(bubbleSortNome, componentes, numComponentes, "Bubble Sort Nome");
                ordenadoPorNome = 1; // Set flag
                mostrarComponentes(componentes, numComponentes);
                break;
            case 3:
                medirTempoOrdenacao(insertionSortTipo, componentes, numComponentes, "Insertion Sort Tipo");
                ordenadoPorNome = 0; // Reset flag
                mostrarComponentes(componentes, numComponentes);
                break;
            case 4:
                medirTempoOrdenacao(selectionSortPrioridade, componentes, numComponentes, "Selection Sort Prioridade");
                ordenadoPorNome = 0; // Reset flag
                mostrarComponentes(componentes, numComponentes);
                break;
            case 5:
                if (!ordenadoPorNome) {
                    printf("Ordene por nome primeiro para usar busca binaria.\n");
                    break;
                }
                printf("Digite o nome do componente-chave: ");
                fgets(nomeChave, 30, stdin);
                nomeChave[strcspn(nomeChave, "\n")] = 0;
                resultado = buscaBinariaPorNome(componentes, numComponentes, nomeChave, &comparacoes);
                if (resultado != -1) {
                    printf("Componente-chave encontrado na posicao %d.\n", resultado);
                    printf("Montagem pode prosseguir!\n");
                } else {
                    printf("Componente-chave nao encontrado. Montagem travada.\n");
                }
                printf("Comparacoes na busca: %d\n", comparacoes);
                break;
            case 6:
                mostrarComponentes(componentes, numComponentes);
                break;
            case 0:
                break;
            default:
                printf("Opcao invalida.\n");
        }
    } while (opcao != 0);

    return 0;
}