#ifndef UTILITARIOS_H
#define UTILITARIOS_H

#include "cardapio.h" // Inclua cardapio.h para usar a estrutura item

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
