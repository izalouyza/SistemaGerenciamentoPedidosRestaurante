#ifndef CARDAPIO_H
#define CARDAPIO_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pedidos.h"

// Enumeração de categorias do cardápio
typedef enum {entrada, principal, sobremesa, bebida} categoria;

// Funções do cardápio
void exibir_card();
void cadastro_card(item *p);
void redimensionar_cardapio();
void remover_card();

extern item* cardapio; // Declaração da variável global
extern int capacidade_cardapio; // Declaração da variável global
extern int codigo; // Declaração da variável global

#endif // CARDAPIO_H
