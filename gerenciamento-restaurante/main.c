#include <stdio.h>      // Para funções de entrada e saída
#include <stdlib.h>     // Para funções de alocação de memória
#include <string.h>     // Para manipulação de strings
#include <locale.h>     // Para configurar a localidade
#include "cardapio_pedidos/cardapio.h"
#include "cardapio_pedidos/pedidos.h"
#include "cardapio_pedidos/utilitarios.h" // Para as definições de estruturas e funções

int main() {
    setlocale(LC_ALL, "Portuguese");
    int *opcion = (int *)malloc(sizeof(int));
    int *opc = (int *)malloc(sizeof(int));

    int capacidade_cardapio = 2;
    item* cardapio = malloc(capacidade_cardapio * sizeof(item));
    if (cardapio == NULL) {
        printf(">> Erro ao alocar memória para o cardápio.\n");
        return 1;
    }

    int capacidade_pedidos = 2;
    Pedido* pedidos = malloc(capacidade_pedidos * sizeof(Pedido));
    if (pedidos == NULL) {
        printf(">> Erro ao alocar memória para os pedidos.\n");
        free(cardapio);
        return 1;
    }

    int codigo = 0;
    int num_pedidos = 0;

    while (1) {
        printf("\n========================================== Gerenciamento do Restaurante ===================================\n\n");
        printf("(1) Cadastrar item \n(2) Exibir cardápio\n(3) Atualizar cardápio\n(4) Remover itens do cardápio\n");
        printf("(5) Criar pedido\n(6) Gerenciar pedidos\n(7) Alterar status de pedidos\n(8) Alterar pedido\n(9) Remover pedido\n(10) Sair\n\n");
        while(1) {
            printf("<< Informe a opção: ");
            if(scanf("%d", opcion) != 1) {
                printf(">> Opção inválida. Por favor, tente novamente.\n");
                while(getchar() != '\n');
            } else { break; }
        }
        switch (*opcion) {
            case 1:
                if (codigo >= capacidade_cardapio) {
                    redimensionar_cardapio(&cardapio, &capacidade_cardapio);
                }
                printf("\n============================================== Cadastrar Item ==============================================\n\n");
                cadastro_card(&cardapio[codigo]);
                codigo++;
                printf(">> Item cadastrado com sucesso.\n");
                break;
            case 2:
                exibir_card(cardapio, codigo);
                break;
            case 3:
                if (codigo > 0) {
                    int num;
                    printf("\n>> Preencha com as informações do item que deseja atualizar.\n");
                    while(1) {
                        printf("Código do item: ");
                        if(scanf("%d", &num) != 1 || num < 1 || num > codigo) {
                            printf(">> Código inválido. Verifique se está correto e corresponde a um item cadastrado. Por favor, tente novamente.\n");
                            while(getchar() != '\n');
                        } else { break; }
                    }
                    num--;
                    printf("\n============================================= Atualizar Cardápio ============================================\n\n");
                    cadastro_card(&cardapio[num]);
                    printf(">> Item atualizado com sucesso.\n");
                } else {
                    printf(">> Não há itens cadastrados.\n");
                }
                break;
            case 4:
                if(codigo > 0) {
                    exibir_card(cardapio, codigo);
                }
                remover_card(cardapio, &codigo);
                break;
            case 5:
                criar_pedido_menu(cardapio, codigo, &pedidos, &num_pedidos, &capacidade_pedidos);
                break;
            case 6:
                gerenciar_pedidos(pedidos, num_pedidos);
                break;
            case 7:
                alterar_status(pedidos, num_pedidos);
                break;
            case 8:
                alterar_pedido(pedidos, num_pedidos, cardapio, codigo);
                break;
            case 9:
                remover_pedido(pedidos, &num_pedidos);
                break;
            case 10:
                while(1) {
                    printf("<< Tem certeza que deseja sair?\n[1] Sim\n[0] Não\n");
                    if(scanf("%d", opc) != 1) {
                        printf("<< Opção inválida. Por favor, insira [1] Sim ou [0] Não.\n");
                        while(getchar() != '\n');
                    } else if(*opc < 0 || *opc > 1) {
                        printf("<< Opção inválida. Por favor, insira [1] Sim ou [0] Não.\n");
                    } else { break; }
                }
                free(cardapio);
                free(pedidos);
                if(*opc == 1) {
                    printf(">> Obrigado, volte sempre.\n");
                    free(opcion);
                    free(opc);
                    return 0;
                }
                break;
            default:
                printf(">> Opção inválida. Por favor, tente novamente.\n");
                break;
        }
    }
}
