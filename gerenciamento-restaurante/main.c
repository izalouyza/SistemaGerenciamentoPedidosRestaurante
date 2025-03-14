#include <stdio.h>      // Para funções de entrada e saída
#include <stdlib.h>     // Para funções de alocação de memória
#include <string.h>     // Para manipulação de strings
#include <locale.h>     // Para configurar a localidade
#include "cardapio_pedidos/cardapio.h"
#include "cardapio_pedidos/pedidos.h"
#include "cardapio_pedidos/utilitarios.h" // Para as definições de estruturas e funções

int main() {
    setlocale(LC_ALL, "Portuguese"); // Configura a localidade para português
    int *opcion = (int *)malloc(sizeof(int)); // Aloca memória para a opção do menu
    int *opc = (int *)malloc(sizeof(int)); // Aloca memória para a opção de sair

    int capacidade_cardapio = 2; // Capacidade inicial do cardápio
    item* cardapio = malloc(capacidade_cardapio * sizeof(item)); // Aloca memória para o cardápio
    if (cardapio == NULL) {
        printf(">> Erro ao alocar memória para o cardápio.\n");
        return 1; // Sai do programa em caso de erro
    }

    int capacidade_pedidos = 2; // Capacidade inicial para pedidos
    Pedido* pedidos = malloc(capacidade_pedidos * sizeof(Pedido)); // Aloca memória para os pedidos
    if (pedidos == NULL) {
        printf(">> Erro ao alocar memória para os pedidos.\n");
        free(cardapio); // Libera a memória do cardápio antes de sair
        return 1; // Sai do programa em caso de erro
    }

    int codigo = 0; // Contador de itens no cardápio
    int num_pedidos = 0; // Contador de pedidos

    while (1) { // Loop principal
        printf("\n========================================== Gerenciamento do Restaurante ===================================\n\n");
        printf("(1) Cadastrar item \n(2) Exibir cardápio\n(3) Atualizar cardápio\n(4) Remover itens do cardápio\n");
        printf("(5) Criar pedido\n(6) Gerenciar pedidos\n(7) Alterar status de pedidos\n(8) Alterar pedido\n(9) Remover pedido\n(10) Sair\n\n");
        
        while(1) { // Loop para entrada da opção
            printf("<< Informe a opção: ");
            if(scanf("%d", opcion) != 1) { // Lê a opção do usuário
                printf(">> Opção inválida. Por favor, tente novamente.\n");
                while(getchar() != '\n'); // Limpa o buffer
            } else { break; } // Sai do loop se a entrada for válida
        }

        switch (*opcion) { // Verifica a opção escolhida
            case 1: // Cadastrar item
                if (codigo >= capacidade_cardapio) {
                    redimensionar_cardapio(&cardapio, &capacidade_cardapio); // Redimensiona o cardápio se necessário
                }
                printf("\n============================================== Cadastrar Item ==============================================\n\n");
                cadastro_card(&cardapio[codigo]); // Cadastra o item
                codigo++; // Incrementa o contador de itens
                printf(">> Item cadastrado com sucesso.\n");
                break;

            case 2: // Exibir cardápio
                exibir_card(cardapio, codigo); // Exibe o cardápio
                break;

            case 3: // Atualizar cardápio
                if (codigo > 0) {
                    int num;
                    printf("\n>> Preencha com as informações do item que deseja atualizar.\n");
                    while(1) {
                        printf("Código do item: ");
                        if(scanf("%d", &num) != 1 || num < 1 || num > codigo) { // Verifica se o código é válido
                            printf(">> Código inválido. Verifique se está correto e corresponde a um item cadastrado. Por favor, tente novamente.\n");
                            while(getchar() != '\n'); // Limpa o buffer
                        } else { break; } // Sai do loop se a entrada for válida
                    }
                    num--; // Ajusta o índice
                    printf("\n============================================= Atualizar Cardápio ============================================\n\n");
                    cadastro_card(&cardapio[num]); // Atualiza o item
                    printf(">> Item atualizado com sucesso.\n
                                    } else {
                    printf(">> Não há itens cadastrados.\n");
                }
                break;

            case 4: // Remover itens do cardápio
                if(codigo > 0) {
                    exibir_card(cardapio, codigo); // Exibe o cardápio para que o usuário saiba qual item remover
                }
                remover_card(cardapio, &codigo); // Chama a função para remover o item
                break;

            case 5: // Criar um novo pedido
                criar_pedido_menu(cardapio, codigo, &pedidos, &num_pedidos, &capacidade_pedidos); // Chama a função para criar um pedido
                break;

            case 6: // Gerenciar pedidos
                gerenciar_pedidos(pedidos, num_pedidos); // Chama a função para gerenciar pedidos
                break;

            case 7: // Alterar status de pedidos
                alterar_status(pedidos, num_pedidos); // Chama a função para alterar o status dos pedidos
                break;

            case 8: // Alterar um pedido existente
                alterar_pedido(pedidos, num_pedidos, cardapio, codigo); // Chama a função para alterar um pedido
                break;

            case 9: // Remover um pedido
                remover_pedido(pedidos, &num_pedidos); // Chama a função para remover um pedido
                break;

            case 10: // Sair do sistema
                while(1) {
                    printf("<< Tem certeza que deseja sair?\n[1] Sim\n[0] Não\n");
                    if(scanf("%d", opc) != 1) { // Lê a opção de sair
                        printf("<< Opção inválida. Por favor, insira [1] Sim ou [0] Não.\n");
                        while(getchar() != '\n'); // Limpa o buffer
                    } else if(*opc < 0 || *opc > 1) {
                        printf("<< Opção inválida. Por favor, insira [1] Sim ou [0] Não.\n");
                    } else { break; } // Sai do loop se a entrada for válida
                }
                free(cardapio); // Libera a memória do cardápio
                free(pedidos); // Libera a memória dos pedidos
                if(*opc == 1) { // Verifica se o usuário escolheu sair
                    printf(">> Obrigado, volte sempre.\n");
                    free(opcion); // Libera a memória de opcion
                    free(opc); // Libera a memória de opc
                    return 0; // Sai do programa
                }
                break;

            default: // Caso o usuário digite uma opção inválida
                printf(">> Opção inválida. Por favor, tente novamente.\n");
                break;
        }
    }
}
