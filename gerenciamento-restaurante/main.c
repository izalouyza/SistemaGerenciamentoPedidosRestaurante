#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include "cardapio.h"
#include "pedidos.h"
#include "utilitarios.h"

// Variáveis globais
item* cardapio = NULL; // Armazenar itens do cardápio
int codigo = 0; // Contador de itens no cardápio
int capacidade_cardapio = 2; // Capacidade inicial do cardápio

pedido* pedidos = NULL; // Armazenar pedidos
int num_pedidos = 0; // Contador de pedidos
int capacidade_pedidos = 2; // Capacidade inicial para pedidos

// Função principal
int main() {
    setlocale(LC_ALL, "Portuguese");

    // Inicializar o cardápio
    inicializar_cardapio(&cardapio, &capacidade_cardapio);
    
    // Inicializar a lista de pedidos
    pedidos = malloc(capacidade_pedidos * sizeof(pedido));
    if (pedidos == NULL) {
        printf(">> Erro ao alocar memória para os pedidos.\n");
        free(cardapio);
        return 1;
    }

    int opcao;
    while (1) {
        printf("\n========================================== Gerenciamento do Restaurante ===================================\n\n");
        printf("(1) Cadastrar item \n(2) Exibir cardápio\n(3) Atualizar cardápio\n(4) Remover itens do cardápio\n");
        printf("(5) Criar pedido\n(6) Gerenciar pedidos\n(7) Alterar status de pedidos\n(8) Alterar pedido\n(9) Remover pedido\n(10) Sair\n\n");
        
        opcao = ler_inteiro("<< Informe a opção: "); // Usando a função utilitária para ler a opção

        switch (opcao) {
            case 1: // Cadastrar itens no cardápio
                if (codigo >= capacidade_cardapio) {
                    redimensionar_cardapio(&cardapio, &capacidade_cardapio);
                }
                printf("\n============================================== Cadastrar Item ==============================================\n\n");
                cadastro_card(&cardapio[codigo]);
                codigo++;
                printf(">> Item cadastrado com sucesso.\n");
                break;
            case 2: // Exibir o cardápio
                exibir_card(cardapio, codigo);
                break;
            case 3: // Atualizar os itens do cardápio
                if (codigo > 0) {
                    int num = ler_inteiro("Código do item: ");
                    if (num >= 1 && num <= codigo) {
                        num--; // Ajustar para índice
                        printf("\n============================================= Atualizar Cardápio ============================================\n\n");
                        cadastro_card(&cardapio[num]);
                        printf(">> Item atualizado com sucesso.\n");
                    } else {
                        printf(">> Código inválido.\n");
                    }
                } else {
                    printf(">> Não há itens cadastrados.\n");
                }
                break;
            case 4: // Remover itens do cardápio
                if (codigo > 0) {
                    exibir_card(cardapio, codigo);
                }
                remover_card(cardapio, &codigo);
                break;
            case 5: // Criar um novo pedido
               criar_pedido_menu(); // chama a função para executar o processo de criação de pedidos
                break;
            case 6: // Gerenciar pedidos
                gerenciar_pedidos(); // chama a função para exibir os pedidos
                break;
            case 7: // Alterar status de pedidos
                alterar_status(); // chama a função para executar o processo de atualização de status do pedido
                break;
            case 8: // Alterar um pedido
               alterar_pedido(); // chama a função para executar o processo de alteração de pedidos
                break;
            case 9: // Remover um pedido
               remover_pedido(); // chama a função para executar o processo de remoção de pedidos
                break;
            case 10: // Sair do sistema
                printf(">> Obrigado, volte sempre.\n");
                free(cardapio);
                free(pedidos);
                return 0;
            default: // Opção inválida
                printf(">> Opção inválida. Por favor, tente novamente.\n");
                break;
        }
    }
}
