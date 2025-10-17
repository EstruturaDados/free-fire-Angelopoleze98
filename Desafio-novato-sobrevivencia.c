#include <stdio.h>    // Biblioteca para entrada e saída padrão
#include <stdlib.h>   // Biblioteca para funções utilitárias (ex: system)
#include <string.h>   // Biblioteca para manipulação de strings

// Definição da struct que representa um item da mochila
typedef struct {
    char nome[30];     // Nome do item
    char tipo[20];     // Tipo do item (ex: arma, munição, cura)
    int quantidade;    // Quantidade do item
} Item;

// Definindo o vetor de itens e um contador para controlar a quantidade atual
#define MAX_ITENS 10
Item mochila[MAX_ITENS];
int totalItens = 0;

// Função para limpar o buffer do teclado (evita problemas com fgets)
void limparBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {}
}

// Função para cadastrar um novo item na mochila
void inserirItem() {
    if (totalItens >= MAX_ITENS) {
        printf("Mochila cheia! Não é possível adicionar mais itens.\n");
        return;
    }

    Item novo;

    printf("Digite o nome do item: ");
    limparBuffer(); // limpa o buffer antes de fgets
    fgets(novo.nome, sizeof(novo.nome), stdin);
    novo.nome[strcspn(novo.nome, "\n")] = '\0'; // remove o '\n'

    printf("Digite o tipo do item (arma, municao, cura, etc.): ");
    fgets(novo.tipo, sizeof(novo.tipo), stdin);
    novo.tipo[strcspn(novo.tipo, "\n")] = '\0';

    printf("Digite a quantidade: ");
    scanf("%d", &novo.quantidade);

    mochila[totalItens] = novo;  // adiciona ao vetor
    totalItens++;

    printf("Item adicionado com sucesso!\n");
}

// Função para remover um item da mochila pelo nome
void removerItem() {
    if (totalItens == 0) {
        printf("A mochila está vazia.\n");
        return;
    }

    char nome[30];
    printf("Digite o nome do item a ser removido: ");
    limparBuffer();
    fgets(nome, sizeof(nome), stdin);
    nome[strcspn(nome, "\n")] = '\0';

    // Busca pelo item no vetor
    int encontrado = 0;
    for (int i = 0; i < totalItens; i++) {
        if (strcmp(mochila[i].nome, nome) == 0) {
            encontrado = 1;
            // Sobrescreve o item com o último da lista
            mochila[i] = mochila[totalItens - 1];
            totalItens--;
            printf("Item '%s' removido com sucesso.\n", nome);
            break;
        }
    }

    if (!encontrado) {
        printf("Item não encontrado.\n");
    }
}

// Função para listar todos os itens da mochila
void listarItens() {
    if (totalItens == 0) {
        printf("A mochila está vazia.\n");
        return;
    }

    printf("\n--- Itens na mochila ---\n");
    for (int i = 0; i < totalItens; i++) {
        printf("Item %d:\n", i + 1);
        printf("  Nome: %s\n", mochila[i].nome);
        printf("  Tipo: %s\n", mochila[i].tipo);
        printf("  Quantidade: %d\n", mochila[i].quantidade);
    }
    printf("------------------------\n");
}

// Função de busca sequencial por nome do item
void buscarItem() {
    if (totalItens == 0) {
        printf("A mochila está vazia.\n");
        return;
    }

    char nome[30];
    printf("Digite o nome do item a ser buscado: ");
    limparBuffer();
    fgets(nome, sizeof(nome), stdin);
    nome[strcspn(nome, "\n")] = '\0';

    int encontrado = 0;
    for (int i = 0; i < totalItens; i++) {
        if (strcmp(mochila[i].nome, nome) == 0) {
            printf("Item encontrado:\n");
            printf("  Nome: %s\n", mochila[i].nome);
            printf("  Tipo: %s\n", mochila[i].tipo);
            printf("  Quantidade: %d\n", mochila[i].quantidade);
            encontrado = 1;
            break;
        }
    }

    if (!encontrado) {
        printf("Item não encontrado.\n");
    }
}

// Função principal que exibe o menu e interage com o usuário
int main() {
    int opcao;

    do {
        printf("\n===== SISTEMA DE INVENTÁRIO =====\n");
        printf("1. Adicionar item\n");
        printf("2. Remover item\n");
        printf("3. Listar itens\n");
        printf("4. Buscar item\n");
        printf("0. Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                inserirItem();
                break;
            case 2:
                removerItem();
                break;
            case 3:
                listarItens();
                break;
            case 4:
                buscarItem();
                break;
            case 0:
                printf("Saindo do sistema...\n");
                break;
            default:
                printf("Opcao invalida. Tente novamente.\n");
        }

    } while (opcao != 0);

    return 0;
}
