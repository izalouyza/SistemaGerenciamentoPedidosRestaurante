#ifndef PEDIDOS_H
#define PEDIDOS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cardapio.h" // Certifique-se de que este cabeçalho está correto

// Enumeração para o status dos pedidos
typedef enum {PENDENTE, EM_PREPARO, PRONTO, ENTREGUE} StatusPedido;

// Estrutura para representar um pedido
typedef struct {
    int cod_pedido; // Código do pedido
    char nome_cliente[100]; // Nome do cliente
    item* itens; // Ponteiro para os itens do pedido
    int num_itens; // Número de itens no pedido
    StatusPedido status; // Status do pedido
} Pedido;

// Funções para gerenciar pedidos
void criar_pedido_menu(Pedido* pedidos, int* num_pedidos, item* cardapio, int codigo);
void gerenciar_pedidos(Pedido* pedidos, int num_pedidos);
void alterar_status(Pedido* pedidos, int num_pedidos);
void alterar_pedido(Pedido* pedidos, int num_pedidos, item* cardapio, int codigo);
void remover_pedido(Pedido* pedidos, int* num_pedidos);

#endif // PEDIDOS_H
