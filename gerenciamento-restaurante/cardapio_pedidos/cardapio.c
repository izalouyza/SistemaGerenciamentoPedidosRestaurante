#include "cardapio.h"
#include "pedidos.h"

// Definição das categorias e strings
char* categs[] = {"Entrada", "Principal", "Sobremesa", "Bebida"};
char* strings[] = {"Código", "Nome", "Descrição", "Preço R$", "Categoria"};

// Função para exibir o cardápio
void exibir_card() {
    if (codigo > 0) {
        printf("\n================================================= Cardápio ================================================\n\n");
        printf("%-10s %-20s %-40s %-15s %-10s\n", strings[0], strings[1], strings[2], strings[3], strings[4]);
        printf("___________________________________________________________________________________________________________\n\n");
        for (int i = 0; i < codigo; i++) {
            printf("%-10d %-20s %-40s %-15.2f %-10s\n", i + 1, cardapio[i].nome, cardapio[i].descri, cardapio[i].preco, categs[cardapio[i].catego]);
        }
        printf("___________________________________________________________________________________________________________\n\n");
    } else {
        printf(">> Não há itens cadastrados.\n\n");
    }
}

// Função para cadastrar um item no cardápio
void cadastro_card(item *p) {
    getchar(); // Limpar o buffer
    printf("Nome do item: ");
    fgets(p->nome, sizeof(p->nome), stdin);
    p->nome[strcspn(p->nome, "\n")] = 0; // Remover a quebra de linha

    printf("Descrição [máx.: 100 caracteres]: ");
    fgets(p->descri, sizeof(p->descri), stdin);
    p->descri[strcspn(p->descri, "\n")] = 0; // Remover a quebra de linha

    while (1) {
        printf("Preço em R$: ");
        if (scanf("%f", &p->preco) != 1) {
            printf(">> Valor inválido. O preço não pode incluir letras e caracteres especiais. Por favor, tente novamente.\n");
            while(getchar() != '\n'); // Limpar o buffer de entrada
        } else if (p->preco < 0) {
            printf(">> Valor inválido. O preço não pode ser um valor negativo. Por favor, tente novamente.\n");
        } else {
            break; // Se o valor for válido e não negativo, sai do loop
        }
    }

    printf("\nCategoria: \n");
    while(1) {
        printf("(1) Entrada\n(2) Principal\n(3) Sobremesa\n(4) Bebida\n");
        printf("<< Informe a opção: ");
        int n;
        if(scanf("%d", &n) != 1 || n < 1 || n > 4) {
            printf(">> Opção inválida. Por favor, tente novamente.\n");
            while(getchar() != '\n'); // Limpar o buffer de entrada
        } else {
            p->catego = (categoria)(n - 1); // Converte o int para categoria
            break; // Se o valor for válido, sai do loop
        }
    }
}

// Função para redimensionar o cardápio
void redimensionar_cardapio() {
    capacidade_cardapio *= 2; // Dobra a capacidade do cardápio
    item* temp = realloc(cardapio, capacidade_cardapio * sizeof(item)); // Tenta realocar a memória
    if (temp == NULL) {
        printf(">> Erro ao redimensionar a memória para o cardápio.\n");
        exit(1); // Sair do programa em caso de erro
    }
    cardapio = temp; // Atualiza o ponteiro do cardápio
}

// Função para remover um item do cardápio
void remover_card() {
    if (codigo > 0) {
        int cod_item;
        printf("Informe o código do item a ser removido: ");
        if (scanf("%d", &cod_item) != 1 || cod_item <= 0 || cod_item > codigo) {
            printf(">> Código inválido. Operação cancelada.\n");
            while (getchar() != '\n'); // Limpar o buffer de entrada
            return;
        }
        cod_item--; // Ajuste do índice
        for (int i = cod_item; i < codigo - 1; i++) {
            cardapio[i] = cardapio[i + 1]; // Move os itens para preencher o espaço do item removido
        }
        codigo--; // Diminui o contador de itens
        printf(">> Item removido com sucesso.\n");
    } else {
        printf(">> Não há itens cadastrados no cardápio.\n");
    }
}