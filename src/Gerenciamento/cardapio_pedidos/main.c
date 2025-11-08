#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include "cardapio.h"
#include "pedidos.h"
#include "utilitarios.h" // Supondo que você tenha um arquivo utilitarios.h

int main() {
    setlocale(LC_ALL, "pt_BR.UTF-8"); // Configurar a localidade para português
    system("chcp 65001"); // Mudar a página de código para UTF-8

    // Variável dinâmica para interagir com a interface principal
    int *opcion = (int *)malloc(sizeof(int)); 
    // Variável dinâmica para interagir com a interface de saída
    int *opc = (int *)malloc(sizeof(int));

    // Alocar memória inicial para o cardápio
    cardapio = malloc(capacidade_cardapio * sizeof(item));
    if (cardapio == NULL) { // Verifica se foi alocado na memória corretamente
        printf(">> Erro ao alocar memória para o cardápio.\n");
        return 1; // Sair do programa em caso de erro
    }
    
    // Alocar memória inicial para os pedidos
    pedidos = malloc(capacidade_pedidos * sizeof(Pedido));
    if (pedidos == NULL) {
        printf(">> Erro ao alocar memória para os pedidos.\n");
        free(cardapio); // Liberar memória do cardápio antes de sair
        return 1; // Sair do programa em caso de erro
    }

    while (1) { // Loop infinito que permite ao usuário interagir diversas vezes com a interface principal
        printf("\n========================================== Gerenciamento do Restaurante ===================================\n\n");
        printf("(1) Cadastrar item \n(2) Exibir cardápio\n(3) Atualizar cardápio\n(4) Remover itens do cardápio\n");
        printf("(5) Criar pedido\n(6) Gerenciar pedidos\n(7) Alterar status de pedidos\n(8) Alterar pedido\n(9) Remover pedido\n(10) Sair\n\n");
        
        while (1) { // Repetir até o usuário digitar um valor válido
            printf("<< Informe a opção: "); // Solicita ao usuário a opção
            if (scanf("%d", opcion) != 1) { // Garante que o usuário digite um int
                printf(">> Opção inválida. Por favor, tente novamente.\n");
                while (getchar() != '\n'); // Limpa o buffer de entrada
            } else {
                break; // Se o valor inserido for válido, sai do loop
            }
        }

        switch (*opcion) { // Permite ao usuário interagir com a interface
            case 1: // Cadastrar itens no cardápio
                if (codigo >= capacidade_cardapio) {
                    redimensionar_cardapio(); // Função para redimensionar o cardápio
                }
                printf("\n============================================== Cadastrar Item ==============================================\n\n");
                cadastro_card(&cardapio[codigo]); // Função para executar o processo de cadastro do item do cardápio
                codigo++; // Atualiza o índice
                printf(">> Item cadastrado com sucesso.\n"); // Mensagem de confirmação
                break;
            case 2: // Exibir o cardápio
                exibir_card(); // Função para exibir o cardápio
                break;
            case 3: // Atualizar os itens do cardápio
                if (codigo > 0) { // Verifica se há itens para atualizar
                    int num;
                    printf("\n>> Preencha com as informações do item que deseja atualizar.\n");
                    while (1) { // Repetição até um valor válido ser inserido
                        printf("Código do item: "); // Solicita ao usuário o código do item
                        if (scanf("%d", &num) != 1 || num < 1 || num > codigo) { // Garante que o valor inserido seja válido
                            printf(">> Código inválido. Verifique se está correto e corresponde a um item cadastrado. Por favor, tente novamente.\n");    
                            while (getchar() != '\n'); // Limpa o buffer de entrada
                        } else {
                            break; // Se o valor inserido for válido, sai do loop
                        }
                    }
                    num--; // Ajustar para índice
                    printf("\n============================================= Atualizar Cardápio ============================================\n\n");
                    cadastro_card(&cardapio[num]); // Função reaproveitada para atualizar o item escolhido
                    printf(">> Item atualizado com sucesso.\n"); // Mensagem de confirmação
                } else {
                    printf(">> Não há itens cadastrados.\n"); // Caso não haja itens cadastrados
                }
                break;
            case 4: // Remover itens do cardápio
                if (codigo > 0) {
                    exibir_card(); // Exibe o cardápio para saber o código do item que deseja remover
                }
                remover_card(); // Chama a função para executar o processo de remoção de itens
                break;
            case 5: // Criar um novo pedido
                criar_pedido_menu(); // Chama a função para executar o processo de criação de pedidos
                break;
            case 6: // Gerenciar pedidos
                gerenciar_pedidos(); // Chama a função para exibir os pedidos
                break;
            case 7: // Alterar status de pedidos
                alterar_status(); // Chama a função para executar o processo de atualização de status do pedido
                break;
            case 8: // Alterar um pedido existente
                alterar_pedido(); // Chama a função para executar o processo de alteração de pedidos
                break;
            case 9: // Remover um pedido
                remover_pedido(); // Chama a função para executar o processo de remoção de pedidos
                break;
            case 10: // Sair do sistema
                while (1) { // Repete até que o usuário digite um valor válido
                    printf("<< Tem certeza que deseja sair?\n[1] Sim\n[0] Não\n"); // Pergunta se o usuário tem certeza
                    if (scanf("%d", opc) != 1) { // Garante que o usuário só digite o valor rápido
                        printf("<< Opção inválida. Por favor, insira [1] Sim ou [0] Não.\n");
                        while (getchar() != '\n');    
                    } else if (*opc < 0 || *opc > 1) {
                        printf("<< Opção inválida. Por favor, insira [1] Sim ou [0] Não.\n");
                    } else {
                        break; // Se o valor inserido for válido, sai do loop
                    }
                }
                free(cardapio); // Libera a variável dinâmica cardapio para evitar vazamento de memória
                free(pedidos); // Libera a variável dinâmica pedidos para evitar vazamento de memória
                if (*opc == 1) { // Verifica se o usuário escolheu a opção 1
                    printf(">> Obrigado, volte sempre.\n");
                    free(opcion); // Libera a variável dinâmica opcion para evitar vazamento de memória
                    free(opc); // Libera a variável dinâmica opc para evitar vazamento de memória
                    return 0; // Fecha o sistema
                }
                break;
            default: // Caso o usuário digite uma opção inválida
                printf(">> Opção inválida. Por favor, tente novamente.\n");
                break;
        }
    }
}
