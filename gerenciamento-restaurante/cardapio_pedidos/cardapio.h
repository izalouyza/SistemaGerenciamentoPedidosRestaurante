#ifndef CARDAPIO_H
#define CARDAPIO_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

// Enumeração de categorias do cardápio
typedef enum {entrada, principal, sobremesa, bebida} categoria;
extern char* categs[];

// Struct para representar um item do cardápio
typedef struct {
    char nome[100]; // nome do item
    char descri[100]; // descrição do item
    float preco; // preço em R$ do item
    categoria catego; // Categoria do item
} item;

// Funções do cardápio
void exibir_card(item* cardapio, int codigo);
void cadastro_card(item *p);
void redimensionar_cardapio(item** cardapio, int* capacidade_cardapio);
void remover_card(item* cardapio, int* codigo);
void atualizar_cardapio(item* cardapio, int codigo);
void inicializar_cardapio(item** cardapio, int* capacidade_cardapio);

#endif // CARDAPIO_H
