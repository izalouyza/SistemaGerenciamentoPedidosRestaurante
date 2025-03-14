#include <stdio.h>      // Para funções de entrada e saída
#include <stdlib.h>     // Para funções de alocação de memória (malloc, realloc, free)
#include <string.h>     // Para funções de manipulação de strings (strncpy)
#include "pedidos.h"    // Para as definições de tipos e funções de pedidos
#include "cardapio.h"   // Para a definição da struct item e a função status_para_string

void criar_pedido_menu(Pedido** pedidos, int* num_pedidos, int* capacidade_pedidos, item* cardapio, int codigo) {
    if (codigo > 0) {
        char nome_cliente[100];
        printf("Nome do cliente: ");
        getchar(); // Limpar o buffer
        fgets(nome_cliente, sizeof(nome_cliente), stdin);
        nome_cliente[strcspn(nome_cliente, "\n")] = 0; // Remover a quebra de linha

        int num_itens_pedido;
        while(1) {
            printf("Quantidade de itens: ");
            if(scanf("%d", &num_itens_pedido) != 1 || num_itens_pedido <= 0) {
                printf("Quantidade inválida. A quantidade de itens não pode ser negativa ou incluir letras e caracteres especiais. Por favor, tente novamente.\n");
                while(getchar() != '\n');
            } else {
                break;
            }
        }

        // Verifica se é necessário redimensionar a lista de pedidos
        if (*num_pedidos >= *capacidade_pedidos) {
            *capacidade_pedidos *= 2;
            Pedido* temp = realloc(*pedidos, *capacidade_pedidos * sizeof(Pedido));
            if (temp == NULL) {
                printf("Erro ao redimensionar os pedidos.\n");
                exit(1); // Sair do programa em caso de erro
            }
            *pedidos = temp;
        }

        Pedido novo_pedido;
        novo_pedido.cod_pedido = *num_pedidos + 1;
        strncpy(novo_pedido.nome_cliente, nome_cliente, sizeof(novo_pedido.nome_cliente) - 1);
        novo_pedido.num_itens = num_itens_pedido;
        novo_pedido.status = PENDENTE;  // Status inicial
        novo_pedido.itens = malloc(num_itens_pedido * sizeof(item)); // Alocar memória para os itens do pedido

        for (int i = 0; i < num_itens_pedido; i++) {
            int codigo_item;
            while(1) {
                printf("Código do item %d: ", i + 1);
                if(scanf("%d", &codigo_item) != 1 || codigo_item < 1 || codigo_item > codigo) {
                    printf(">> Código inválido. Verifique se está correto e corresponde a um item cadastrado. Por favor, tente novamente.\n");
                    while(getchar() != '\n');
                } else {
                    novo_pedido.itens[i] = cardapio[codigo_item - 1];    
                    break;
                }
            }
        }

        (*pedidos)[*num_pedidos] = novo_pedido; // Adiciona o novo pedido à lista de pedidos
        (*num_pedidos)++; // Incrementa o contador de pedidos
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

void gerenciar_pedidos(Pedido* pedidos, int num_pedidos) {
    if (num_pedidos > 0) {
        printf("\n=========================================== Pedidos Realizados ============================================\n\n");
        for (int i = 0; i < num_pedidos; i++) {
            printf("\nPedido %d:\n", pedidos[i].cod_pedido);
            printf("Status: %s\n", status_para_string(pedidos[i].status));
            printf("Cliente: %s\n", pedidos[i].nome_cliente);
            printf("Itens do Pedido:\n");
            float total = 0; // Inicializar total
            for (int j = 0; j < pedidos[i].num_itens; j++) {
                printf("-> %s - R$ %.2f\n", pedidos[i].itens[j].nome, pedidos[i].itens[j].preco);
                total += pedidos[i].itens[j].preco;
            }
            printf("Total: R$ %.2f\n", total);
            printf("\n===========================================================================================================\n\n");
        }
    } else {
        printf(">> Não há pedidos para exibir.\n\n");
    }
}

void alterar_status(Pedido* pedidos, int num_pedidos) {
    if (num_pedidos > 0) {
        printf("\n>> Preencha com as informações do pedido que deseja atualizar.\n");
        int cod_pedido;
        while(1) {
            printf("Número do pedido: ");
            if(scanf("%d", &cod_pedido) != 1 || cod_pedido <= 0 || cod_pedido > num_pedidos) {
                printf("Número inválido. Verifique se está correto e corresponde a um pedido cadastrado. Por favor, tente novamente.\n");
                while(getchar() != '\n');
            } else {
                break;
            }
        }
        cod_pedido--; // Ajuste do índice
        int opcao;
        while(1) {
            printf("\nStatus:\n");
            printf("(1) Pendente\n(2) Em preparo\n(3) Pronto\n(4) Entregue\n");
            printf("Informe o status: ");
            if(scanf("%d", &opcao) != 1 || opcao < 1 || opcao > 4) {
                printf(">> Opção inválida. Por favor, tente novamente.\n");
                while(getchar() != '\n');
            } else {
                break;
            }
        }
        pedidos[cod_pedido].status = (StatusPedido)(opcao - 1);
        printf("Status do pedido %d alterado para: %s\n", cod_pedido + 1, status_para_string(pedidos[cod_pedido].status));

        // Verifica se o status foi alterado para "Entregue"
        if (pedidos[cod_pedido].status == ENTREGUE) {
            printf(">> O pedido %d foi finalizado e entregue ao cliente.\n", cod_pedido + 1);
        }
    } else {
        printf(">> Não há pedidos cadastrados.\n\n");
    }
}

void alterar_pedido(Pedido* pedidos, int num_pedidos, item* cardapio, int codigo) {
    if(num_pedidos > 0) {
        printf("\n>> Preencha com as informações do pedido que deseja atualizar.\n");
        int cod_pedido;
        while(1) {
            printf("Número do pedido: ");
            if(scanf("%d", &cod_pedido) != 1 || cod_pedido <= 0 || cod_pedido > num_pedidos) {
                printf("Número inválido. Verifique se está correto e corresponde a um pedido cadastrado. Por favor, tente novamente.\n");
                while(getchar() != '\n');
            } else {
                break;
            }
        }
        cod_pedido--; // Ajuste do índice
        Pedido *pedido = &pedidos[cod_pedido];
        printf("\nAlterando o pedido %d de %s:\n", pedido->cod_pedido, pedido->nome_cliente);
        int num_itens_pedido;
        printf("Quantidade de itens: ");
        scanf("%d", &num_itens_pedido);

        if (num_itens_pedido > 0) {
            pedido->num_itens = num_itens_pedido;
            // Receber os novos itens do pedido
            for (int i = 0; i < num_itens_pedido; i++) {
                int codigo_item;
                while(1) {
                    printf("Código do item %d do pedido: ", i + 1);
                    if(scanf("%d", &codigo_item) != 1 || codigo_item <= 0 || codigo_item > codigo) {
                        printf("Código inválido. Verifique se está correto e corresponde a um item cadastrado. Por favor, tente novamente.\n");
                        while(getchar() != '\n');
                    } else {
                        pedido->itens[i] = cardapio[codigo_item - 1]; // Atualizar item do pedido
                        break;
                    }
                }
            }
            printf(">> Pedido %d atualizado com sucesso.\n", pedido->cod_pedido);
        } else {
            printf(">> Número de itens inválido. Operação cancelada.\n");
        }
    } else {
        printf(">> Não há pedidos cadastrados.\n");
    }
}

void remover_pedido(Pedido* pedidos, int* num_pedidos) {
    if(*num_pedidos > 0) {
        printf("\n>> Preencha com as informações do pedido que deseja remover.\n");
        int cod_pedido;
        while(1) {
            printf("Número do pedido: ");
            if(scanf("%d", &cod_pedido) != 1 || cod_pedido <= 0 || cod_pedido > *num_pedidos) {
                printf("Número inválido. Verifique se está correto e corresponde a um pedido cadastrado. Por favor, tente novamente.\n");
                while(getchar() != '\n');
            } else {
                break;
            }
        }
        cod_pedido--; // Ajuste do índice
        // Remover pedido e reorganizar lista
        for (int i = cod_pedido; i < *num_pedidos - 1; i++) {
            pedidos[i] = pedidos[i + 1];
        }
        (*num_pedidos)--; // Diminui o contador de pedidos
        printf("Pedido removido com sucesso.\n");
    } else {
        printf(">> Não há pedidos cadastrados.\n");
    }
}
