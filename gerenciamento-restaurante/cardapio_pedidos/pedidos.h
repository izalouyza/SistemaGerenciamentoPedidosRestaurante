#ifndef PEDIDOS_H
#define PEDIDOS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Estrutura para representar um item de pedido
typedef struct {
    int codigo_item;      // Código do item
    int quantidade;       // Quantidade do item
    float preco_unitario; // Preço unitário do item
} pedido_item;

// Estrutura para representar um pedido
typedef struct {
    int numero_pedido;    // Número do pedido
    pedido_item* itens;    // Ponteiro para os itens do pedido
    int total_itens;      // Total de itens no pedido
    float total_pedido;   // Total do valor do pedido
} pedido;

// Funções para gerenciar pedidos
void inicializar_pedido(pedido* p); // Inicializa um novo pedido
void adicionar_item_pedido(pedido* p, int codigo_item, int quantidade, float preco_unitario); // Adiciona um item ao pedido
void remover_item_pedido(pedido* p, int codigo_item); // Remove um item do pedido
void exibir_pedido(const pedido* p); // Exibe os detalhes do pedido
void liberar_pedido(pedido* p); // Libera a memória alocada para os itens do pedido

#endif // PEDIDOS_H
