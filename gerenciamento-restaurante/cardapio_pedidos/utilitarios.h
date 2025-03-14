#ifndef UTILITARIOS_H
#define UTILITARIOS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

// Enumeração de categorias do cardápio
typedef enum {entrada, principal, sobremesa, bebida} categoria;
extern char* categs[];

// Struct para representar um item do cardápio
typedef struct {
    char nome[100];
    char descri[100];
    float preco;
    categoria catego;
} item;

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

// Funções para manipulação do cardápio
void exibir_card(item* cardapio, int codigo);
void cadastro_card(item *p);
void redimensionar_cardapio(item** cardapio, int* capacidade_cardapio);
void remover_card(item* cardapio, int* codigo);
void criar_pedido_menu(item* cardapio, int codigo, Pedido** pedidos, int* num_pedidos, int* capacidade_pedidos);
void gerenciar_pedidos(Pedido* pedidos, int num_pedidos);
void alterar_status(Pedido* pedidos, int num_pedidos);
void alterar_pedido(Pedido* pedidos, int num_pedidos, item* cardapio, int codigo);
void remover_pedido(Pedido* pedidos, int* num_pedidos);

#endif // UTILITARIO_H
