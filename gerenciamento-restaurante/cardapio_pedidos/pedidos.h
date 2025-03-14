#ifndef PEDIDOS_H
#define PEDIDOS_H

#include "cardapio.h" // Inclua cardapio.h para usar a estrutura item

// Enumeração para o status dos pedidos
typedef enum {PENDENTE, EM_PREPARO, PRONTO, ENTREGUE} StatusPedido;

// Estrutura para representar um pedido
typedef struct {
    int cod_pedido;
    char nome_cliente[100];
    item* itens;
    int num_itens;
    StatusPedido status;
} Pedido;

// Funções para gerenciar pedidos
void criar_pedido_menu(Pedido* pedidos, int* num_pedidos, item* cardapio, int codigo);
void gerenciar_pedidos(Pedido* pedidos, int num_pedidos);
void alterar_status(Pedido* pedidos, int num_pedidos);
void alterar_pedido(Pedido* pedidos, int num_pedidos, item* cardapio, int codigo);
void remover_pedido(Pedido* pedidos, int* num_pedidos);

#endif // PEDIDOS_H
