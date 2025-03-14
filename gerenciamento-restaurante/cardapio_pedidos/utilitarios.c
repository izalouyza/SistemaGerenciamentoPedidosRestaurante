#include <stdio.h>      // Para funções de entrada e saída
#include <stdlib.h>     // Para funções de alocação de memória
#include <string.h>     // Para manipulação de strings
#include "cardapio_pedidos/utilitarios.h" // Para as definições de estruturas e funções

// Definição das categorias
char* categs[] = {"Entrada", "Principal", "Sobremesa", "Bebida"};

// Função para exibir o cardápio
void exibir_card(item* cardapio, int codigo) {
    if(codigo > 0) {
        printf("\n================================================= Cardápio ================================================\n\n");
        printf("%-10s %-20s %-40s %-15s %-10s\n", "Código", "Nome", "Descrição", "Preço R$", "Categoria");
        printf("___________________________________________________________________________________________________________\n\n");
        for(int i = 0; i < codigo; i++) {
            printf("%-10d %-20s %-40s %-15.2f %-10s\n", i + 1, cardapio[i].nome, cardapio[i].descri, cardapio[i].preco, categs[cardapio[i].catego]);
        }
        printf("___________________________________________________________________________________________________________\n\n");
    } else {
        printf(">> Não há itens cadastrados.\n\n");
    }
}

// Função para cadastrar itens no cardápio
void cadastro_card(item *p) {
    getchar();
    printf("Nome do item: ");
    fgets(p->nome, sizeof(p->nome), stdin);
    p->nome[strcspn(p->nome, "\n")] = 0;

    printf("Descrição [máx.: 100 caracteres]: ");
    fgets(p->descri, sizeof(p->descri), stdin);
    p->descri[strcspn(p->descri, "\n")] = 0;

    while (1) {
        printf("Preço em R$: ");
        if (scanf("%f", &p->preco) != 1) {
            printf(">> Valor inválido. O preço não pode incluir letras e caracteres especiais. Por favor, tente novamente.\n");
            while(getchar() != '\n');
        } else if (p->preco < 0) {
            printf(">> Valor inválido. O preço não pode ser um valor negativo. Por favor, tente novamente.\n");
        } else { break; }
    }

    printf("\nCategoria: \n");
    while(1) {
        printf("(1) Entrada\n(2) Principal\n(3) Sobremesa\n(4) Bebida\n");
        printf("<< Informe a opção: ");
        int n;
        if(scanf("%d", &n) != 1 || n < 1 || n > 4) {
            printf(">> Opção inválida. Por favor, tente novamente.\n");
            while(getchar() != '\n');
        } else {
            p->catego = (categoria)(n - 1);
            break;
        }
    }
}

// Função para redimensionar o cardápio
void redimensionar_cardapio(item** cardapio, int* capacidade_cardapio) {
    *capacidade_cardapio *= 2;
    item* temp = realloc(*cardapio, (*capacidade_cardapio) * sizeof(item));
    if (temp == NULL) {
        printf(">> Erro ao redimensionar o cardápio.\n");
        exit(1);
    }
    *cardapio = temp;
}

// Função para remover itens do cardápio
void remover_card(item* cardapio, int* codigo) {
    if(*codigo > 0) {
        int num;
        printf("\n>> Preencha com as informações do item que deseja remover.\n");
        while(1) {
            printf("Código do item: ");
            if(scanf("%d", &num) != 1 || num < 1 || num > *codigo) {
                printf(">> Código inválido. Verifique se está correto e corresponde a um item cadastrado. Por favor, tente novamente.\n");
                while(getchar() != '\n');
            } else { break; }
        }
        num--;
        for(int i = num; i < *codigo - 1; i++) {
            cardapio[i] = cardapio[i + 1];
        }
        (*codigo)--;
        printf(">> Item removido com sucesso.\n\n");
    } else {
        printf(">> Não há itens cadastrados.\n\n");
    }
}

// Função para criar um novo pedido
void criar_pedido_menu(item* cardapio, int codigo, Pedido** pedidos, int* num_pedidos, int* capacidade_pedidos) {
    if (codigo > 0) {
        char nome_cliente[100];
        printf("Nome do cliente: ");
        getchar();
        fgets(nome_cliente, sizeof(nome_cliente), stdin);
        nome_cliente[strcspn(nome_cliente, "\n")] = 0;

        int num_itens_pedido;
        while(1) {
            printf("Quantidade de itens: ");
            if(scanf("%d", &num_itens_pedido) != 1 || num_itens_pedido <= 0) {
                printf(">> Quantidade inválida. A quantidade de itens não pode ser negativa ou incluir letras e caracteres especiais. Por favor, tente novamente.\n");
                while(getchar() != '\n');
            } else { break; }
        }

        if (*num_pedidos >= *capacidade_pedidos) {
            *capacidade_pedidos *= 2;
            Pedido* temp = realloc(*pedidos, (*capacidade_pedidos) * sizeof(Pedido));
            if (temp == NULL) {
                printf(">> Erro ao redimensionar os pedidos.\n");
                exit(1);
            }
            *pedidos = temp;
        }

        Pedido novo_pedido;
        novo_pedido.cod_pedido = *num_pedidos + 1;
        strncpy(novo_pedido.nome_cliente, nome_cliente, sizeof(novo_pedido.nome_cliente) - 1);
        novo_pedido.num_itens = num_itens_pedido;
        novo_pedido.status = PENDENTE;
        novo_pedido.itens = malloc(num_itens_pedido * sizeof(item));

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
        (*pedidos)[*num_pedidos] = novo_pedido;
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

// Função para gerenciar os pedidos
void gerenciar_pedidos(Pedido* pedidos, int num_pedidos) {
    if (num_pedidos > 0) {
        printf("\n=========================================== Pedidos Realizados ============================================\n\n");
        for (int i = 0; i < num_pedidos; i++) {
            printf("\nPedido %d:\n", pedidos[i].cod_pedido);
            printf("Status: %s\n", (pedidos[i].status == PENDENTE) ? "Pendente" : (pedidos[i].status == EM_PREPARO) ? "Em preparo" : (pedidos[i].status == PRONTO) ? "Pronto" : "Entregue");
            printf("Cliente: %s\n", pedidos[i].nome_cliente);
            printf("Itens do Pedido:\n");
            float total = 0;
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

// Função para alterar o status do pedido
void alterar_status(Pedido* pedidos, int num_pedidos) {
    if (num_pedidos > 0) {
        printf("\n>> Preencha com as informações do pedido que deseja atualizar.\n");
        int cod_pedido;
        while(1) {
            printf("Número do pedido: ");
            if(scanf("%d", &cod_pedido) != 1 || cod_pedido <= 0 || cod_pedido > num_pedidos) {
                printf(">> Número inválido. Verifique se está correto e corresponde a um pedido cadastrado. Por favor, tente novamente.\n");
                while(getchar() != '\n');
            } else { break; }
        }
        cod_pedido--;
        int opcao;
        while(1) {
            printf("\nStatus:\n");
            printf("(1) Pendente\n(2) Em preparo\n(3) Pronto\n(4) Entregue\n");
            printf("<< Informe o status: ");
            if(scanf("%d", &opcao) != 1 || opcao < 1 || opcao > 4) {
                printf(">> Opção inválida. Por favor, tente novamente.\n");
                while(getchar() != '\n');
            } else { break; }
        }
        pedidos[cod_pedido].status = (StatusPedido)(opcao - 1);
        printf(">> Status do pedido %d alterado para: %s\n", cod_pedido + 1, (pedidos[cod_pedido].status == PENDENTE) ? "Pendente" : (pedidos[cod_pedido].status == EM_PREPARO) ? "Em preparo" : (pedidos[cod_pedido].status == PRONTO) ? "Pronto" : "Entregue");

        if (pedidos[cod_pedido].status == ENTREGUE) {
            printf(">> O pedido %d foi finalizado e entregue ao cliente.\n", cod_pedido + 1);
        }
    } else {
        printf(">> Não há pedidos cadastrados.\n\n");
    }
}

// Função para alterar um pedido existente
void alterar_pedido(Pedido* pedidos, int num_pedidos, item* cardapio, int codigo) {
    if(num_pedidos > 0 && codigo > 0) {
        printf("\n>> Preencha com as informações do pedido que deseja atualizar.\n");
        int cod_pedido;
        while(1) {
            printf("Número do pedido: ");
            if(scanf("%d", &cod_pedido) != 1 || cod_pedido <= 0 || cod_pedido > num_pedidos) {
                printf(">> Número inválido. Verifique se está correto e corresponde a um pedido cadastrado. Por favor, tente novamente.\n");
                while(getchar() != '\n');
            } else { break; }
        }
        cod_pedido--;
        Pedido *pedido = &pedidos[cod_pedido];
        printf("\n>> Alterando o pedido %d de %s:\n", pedido->cod_pedido, pedido->nome_cliente);
        int num_itens_pedido;
        printf("Quantidade de itens: ");
        while(1) {
            if(scanf("%d", &num_itens_pedido) != 1) {
                printf(">> Valor inválido. Por favor, tente novamente.\n");
                while(getchar() != '\n');
            } else { break; }
        }

        if (num_itens_pedido > 0) {
            pedido->num_itens = num_itens_pedido;
            for (int i = 0; i < num_itens_pedido; i++) {
                int codigo_item;
                while(1) {
                    printf("Código do item %d do pedido: ", i + 1);
                    if(scanf("%d", &codigo_item) != 1 || codigo_item <= 0 || codigo_item > codigo) {
                        printf(">> Código inválido. Verifique se está correto e corresponde a um item cadastrado. Por favor, tente novamente.\n");
                        while(getchar() != '\n');
                    } else { break; }
                }
                pedido->itens[i] = cardapio[codigo_item - 1];
            }
            printf(">> Pedido %d atualizado com sucesso.\n", pedido->cod_pedido);
        } else {
            printf(">> Número de itens inválido. Operação cancelada.\n");
        }
    } else if(num_pedidos <= 0) {
        printf(">> Não há pedidos cadastrados.\n");
    } else if(codigo <= 0) {
        printf(">> Não há itens cadastrados.\n");
    }
}

// Função para remover um pedido pelo código
void remover_pedido(Pedido* pedidos, int* num_pedidos) {
    if(*num_pedidos > 0) {
        printf("\n>> Preencha com as informações do pedido que deseja remover.\n");
        int cod_pedido;
        while(1) {
            printf("Número do pedido: ");
            if(scanf("%d", &cod_pedido) != 1 || cod_pedido <= 0 || cod_pedido > *num_pedidos) {
                printf(">> Número inválido. Verifique se está correto e corresponde a um pedido cadastrado. Por favor, tente novamente.\n");
                while(getchar() != '\n');
            } else { break; }
        }
        cod_pedido--;
        for (int i = cod_pedido; i < *num_pedidos - 1; i++) {
            pedidos[i] = pedidos[i + 1];
        }
        (*num_pedidos)--;
        printf(">> Pedido removido com sucesso.\n");
    } else {
        printf(">> Não há pedidos cadastrados.\n");
    }
}
