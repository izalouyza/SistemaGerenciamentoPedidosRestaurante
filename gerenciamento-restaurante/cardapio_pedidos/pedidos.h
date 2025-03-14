#ifndef PEDIDOS_H
#define PEDIDOS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Enum para status dos pedidos
typedef enum {pendente, em_preparo, pronto, entregue} StatusPedido;

// Struct para representar um item do cardápio
typedef struct {
    char nome[100];      // Nome do item
    char descri[100];    // Descrição do item
    float preco;         // Preço em R$ do item
    int catego; // Categoria do item
    } item;

// Struct para representar um pedido
typedef struct {
    int cod_pedido;          // Identificador do pedido
    char nome_cliente[100];  // Nome do cliente
    item* itens;            // Armazenar os itens do pedido
    int num_itens;          // Número de itens no pedido
    StatusPedido status;     // Status do pedido
} Pedido;

// Funções para gerenciar pedidos
void criar_pedido_menu();
void inicializar_pedido(Pedido* pedido, int num_itens);
void gerenciar_pedidos();
void alterar_status();
void alterar_pedido();
void remover_pedido();
const char* status_para_string(StatusPedido status);

// Declarações de variáveis globais
extern Pedido* pedidos;          // Declaração da variável global para pedidos
extern int capacidade_pedidos;   // Declaração da variável global para capacidade de pedidos
extern int num_pedidos;          // Declaração da variável global para número de pedidos

#endif // PEDIDOS_H
