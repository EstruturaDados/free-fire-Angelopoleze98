#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Definicao da struct Item, que representa um item na mochila.
// Contem nome, tipo e quantidade.
typedef struct {
    char nome[30];
    char tipo[20];
    int quantidade;
} Item;

// Definicao da struct No para a lista encadeada.
// Cada no contem um Item e um ponteiro para o proximo no.
typedef struct No {
    Item dados;
    struct No* proximo;
} No;

// Definicao da mochila usando vetor (array sequencial).
// Usa um array fixo de tamanho MAX e um contador de tamanho atual.
#define MAX 100
typedef struct {
    Item itens[MAX];
    int tamanho;
} MochilaVetor;

// Definicao da mochila usando lista encadeada.
// Aponta para o inicio da lista.
typedef struct {
    No* inicio;
} MochilaLista;

// Funcoes para MochilaVetor

// Inicializa a mochila vetor, definindo tamanho como 0.
void initVetor(MochilaVetor* mv) {
    mv->tamanho = 0;
}

// Insere um novo item no final do vetor.
// Retorna 1 se sucesso, 0 se mochila cheia.
// Complexidade: O(1) - insercao constante.
int inserirItemVetor(MochilaVetor* mv, Item it) {
    if (mv->tamanho >= MAX) {
        return 0; // Mochila cheia
    }
    mv->itens[mv->tamanho++] = it;
    return 1;
}

// Remove um item pelo nome.
// Percorre o vetor sequencialmente, remove e desloca os itens subsequentes.
// Retorna 1 se removido, 0 se nao encontrado.
// Complexidade: O(n) - pior caso percorre todo o vetor e desloca.
int removerItemVetor(MochilaVetor* mv, char* nome) {
    for (int i = 0; i < mv->tamanho; i++) {
        if (strcmp(mv->itens[i].nome, nome) == 0) {
            for (int j = i; j < mv->tamanho - 1; j++) {
                mv->itens[j] = mv->itens[j + 1];
            }
            mv->tamanho--;
            return 1;
        }
    }
    return 0;
}

// Lista todos os itens no vetor.
// Percorre e imprime cada item.
// Complexidade: O(n).
void listarVetor(MochilaVetor* mv) {
    for (int i = 0; i < mv->tamanho; i++) {
        printf("Nome: %s, Tipo: %s, Quantidade: %d\n", mv->itens[i].nome, mv->itens[i].tipo, mv->itens[i].quantidade);
    }
}

// Busca sequencial por nome no vetor.
// Conta o numero de comparacoes realizadas.
// Retorna o indice se encontrado, -1 caso contrario.
// Complexidade: O(n) - percorre ate encontrar ou fim.
int buscarSequencialVetor(MochilaVetor* mv, char* nome, int* comparacoes) {
    *comparacoes = 0;
    for (int i = 0; i < mv->tamanho; i++) {
        (*comparacoes)++;
        if (strcmp(mv->itens[i].nome, nome) == 0) {
            return i;
        }
    }
    return -1;
}

// Ordena o vetor por nome usando Bubble Sort.
// Compara strings com strcmp e troca se necessario.
// Complexidade: O(n^2) - adequado para demonstracao, mas nao eficiente para grandes n.
void ordenarVetor(MochilaVetor* mv) {
    for (int i = 0; i < mv->tamanho - 1; i++) {
        for (int j = 0; j < mv->tamanho - i - 1; j++) {
            if (strcmp(mv->itens[j].nome, mv->itens[j + 1].nome) > 0) {
                Item temp = mv->itens[j];
                mv->itens[j] = mv->itens[j + 1];
                mv->itens[j + 1] = temp;
            }
        }
    }
}

// Busca binaria por nome no vetor (requer ordenacao previa).
// Conta o numero de comparacoes.
// Retorna o indice se encontrado, -1 caso contrario.
// Complexidade: O(log n) - muito mais eficiente que sequencial para vetores ordenados.
int buscarBinariaVetor(MochilaVetor* mv, char* nome, int* comparacoes) {
    *comparacoes = 0;
    int low = 0;
    int high = mv->tamanho - 1;
    while (low <= high) {
        (*comparacoes)++;
        int mid = (low + high) / 2;
        int cmp = strcmp(mv->itens[mid].nome, nome);
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

// Funcoes para MochilaLista

// Inicializa a mochila lista, definindo inicio como NULL.
void initLista(MochilaLista* ml) {
    ml->inicio = NULL;
}

// Insere um novo item no inicio da lista (para simplicidade e eficiencia).
// Aloca memoria para novo no.
// Retorna 1 se sucesso, 0 se falha na alocacao.
// Complexidade: O(1) - insercao constante, vantagem sobre vetor em casos de redimensionamento.
int inserirItemLista(MochilaLista* ml, Item it) {
    No* novo = (No*)malloc(sizeof(No));
    if (!novo) {
        return 0; // Falha na alocacao
    }
    novo->dados = it;
    novo->proximo = ml->inicio;
    ml->inicio = novo;
    return 1;
}

// Remove um item pelo nome.
// Percorre a lista, ajusta ponteiros e libera memoria.
// Retorna 1 se removido, 0 se nao encontrado.
// Complexidade: O(n) - similar ao vetor, mas sem deslocamento de elementos.
int removerItemLista(MochilaLista* ml, char* nome) {
    No* atual = ml->inicio;
    No* prev = NULL;
    while (atual) {
        if (strcmp(atual->dados.nome, nome) == 0) {
            if (prev) {
                prev->proximo = atual->proximo;
            } else {
                ml->inicio = atual->proximo;
            }
            free(atual);
            return 1;
        }
        prev = atual;
        atual = atual->proximo;
    }
    return 0;
}

// Lista todos os itens na lista.
// Percorre e imprime cada item.
// Complexidade: O(n).
void listarLista(MochilaLista* ml) {
    No* atual = ml->inicio;
    while (atual) {
        printf("Nome: %s, Tipo: %s, Quantidade: %d\n", atual->dados.nome, atual->dados.tipo, atual->dados.quantidade);
        atual = atual->proximo;
    }
}

// Busca sequencial por nome na lista.
// Conta o numero de comparacoes.
// Retorna a posicao (comecando de 0) se encontrado, -1 caso contrario.
// Complexidade: O(n) - percorre ate encontrar ou fim.
int buscarSequencialLista(MochilaLista* ml, char* nome, int* comparacoes) {
    *comparacoes = 0;
    No* atual = ml->inicio;
    int pos = 0;
    while (atual) {
        (*comparacoes)++;
        if (strcmp(atual->dados.nome, nome) == 0) {
            return pos;
        }
        pos++;
        atual = atual->proximo;
    }
    return -1;
}

// Funcao auxiliar para ler um item do usuario.
void lerItem(Item* it) {
    printf("Digite o nome do item: ");
    scanf("%s", it->nome);
    printf("Digite o tipo do item: ");
    scanf("%s", it->tipo);
    printf("Digite a quantidade: ");
    scanf("%d", &it->quantidade);
}

// Funcao auxiliar para ler um nome.
void lerNome(char* nome) {
    printf("Digite o nome do item: ");
    scanf("%s", nome);
}

// Menu principal para operacoes em uma estrutura especifica.
// Parametro isVetor: 1 para vetor, 0 para lista.
void menuOperacoes(MochilaVetor* mv, MochilaLista* ml, int isVetor) {
    int opcao;
    do {
        printf("\nMenu de Operacoes:\n");
        printf("1. Inserir item\n");
        printf("2. Remover item\n");
        printf("3. Listar itens\n");
        printf("4. Buscar sequencial\n");
        if (isVetor) {
            printf("5. Ordenar vetor\n");
            printf("6. Buscar binaria (requer ordenacao)\n");
        }
        printf("0. Voltar\n");
        printf("Escolha: ");
        scanf("%d", &opcao);

        Item it;
        char nome[30];
        int comparacoes;
        int resultado;

        switch (opcao) {
            case 1:
                lerItem(&it);
                if (isVetor) {
                    if (inserirItemVetor(mv, it)) {
                        printf("Item inserido com sucesso.\n");
                    } else {
                        printf("Mochila cheia.\n");
                    }
                } else {
                    if (inserirItemLista(ml, it)) {
                        printf("Item inserido com sucesso.\n");
                    } else {
                        printf("Falha na alocacao.\n");
                    }
                }
                break;
            case 2:
                lerNome(nome);
                if (isVetor) {
                    if (removerItemVetor(mv, nome)) {
                        printf("Item removido.\n");
                    } else {
                        printf("Item nao encontrado.\n");
                    }
                } else {
                    if (removerItemLista(ml, nome)) {
                        printf("Item removido.\n");
                    } else {
                        printf("Item nao encontrado.\n");
                    }
                }
                break;
            case 3:
                if (isVetor) {
                    listarVetor(mv);
                } else {
                    listarLista(ml);
                }
                break;
            case 4:
                lerNome(nome);
                if (isVetor) {
                    resultado = buscarSequencialVetor(mv, nome, &comparacoes);
                } else {
                    resultado = buscarSequencialLista(ml, nome, &comparacoes);
                }
                if (resultado != -1) {
                    printf("Item encontrado na posicao %d.\n", resultado);
                } else {
                    printf("Item nao encontrado.\n");
                }
                printf("Numero de comparacoes: %d\n", comparacoes);
                break;
            case 5:
                if (isVetor) {
                    ordenarVetor(mv);
                    printf("Vetor ordenado por nome.\n");
                }
                break;
            case 6:
                if (isVetor) {
                    lerNome(nome);
                    resultado = buscarBinariaVetor(mv, nome, &comparacoes);
                    if (resultado != -1) {
                        printf("Item encontrado na posicao %d.\n", resultado);
                    } else {
                        printf("Item nao encontrado.\n");
                    }
                    printf("Numero de comparacoes: %d\n", comparacoes);
                }
                break;
            case 0:
                break;
            default:
                printf("Opcao invalida.\n");
        }
    } while (opcao != 0);
}

// Funcao main: inicializa estruturas e apresenta menu principal para escolha de estrutura.
// Permite alternar entre vetor e lista.
// Comentarios destacam diferencas: vetor tem acesso rapido mas insercao/remoção custosa; lista dinamica mas acesso sequencial.
int main() {
    MochilaVetor mv;
    MochilaLista ml;
    initVetor(&mv);
    initLista(&ml);

    int escolha;
    do {
        printf("\nEscolha a estrutura:\n");
        printf("1. Mochila com Vetor\n");
        printf("2. Mochila com Lista Encadeada\n");
        printf("0. Sair\n");
        printf("Escolha: ");
        scanf("%d", &escolha);

        switch (escolha) {
            case 1:
                menuOperacoes(&mv, &ml, 1);
                break;
            case 2:
                menuOperacoes(&mv, &ml, 0);
                break;
            case 0:
                break;
            default:
                printf("Opcao invalida.\n");
        }
    } while (escolha != 0);

    // Libera memoria da lista ao final (boa pratica, embora nao obrigatorio aqui).
    No* atual = ml.inicio;
    while (atual) {
        No* temp = atual;
        atual = atual->proximo;
        free(temp);
    }

    return 0;
}