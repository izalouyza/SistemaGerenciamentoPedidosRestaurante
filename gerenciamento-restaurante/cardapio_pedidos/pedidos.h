#ifndef PEDIDOS_H
#define PEDIDOS_H

#include "cardapio.h"

// Enum para status dos pedidos
typedef enum {PENDENTE, EM_PREPARO, PRONTO, ENTREGUE} StatusPedido;

// Struct para representar um pedido
typedef struct {
    int cod_pedido;
    char nome_cliente[100];
    item* itens;
    int num_itens;
    StatusPedido status;
} Pedido;

// Funções de pedidos
void criar_pedido_menu(Pedido** pedidos, int* num_pedidos, int* capacidade_pedidos, item* cardapio, int codigo);
void gerenciar_pedidos(Pedido* pedidos, int num_pedidos);
void alterar_status(Pedido* pedidos, int num_pedidos);
void alterar_pedido(Pedido* pedidos, int num_pedidos, item* cardapio, int codigo);
void remover_pedido(Pedido* pedidos, int* num_pedidos);

#endif // PEDIDOS_H
