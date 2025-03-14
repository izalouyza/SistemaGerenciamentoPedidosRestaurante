#include <stdio.h>      // Para funções de entrada e saída
#include <stdlib.h>     // Para alocação de memória
#include <string.h>     // Para manipulação de strings
#include "cardapio_pedidos/cardapio.h" // Para usar a estrutura item e a enumeração categoria
#include "cardapio_pedidos/pedidos.h" // Para usar a estrutura Pedido e as funções relacionadas



// Definindo um valor inicial para a capacidade de pedidos
int capacidade_pedidos = 2; 

// Implementação das funções relacionadas aos pedidos
void criar_pedido_menu(Pedido** pedidos, int* num_pedidos, item* cardapio, int codigo) {
    if (codigo > 0) { // Verificar se há itens a oferecer ao cliente
        char nome_cliente[100];
        printf("Nome do cliente: "); // Solicita o nome do cliente
        getchar(); // Limpar o buffer
        fgets(nome_cliente, sizeof(nome_cliente), stdin); // Recebe o nome do cliente
        nome_cliente[strcspn(nome_cliente, "\n")] = 0; // Remover a quebra de linha

        int num_itens_pedido; // Determina quantos itens o cliente gostaria de consumir
        while(1) { // Repetição até um valor válido ser inserido
            printf("Quantidade de itens: "); // Solicita a quantidade de itens
            if(scanf("%d", &num_itens_pedido) != 1 || num_itens_pedido <= 0) { // Garante que o valor inserido seja válido
                printf(">> Quantidade inválida. A quantidade de itens não pode ser negativa ou incluir letras e caracteres especiais. Por favor, tente novamente.\n");
                while(getchar() != '\n'); // Limpa o buffer de entrada
            } else { 
                break; 
            } // Se o valor for válido, sai do loop
        }

        // Redimensionar o array de pedidos se necessário
        if (*num_pedidos >= capacidade_pedidos) { 
            capacidade_pedidos *= 2;
            Pedido* temp = realloc(*pedidos, capacidade_pedidos * sizeof(Pedido));
            if (temp == NULL) {
                printf(">> Erro ao redimensionar os pedidos.\n");
                free(*pedidos); // Libera a memória anterior se realloc falhar
                exit(1); // Sair do programa em caso de erro
            }
            *pedidos = temp; // Atualiza o ponteiro original
        }

        Pedido novo_pedido;
        novo_pedido.cod_pedido = *num_pedidos + 1;
        strncpy(novo_pedido.nome_cliente, nome_cliente, sizeof(novo_pedido.nome_cliente) - 1);
        novo_pedido.num_itens = num_itens_pedido;
        novo_pedido.status = PENDENTE;  // Status inicial
        novo_pedido.itens = malloc(num_itens_pedido * sizeof(item)); // Alocar memória para os itens do pedido

        if (novo_pedido.itens == NULL) {
            printf(">> Erro ao alocar memória para os itens do pedido.\n");
            exit(1);
        }

        for (int i = 0; i < num_itens_pedido; i++) {
            int codigo_item;
            while(1) { // Repetição até um valor válido ser inserido
                printf("Código do item %d: ", i + 1); // Solicita o código do item
                if(scanf("%d", &codigo_item) != 1 || codigo_item < 1 || codigo_item > codigo) { // Garante que o valor inserido seja válido
                    printf(">> Código inválido. Verifique se está correto e corresponde a um item cadastrado. Por favor, tente novamente.\n");
                    while(getchar() != '\n'); // Limpa o buffer de entrada
                } else {
                    novo_pedido.itens[i] = cardapio[codigo_item - 1];  
                    break;
                }
            }
        }

        (*pedidos)[*num_pedidos] = novo_pedido; // Atualiza o pedido
        (*num_pedidos)++;
        printf("\n>> Pedido %d criado com sucesso.\n", novo_pedido.cod_pedido);
        printf("Nome do cliente: %s\n", novo_pedido.nome_cliente);
        printf("Itens do Pedido:\n");
        for (int i = 0; i < novo_pedido.num_itens; i++) {
            printf("  %s - R$ %.2f\n", novo_pedido.itens[i].nome, novo_pedido.itens[i].preco);
        }
        printf("Status: Pendente\n\n");
    } else {
        printf(">> Operação inválida. Não há itens cadastrados no cardápio. Por favor, tente novamente.\n");
    }
}
