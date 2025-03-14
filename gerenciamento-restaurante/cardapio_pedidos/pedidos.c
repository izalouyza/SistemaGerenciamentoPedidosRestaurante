#include "pedidos.h"

// Função para inicializar um pedido
void inicializar_pedido(pedido* p) {
    p->numero_pedido = 0;
    p->itens = NULL;
    p->total_itens = 0;
    p->total_pedido = 0.0;
}

// Função para adicionar um item ao pedido
void adicionar_item_pedido(pedido* p, int codigo_item, int quantidade, float preco_unitario) {
    p->itens = realloc(p->itens, (p->total_itens + 1) * sizeof(pedido_item));
    if (p->itens == NULL) {
        printf(">> Erro ao alocar memória para os itens do pedido.\n");
        exit(1);
    }
    p->itens[p->total_itens].codigo_item = codigo_item;
    p->itens[p->total_itens].quantidade = quantidade;
    p->itens[p->total_itens].preco_unitario = preco_unitario;
    p->total_pedido += quantidade * preco_unitario;
    p->total_itens++;
}

// Função para remover um item do pedido
void remover_item_pedido(pedido* p, int codigo_item) {
    for (int i = 0; i < p->total_itens; i++) {
        if (p->itens[i].codigo_item == codigo_item) {
            p->total_pedido -= p->itens[i].quantidade * p->itens[i].preco_unitario;
            for (int j = i; j < p->total_itens - 1; j++) {
                p->itens[j] = p->itens[j + 1];
            }
            p->total_itens--;
            p->itens = realloc(p->itens, p->total_itens * sizeof(pedido_item));
            return;
        }
    }
    printf(">> Item com código %d não encontrado no pedido.\n", codigo_item);
}

// Função para exibir o pedido
void exibir_pedido(const pedido* p) {
    printf("\n======================== Pedido ========================\n");
    printf("Número do Pedido: %d\n", p->numero_pedido);
    printf("%-10s %-10s %-15s %-10s\n", "Código", "Quantidade", "Preço Unitário", "Subtotal");
    printf("-------------------------------------------------------\n");
    for (int i = 0; i < p->total_itens; i++) {
        float subtotal = p->itens[i].quantidade * p->itens[i].preco_unitario;
        printf("%-10d %-10d %-15.2f %-10.2f\n", p->itens[i].codigo_item, p->itens[i].quantidade, p->itens[i].preco_unitario, subtotal);
    }
    printf("-------------------------------------------------------\n");
    printf("Total do Pedido: R$ %.2f\n", p->total_pedido);
    printf("=======================================================\n");
}

// Função para liberar a memória do pedido
void liberar_pedido(pedido* p) {
    free(p->itens);
    p->itens = NULL;
    p->total_itens = 0;
    p->total_pedido = 0.0;
}
