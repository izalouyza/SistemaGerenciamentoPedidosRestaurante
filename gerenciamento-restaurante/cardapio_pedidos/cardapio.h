#include "cardapio.h"

// Enumeração das strings para a interface
char* categs[] = {"Entrada", "Principal", "Sobremesa", "Bebida"};

// Função para exibir o cardápio
void exibir_card(item* cardapio, int codigo) {
    if(codigo > 0) { // Verifica se há itens para exibir
        printf("\n================================================= Cardápio ================================================\n\n");
        printf("%-10s %-20s %-40s %-15s %-10s\n", "Código", "Nome", "Descrição", "Preço R$", "Categoria");
        printf("___________________________________________________________________________________________________________\n\n");
        for(int i = 0; i < codigo; i++) {
            // Exibe cada item do cardápio formatado
            printf("%-10d %-20s %-40s %-15.2f %-10s\n", i + 1, cardapio[i].nome, cardapio[i].descri, cardapio[i].preco, categs[cardapio[i].catego]);
        }
        printf("___________________________________________________________________________________________________________\n\n");
    } else {
        printf(">> Não há itens cadastrados.\n\n"); // caso não haja itens cadastrados
    }
}

// Função para cadastrar itens no cardápio
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
            while(getchar() != '\n');  // Limpar o buffer de entrada
        } else if (p->preco < 0) {
            printf(">> Valor inválido. O preço não pode ser um valor negativo. Por favor, tente novamente.\n");
        } else { break; }
    }

    printf("\nCategoria: \n");
    while(1) {
        printf("(1) Entrada\n(2) Principal\n(3) Sobremesa\n(4) Bebida\n");
        printf("<< Informe a opção: ");
        int n;
        if(scanf("%d", &n) != 1 || n < 1 || n > 4) {
            printf(">> Opção inválida. Por favor, tente novamente.\n");
            while(getchar() != '\n');
        } else {
            p->catego = (categoria)(n - 1);
            break;
        }
    }
}

// Função para redimensionar o cardápio
void redimensionar_cardapio(item** cardapio, int* capacidade_cardapio) {
    *capacidade_cardapio *= 2;
    item* temp = realloc(*cardapio, (*capacidade_cardapio) * sizeof(item));
    if (temp == NULL) {
        printf(">> Erro ao redimensionar o cardápio.\n");
        exit(1);
    }
    *cardapio = temp;
}

// Função para remover itens do cardápio
void remover_card(item* cardapio, int* codigo) {
    if(*codigo > 0) {
        int num;
        printf("\n>> Preencha com as informações do item que deseja remover.\n");
        while(1) {
            printf("Código do item: ");
            if(scanf("%d", &num) != 1 || num < 1 || num > *codigo) {
                printf(">> Código inválido. Verifique se está correto e corresponde a um item cadastrado. Por favor, tente novamente.\n");
                while(getchar() != '\n');
            } else { break; }
        }
        num--;
        for(int i = num; i < *codigo - 1; i++) {
            cardapio[i] = cardapio[i + 1];
        }
        (*codigo)--;
        printf(">> Item removido com sucesso.\n\n");
    } else {
        printf(">> Não há itens cadastrados.\n\n");
    }
}

// Função para inicializar o cardápio
void inicializar_cardapio(item** cardapio, int* capacidade_cardapio) {
    *capacidade_cardapio = 2;
    *cardapio = malloc(*capacidade_cardapio * sizeof(item));
    if (*cardapio == NULL) {
        printf(">> Erro ao alocar memória para o cardápio.\n");
        exit(1);
    }
}
