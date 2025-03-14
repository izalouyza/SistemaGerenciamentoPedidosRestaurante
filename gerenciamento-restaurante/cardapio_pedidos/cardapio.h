#ifndef CARDAPIO_H
#define CARDAPIO_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Enumeração de categorias do cardápio
typedef enum {entrada, principal, sobremesa, bebida} categoria;

// Struct para representar um item do cardápio
typedef struct {
    char nome[100];
    char descri[100];
    float preco;
    categoria catego;
} item;

// Funções do cardápio
void exibir_card(item* cardapio, int codigo);
void cadastro_card(item *p);
void redimensionar_cardapio(item** cardapio, int* capacidade_cardapio);
void remover_card(item* cardapio, int* codigo);

#endif // CARDAPIO_H
