#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define MAX_ITENS 10

// ===============================
//        ESTRUTURA DO ITEM
// ===============================
typedef struct {
    char nome[50];
    char tipo[30];
    int quantidade;
    int prioridade; // 1 a 5 (nível Mestre)
} Item;

// ===============================
//      ENUM PARA ORDENAÇÃO
// ===============================
typedef enum {
    ORDENAR_NOME = 1,
    ORDENAR_TIPO = 2,
    ORDENAR_PRIORIDADE = 3
} CriterioOrdenacao;

// ===============================
//      VARIÁVEIS GLOBAIS
// ===============================
Item mochila[MAX_ITENS];
int totalItens = 0;
bool estaOrdenadoPorNome = false;

// ===============================
//      FUNÇÃO AUXILIAR
// ===============================
void limparBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void adicionarItem() {
    if (totalItens >= MAX_ITENS) {
        printf("\n Mochila cheia! (Máx: 10)\n");
        return;
    }

    Item novo;
    printf("\n Novo Item:\n");
    printf("Nome: ");
    fgets(novo.nome, 50, stdin); novo.nome[strcspn(novo.nome, "\n")] = 0;

    printf("Tipo: ");
    fgets(novo.tipo, 30, stdin); novo.tipo[strcspn(novo.tipo, "\n")] = 0;

    printf("Quantidade: ");
    scanf("%d", &novo.quantidade);
    limparBuffer();

    printf("Prioridade (1 a 5): ");
    scanf("%d", &novo.prioridade);
    limparBuffer();

    mochila[totalItens++] = novo;
    estaOrdenadoPorNome = false;

    printf("\n Item adicionado!\n");
}

void removerItem() {
    if (totalItens == 0) {
        printf("\n Mochila vazia!\n");
        return;
    }

    char nome[50];
    printf("\nDigite o nome do item a remover: ");
    fgets(nome, 50, stdin); nome[strcspn(nome, "\n")] = 0;

    for (int i = 0; i < totalItens; i++) {
        if (strcmp(mochila[i].nome, nome) == 0) {
            for (int j = i; j < totalItens - 1; j++) {
                mochila[j] = mochila[j + 1];
            }
            totalItens--;
            printf("\n Item removido com sucesso!\n");
            return;
        }
    }
    printf("\n Item não encontrado!\n");
}

void listarItens() {
    if (totalItens == 0) {
        printf("\n Mochila vazia!\n");
        return;
    }

    printf("\n=====  ITENS DA MOCHILA =====\n");
    printf("%-20s %-15s %-10s %-10s\n", "Nome", "Tipo", "Qtd", "Prioridade");
    printf("---------------------------------------------------------\n");

    for (int i = 0; i < totalItens; i++) {
        printf("%-20s %-15s %-10d %-10d\n",
               mochila[i].nome,
               mochila[i].tipo,
               mochila[i].quantidade,
               mochila[i].prioridade);
    }
}

void buscarItemSequencial() {
    if (totalItens == 0) {
        printf("\n Mochila vazia!\n");
        return;
    }

    char nome[50];
    printf("\nDigite o nome do item a buscar: ");
    fgets(nome, 50, stdin); nome[strcspn(nome, "\n")] = 0;

    for (int i = 0; i < totalItens; i++) {
        if (strcmp(mochila[i].nome, nome) == 0) {
            printf("\n Item encontrado!\n");
            printf("Nome: %s\n", mochila[i].nome);
            printf("Tipo: %s\n", mochila[i].tipo);
            printf("Quantidade: %d\n", mochila[i].quantidade);
            printf("Prioridade: %d\n", mochila[i].prioridade);
            return;
        }
    }

    printf("\n Item não encontrado!\n");
}

int comparar(const Item *a, const Item *b, CriterioOrdenacao criterio) {
    switch (criterio) {
        case ORDENAR_NOME: return strcmp(a->nome, b->nome);
        case ORDENAR_TIPO: return strcmp(a->tipo, b->tipo);
        case ORDENAR_PRIORIDADE: return a->prioridade - b->prioridade;
    }
    return 0;
}

void ordenar(CriterioOrdenacao criterio) {
    int comparacoes = 0;

    for (int i = 1; i < totalItens; i++) {
        Item chave = mochila[i];
        int j = i - 1;

        while (j >= 0 && comparar(&mochila[j], &chave, criterio) > 0) {
            mochila[j + 1] = mochila[j];
            j--;
            comparacoes++;
        }

        mochila[j + 1] = chave;
    }

    printf("\n Ordenação concluída!\n");
    printf("Comparações realizadas: %d\n", comparacoes);

    estaOrdenadoPorNome = (criterio == ORDENAR_NOME);
}

void buscaBinaria() {
    if (!estaOrdenadoPorNome) {
        printf("\n A lista precisa estar ordenada por *nome* antes da busca binária!\n");
        return;
    }

    char nome[50];
    printf("\nDigite o nome do item a buscar: ");
    fgets(nome, 50, stdin); nome[strcspn(nome, "\n")] = 0;

    int inicio = 0, fim = totalItens - 1;

    while (inicio <= fim) {
        int meio = (inicio + fim) / 2;
        int cmp = strcmp(mochila[meio].nome, nome);

        if (cmp == 0) {
            printf("\n Item encontrado via busca binária!\n");
            printf("Nome: %s\n", mochila[meio].nome);
            printf("Tipo: %s\n", mochila[meio].tipo);
            printf("Quantidade: %d\n", mochila[meio].quantidade);
            printf("Prioridade: %d\n", mochila[meio].prioridade);
            return;
        }
        if (cmp < 0) inicio = meio + 1;
        else fim = meio - 1;
    }

    printf("\n Item não encontrado!\n");
}

// ===============================
//            MENU
// ===============================
void menu() {
    int opcao;

    do {
        printf("\n\n=====  DESAFIO CÓDIGO DA ILHA — FREE FIRE =====\n");
        printf("1 - Adicionar item\n");
        printf("2 - Remover item\n");
        printf("3 - Listar itens\n");
        printf("4 - Buscar (sequencial)\n");
        printf("5 - Ordenar mochila\n");
        printf("6 - Buscar binária\n");
        printf("0 - Sair\n");
        printf(" Escolha: ");
        scanf("%d", &opcao);
        limparBuffer();

        switch (opcao) {
            case 1: adicionarItem(); break;
            case 2: removerItem(); break;
            case 3: listarItens(); break;
            case 4: buscarItemSequencial(); break;
            case 5: {
                int c;
                printf("\nCritério de ordenação:\n");
                printf("1 - Nome\n2 - Tipo\n3 - Prioridade\n");
                printf(" Escolha: ");
                scanf("%d", &c);
                limparBuffer();

                if (c >= 1 && c <= 3)
                    ordenar((CriterioOrdenacao)c);
                else
                    printf("\n Critério inválido!\n");

                break;
            }
            case 6: buscaBinaria(); break;
            case 0: printf("\n Saindo...\n"); break;
            default: printf("\n Opção inválida!\n");
        }
    } while (opcao != 0);
}

// ===============================
//             MAIN
// ===============================
int main() {
    menu();
    return 0;
}
