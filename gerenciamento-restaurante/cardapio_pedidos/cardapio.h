#ifndef CARDAPIO_H
#define CARDAPIO_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h> // Incluído caso você precise de suporte a localização

typedef enum {entrada, principal, sobremesa, bebida} categoria;

// Estrutura para representar um item do cardápio
typedef struct {
    char nome[100]; // Nome do item
    char descri[100]; // Descrição do item
    float preco; // Preço do item
    categoria catego; // Categoria do item
} item;

// Função para exibir o cardápio
void exibir_card(item* cardapio, int codigo);

// Função para cadastrar um item no cardápio
void cadastro_card(item *p);

// Função para remover um item do cardápio
void remover_card(item* cardapio, int* codigo);

// Função para redimensionar o cardápio
void redimensionar_cardapio(item** cardapio, int* capacidade_cardapio);

#endif // CARDAPIO_H
