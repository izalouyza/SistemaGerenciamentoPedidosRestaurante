#include "cardapio.h"

void exibir_card(item* cardapio, int codigo) {
    if(codigo > 0) {
        printf("\n================================================= Cardápio ================================================\n\n");
        printf("%-10s %-20s %-40s %-15s %-10s\n", "Código", "Nome", "Descrição", "Preço R$", "Categoria");
        printf("___________________________________________________________________________________________________________\n\n");
        for(int i = 0; i < codigo; i++) {
            printf("%-10d %-20s %-40s %-15.2f %-10s\n", i + 1, cardapio[i].nome, cardapio[i].descri, cardapio[i].preco, (cardapio[i].catego == entrada) ? "Entrada" : (cardapio[i].catego == principal) ? "Principal" : (cardapio[i].catego == sobremesa) ? "Sobremesa" : "Bebida");
        }
        printf("___________________________________________________________________________________________________________\n\n");
    } else {
        printf(">> Não há itens cadastrados.\n\n");
    }
}

void cadastro_card(item *p) {
    // Implementação da função de cadastro
}

void redimensionar_cardapio(item** cardapio, int* capacidade_cardapio) {
    // Implementação da função de redimensionamento
}

void remover_card(item* cardapio, int* codigo) {
    // Implementação da função de remoção
}
