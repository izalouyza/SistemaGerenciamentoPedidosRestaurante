#ifndef PEDIDOS_H
#define PEDIDOS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Estrutura para representar um item de pedido
typedef struct {
    int codigo_item;
    int quantidade;
    float preco_unitario;
} pedido_item;

// Estrutura para representar um pedido
typedef struct {
    int numero_pedido;
    pedido_item* itens;
    int total_itens;
    float total_pedido;
} pedido;

// Funções para gerenciar pedidos
void inicializar_pedido(pedido* p);
void adicionar_item_pedido(pedido* p, int codigo_item, int quantidade, float preco_unitario);
void remover_item_pedido(pedido* p, int codigo_item);
void exibir_pedido(const pedido* p);
void liberar_pedido(pedido* p);

#endif // PEDIDOS_H
