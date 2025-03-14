#ifndef UTILITARIOS_H
#define UTILITARIOS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

// Enumeração de categorias do cardápio
typedef enum {entrada, principal, sobremesa, bebida} categoria;
extern char* categs[]; // Declaração externa para o array categs

// Struct para representar um item do cardápio
typedef struct {
    char nome[100]; // Nome do item
    char descri[100]; // Descrição do item
    float preco; // Preço do item
    categoria catego; // Categoria do item
} item;

// Enum para status dos pedidos
typedef enum {PENDENTE, EM_PREPARO, PRONTO, ENTREGUE} StatusPedido;

// Struct para representar um pedido
typedef struct {
    int cod_pedido; // Código do pedido
    char nome_cliente[100]; // Nome do cliente
    item* itens; // Ponteiro para os itens do pedido
    int num_itens; // Número de itens no pedido
    StatusPedido status; // Status do pedido
} Pedido;

// Funções para manipulação do cardápio e pedidos
void exibir_card(item* cardapio, int codigo);
void cadastro_card(item *p);
void redimensionar_cardapio(item** cardapio, int* capacidade_cardapio);
void remover_card(item* cardapio, int* codigo);
void criar_pedido_menu(item* cardapio, int codigo, Pedido** pedidos, int* num_pedidos, int* capacidade_pedidos);
void gerenciar_pedidos(Pedido* pedidos, int num_pedidos);
void alterar_status(Pedido* pedidos, int num_pedidos);
void alterar_pedido(Pedido* pedidos, int num_pedidos, item* cardapio, int codigo);
void remover_pedido(Pedido* pedidos, int* num_pedidos);

#endif // UTILITARIOS_H
