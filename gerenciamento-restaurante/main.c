#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include "cardapio_pedidos/cardapio.h"
#include "cardapio_pedidos/pedidos.h"
#include "cardapio_pedidos/utilitarios.h"

int main() {
    setlocale(LC_ALL, "Portuguese");

    item* cardapio = NULL;
    int codigo = 0;
    int capacidade_cardapio = 2;

    Pedido* pedidos = NULL;
    int num_pedidos = 0;
    int capacidade_pedidos = 2;

    // Alocação inicial de memória
    cardapio = malloc(capacidade_cardapio * sizeof(item));
    pedidos = malloc(capacidade_pedidos * sizeof(Pedido));

    // Loop principal
    while (1) {
        // Exibir menu e processar opções
    }

    // Liberar memória
    free(cardapio);
    free(pedidos);
    return 0;
}
