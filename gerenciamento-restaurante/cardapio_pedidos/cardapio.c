#include <stdio.h>      // Para funções de entrada e saída
#include <stdlib.h>     // Para funções de alocação de memória (malloc, realloc, free)
#include <string.h>     // Para funções de manipulação de strings (fgets, strcspn)
#include "cardapio.h"   // Para as definições de tipos e funções do cardápio

void exibir_card(item* cardapio, int codigo) {
    if(codigo > 0) {
        printf("\n================================================= Cardápio ================================================\n\n");
        printf("%-10s %-20s %-40s %-15s %-10s\n", "Código", "Nome", "Descrição", "Preço R$", "Categoria");
        printf("___________________________________________________________________________________________________________\n\n");
        for(int i = 0; i < codigo; i++) {
            printf("%-10d %-20s %-40s %-15.2f %-10s\n", i + 1, cardapio[i].nome, cardapio[i].descri, cardapio[i].preco, 
                   (cardapio[i].catego == entrada) ? "Entrada" : 
                   (cardapio[i].catego == principal) ? "Principal" : 
                   (cardapio[i].catego == sobremesa) ? "Sobremesa" : "Bebida");
        }
        printf("___________________________________________________________________________________________________________\n\n");
    } else {
        printf(">> Não há itens cadastrados.\n\n");
    }
}

void cadastro_card(item *p) {
    getchar(); // Limpar o buffer
    printf("Nome do item: "); 
    fgets(p->nome, sizeof(p->nome), stdin);
    p->nome[strcspn(p->nome, "\n")] = 0; // Remover a quebra de linha

    printf("Descrição [máx.: 100 caracteres]: ");
    fgets(p->descri, sizeof(p->descri), stdin);
    p->descri[strcspn(p->descri, "\n")] = 0; // Remover a quebra de linha

    while (1) {  // Repetição até um preço válido ser inserido
        printf("Preço em R$: ");
        // Tenta ler o preço como um float
        if (scanf("%f", &p->preco) != 1) {
            // Se a leitura falhar, limpa o buffer e solicita novamente
            printf("Valor inválido. O preço não pode incluir letras e caracteres especiais. Por favor, tente novamente.\n");
            while(getchar() != '\n');  // Limpar o buffer de entrada
        } else if (p->preco < 0) {
            printf("Valor inválido. O preço não pode ser um valor negativo. Por favor, tente novamente.\n");
        } else {
            break; // Se o valor for válido e não negativo, sai do loop
        }
    }
    int n;
    printf("\nCategoria: \n");
    while(1){
        printf("(1) Entrada\n(2) Principal\n(3) Sobremesa\n(4) Bebida\n");
        printf("Informe a opção: ");
        if(scanf("%d", &n) != 1) {
            printf("Valor inválido, por favor digite um valor válido\n");
            while(getchar() != '\n');
        } else if(n <= 0 || n > 4){
            printf("Opção inválida, por favor tente novamente.\n");
        }else {
            p->catego = (categoria)(n - 1);
            break;
        }
    }
}

void redimensionar_cardapio(item** cardapio, int* capacidade_cardapio) {
    *capacidade_cardapio *= 2; // Dobra a capacidade
    item* temp = realloc(*cardapio, *capacidade_cardapio * sizeof(item));
    if (temp == NULL) {
        printf("Erro ao redimensionar o cardápio.\n");
        exit(1); // Sair do programa em caso de erro
    }
    *cardapio = temp; // Atualiza o ponteiro do cardápio
}

void remover_card(item* cardapio, int* codigo) {
    if(*codigo > 0) {
        int num;  // Usar um inteiro simples
        printf("\n>> Preencha com as informações do item que deseja remover.\n");
        while(1) {
            printf("Código do item: ");
            if(scanf("%d", &num) != 1 || num < 1 || num > *codigo) {  // Usar &num diretamente
                printf("Código inválido. Verifique se está correto e corresponde a um item cadastrado. Por favor, tente novamente.\n");
                while(getchar() != '\n');
            } else {
                break;
            }
        }
        num--;  // Ajuste do índice
        for(int i = num; i < *codigo - 1; i++) { // Remover item
            cardapio[i] = cardapio[i + 1];
        }
        (*codigo)--; // Diminui o contador de itens
        printf(">> Item removido com sucesso.\n\n");
    } else {
        printf(">> Não há itens cadastrados.\n\n");
    }
}
