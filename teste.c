#include <stdio.h>
#include <locale.h>
#include <stdlib.h>
#include <string.h>

// Enum para status dos pedidos
typedef enum {PENDENTE, EM_PREPARO, PRONTO, ENTREGUE} StatusPedido;

// Enumeração de categorias do cardápio
typedef enum {entrada, principal, sobremesa, bebida} categoria;
const char* categs[] = {"Entrada", "Principal", "Sobremesa", "Bebida"};
const char* strings[] = {"Código", "Nome", "Descrição", "Preço R$", "Categoria"};

// Struct para representar um item do cardápio
typedef struct {
    char nome[100];
    char descri[100];
    float preco;
    categoria catego;
} item;

// Struct para representar um pedido
typedef struct {
    int cod_pedido;          // Identificador do pedido
    char nome_cliente[100];  // Nome do cliente
    item* itens;             // Armazenar os itens do pedido
    int num_itens;           // Número de itens no pedido
    StatusPedido status;     // Status do pedido
} Pedido;

// Variáveis globais
item* cardapio = NULL; // Armazenar itens do cardápio
int codigo = 0; // Contador de itens no cardápio
int capacidade_cardapio = 2; // Capacidade inicial

Pedido* pedidos = NULL; // Armazenar os pedidos
int num_pedidos = 0; // Contador de pedidos
int capacidade_pedidos = 2; // Capacidade inicial

// Função para exibir o cardápio
void exibir_card() {
    if(codigo > 0) {
        printf("\n================================================= Cardápio ================================================\n\n");
        printf("%-10s %-20s %-40s %-15s %-10s\n", strings[0], strings[1], strings[2], strings[3], strings[4]);
        printf("___________________________________________________________________________________________________________\n\n");
        for(int i = 0; i < codigo; i++) {
            printf("%-10d %-20s %-40s %-15.2f %-10s\n", i + 1, cardapio[i].nome, cardapio[i].descri, cardapio[i].preco, categs[cardapio[i].catego]);
        }
        printf("___________________________________________________________________________________________________________\n\n");
    } else {
        printf(">> Nenhum item cadastrado.\n\n");
    }
}

// Função para cadastrar itens no cardápio
void cadastro_card(item *p) {
    getchar(); // Limpar o buffer
    printf("Nome do item: "); 
    fgets(p->nome, sizeof(p->nome), stdin);
    p->nome[strcspn(p->nome, "\n")] = 0; // Remover a quebra de linha

    printf("Descrição [máx.: 100 caracteres]: ");
    fgets(p->descri, sizeof(p->descri), stdin);
    p->descri[strcspn(p->descri, "\n")] = 0; // Remover a quebra de linha

    while (1) {
        printf("Preço em R$: ");
        // Tenta ler o preço como um float
        if (scanf("%f", &p->preco) != 1) {
            // Se a leitura falhar, limpa o buffer e solicita novamente
            printf("Valor inválido. Por favor, insira um número válido.\n");
            while(getchar() != '\n');  // Limpar o buffer de entrada
        } else if (p->preco < 0) {
            printf("O preço não pode ser negativo. Tente novamente.\n");
        } else {break;}// Se o valor for válido e não negativo, sai do loop
    }

    printf("\nCategoria: \n");
    while(1) {
        printf("(1) Entrada\n(2) Principal\n(3) Sobremesa\n(4) Bebida\n");
        printf("Informe a opção: ");
        int n;
        if(scanf("%d", &n) != 1 || n < 1 || n > 4) {
            printf("Valor inválido. Por favor, insira um número válido.\n");
            while(getchar() != '\n');
        } else {
            p->catego = (categoria)(n - 1);
            break;
        }
    }
}

// Função para redimensionar o cardápio
void redimensionar_cardapio() {
    capacidade_cardapio *= 2;
    item* temp = realloc(cardapio, capacidade_cardapio * sizeof(item));
    if (temp == NULL) {
        printf("Erro ao redimensionar o cardápio.\n");
        exit(1); // Sair do programa em caso de erro
    }
    cardapio = temp;
}

// Função para remover itens do cardápio
void remover_card() {
    if(codigo > 0) {
        printf("\n>> Preencha com as informações do item que deseja remover.\n");
        int num;
        while(1) {
            printf("Código do item: ");
            if(scanf("%d", &num) != 1 || num < 1 || num > codigo) {
                printf("Código inválido, tente novamente.\n");
                while(getchar() != '\n');
            } else {
                break;
            }
        }
        num--; // Ajustar para índice
        for(int i = num; i < codigo - 1; i++) { // Remover item
            cardapio[i] = cardapio[i + 1];
        }
        codigo--;
        printf(">> Item removido com sucesso.\n\n");
    } else {
        printf(">> Não há itens cadastrados.\n\n");
    }
}

// Função para criar um novo pedido
void criar_pedido_menu() {
    if (codigo > 0) {
        char nome_cliente[100];
        printf("Nome do cliente: ");
        getchar(); // Limpar o buffer
        fgets(nome_cliente, sizeof(nome_cliente), stdin);
        nome_cliente[strcspn(nome_cliente, "\n")] = 0; // Remover a quebra de linha

        int num_itens_pedido;
        while(1) {
            printf("Quantidade de itens: ");
            if(scanf("%d", &num_itens_pedido) != 1 || num_itens_pedido <= 0 || num_itens_pedido > codigo) {
                printf("Valor inválido. Por favor, insira um número válido entre 1 e %d.\n", codigo);
                while(getchar() != '\n');
            } else {
                break;
            }
        }

        if (num_pedidos >= capacidade_pedidos) {
            capacidade_pedidos *= 2;
            Pedido* temp = realloc(pedidos, capacidade_pedidos * sizeof(Pedido));
            if (temp == NULL) {
                printf("Erro ao redimensionar os pedidos.\n");
                exit(1); // Sair do programa em caso de erro
            }
            pedidos = temp;
        }

        Pedido novo_pedido;
        novo_pedido.cod_pedido = num_pedidos + 1;
        strncpy(novo_pedido.nome_cliente, nome_cliente, sizeof(novo_pedido.nome_cliente) - 1);
        novo_pedido.num_itens = num_itens_pedido;
        novo_pedido.status = PENDENTE;  // Status inicial
        novo_pedido.itens = malloc(num_itens_pedido * sizeof(item)); // Alocar memória para os itens do pedido

        for (int i = 0; i < num_itens_pedido; i++) {
            int codigo_item;
            while(1) {
                printf("Código do item %d do pedido: ", i + 1);
                if(scanf("%d", &codigo_item) != 1 || codigo_item < 1 || codigo_item > codigo) {
                    printf(">> Código inválido, tente novamente.\n");
                    while(getchar() != '\n');
                } else {
                    novo_pedido.itens[i] = cardapio[codigo_item - 1];    
                    break;
                }
            }
        }

        pedidos[num_pedidos] = novo_pedido;
        num_pedidos++;
        printf("\n>> Pedido %d criado com sucesso.\n", novo_pedido.cod_pedido);
        printf("Nome do cliente: %s\n", novo_pedido.nome_cliente);
        printf("Itens do Pedido:\n");
        for (int i = 0; i < novo_pedido.num_itens; i++) {
            printf("  %s - R$ %.2f\n", novo_pedido.itens[i].nome, novo_pedido.itens[i].preco);
        }
        printf("Status: Pendente\n\n");
    } else {
        printf(">> Não há pedidos a oferecer ao cliente, por favor cadastre algum item antes.\n");
    }
}

// Função para exibir o status do pedido
const char* status_para_string(StatusPedido status) {
    switch (status) {
        case PENDENTE: return "Pendente";
        case EM_PREPARO: return "Em preparo";
        case PRONTO: return "Pronto";
        case ENTREGUE: return "Entregue";
        default: return "Sem informação";
    }
}

// Função para gerenciar os pedidos (exibir todos os pedidos)
void gerenciar_pedidos() {
    if (num_pedidos > 0) {
        printf("\n=========================================== Pedidos Realizados ============================================\n\n");
        float * total = (float *)malloc(sizeof(float));
        for (int i = 0; i < num_pedidos; i++) {
            printf("\nPedido %d:\n", pedidos[i].cod_pedido);
            printf("Status: %s\n", status_para_string(pedidos[i].status));
            printf("Cliente: %s\n", pedidos[i].nome_cliente);
            printf("Itens do Pedido:\n");
            //float total = 0;
            total = (float *)malloc(sizeof(float));
            for (int j = 0; j < pedidos[i].num_itens; j++) {
                printf("-> %s - R$ %.2f\n", pedidos[i].itens[j].nome, pedidos[i].itens[j].preco);
                *total += pedidos[i].itens[j].preco;
            }
            printf("Total: R$ %.2f\n", *total);
            *total = 0; //resetar total
            free(total);
            printf("\n===========================================================================================================\n\n");
        }
        free(total);
    } else {
        printf(">> Não há pedidos para exibir.\n\n");
    }
}

// Função para alterar o status do pedido
void alterar_status() {
    if(num_pedidos > 0) {
        printf("\n>> Preencha com as informações do pedido que deseja atualizar.\n");
        int cod_pedido;
        while(1) {
            printf("Código do pedido: ");
            if(scanf("%d", &cod_pedido) != 1 || cod_pedido <= 0 || cod_pedido > num_pedidos) {
                printf("Código inválido, tente novamente!\n");
                while(getchar() != '\n');
            } else {
                break;
            }
        }

        int opcao;
        while(1) {
            printf("\nStatus:\n");
            printf("(1) Pendente\n(2) Em preparo\n(3) Pronto\n(4) Entregue\n");
            printf("Informe o status: ");
            if(scanf("%d", &opcao) != 1 || opcao < 1 || opcao > 4) {
                printf(">> Valor inválido. Por favor, insira um número válido entre 1 e 4.\n");
                while(getchar() != '\n');
            } else {
                break;
            }
        }

        pedidos[cod_pedido - 1].status = (StatusPedido)(opcao - 1);
        printf("Status do pedido %d alterado para: %s\n", cod_pedido, status_para_string(pedidos[cod_pedido - 1].status));
    } else {
        printf(">> Nenhum pedido cadastrado no momento.\n\n");
    }
}

// Função para alterar um pedido existente
void alterar_pedido() {
    if(num_pedidos > 0) {
        printf("\n>> Preencha com as informações do pedido que deseja atualizar.\n");
        int cod_pedido;
        while(1) {
            printf("Código do pedido: ");
            if(scanf("%d", &cod_pedido) != 1 || cod_pedido <= 0 || cod_pedido > num_pedidos) {
                printf("Código inválido, tente novamente.\n");
                while(getchar() != '\n');
            } else {
                break;
            }
        }

        Pedido *pedido = &pedidos[cod_pedido - 1];
        printf("\nAlterando o pedido %d de %s:\n", pedido->cod_pedido, pedido->nome_cliente);
        int num_itens_pedido;
        printf("Quantidade de itens: ");
        scanf("%d", &num_itens_pedido);

        if (num_itens_pedido > 0 && num_itens_pedido <= codigo) {
            free(pedido->itens); // Liberar memória anterior
            pedido->itens = malloc(num_itens_pedido * sizeof(item)); // Alocar nova memória para os itens
            pedido->num_itens = num_itens_pedido;
            for (int i = 0; i < num_itens_pedido; i++) {
                int codigo_item;
                while(1) {
                    printf("Código do item %d do pedido: ", i + 1);
                    if(scanf("%d", &codigo_item) != 1 || codigo_item <= 0 || codigo_item > codigo) {
                        printf(">> Código inválido, tente novamente.\n");
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
        printf(">> Nenhum pedido cadastrado no momento.\n");
    }
}

// Função para remover um pedido pelo código
void remover_pedido() {
    if(num_pedidos > 0) {
        printf("\n>> Preencha com as informações do pedido que deseja remover.\n");
        int cod_pedido;
        while(1) {
            printf("Código do pedido: ");
            if(scanf("%d", &cod_pedido) != 1 || cod_pedido <= 0 || cod_pedido > num_pedidos) {
                printf("Pedido não encontrado. \n");
                while(getchar() != '\n');
            } else {
                break;
            }
        }

        free(pedidos[cod_pedido - 1].itens); // Liberar memória dos itens do pedido
        for (int i = cod_pedido - 1; i < num_pedidos - 1; i++) {
            pedidos[i] = pedidos[i + 1];
        }
        num_pedidos--;
        printf("Pedido removido com sucesso.\n");
    } else {
        printf("Nenhum pedido cadastrado no momento.\n");
    }
}

int main() {
    setlocale(LC_ALL, "Portuguese");

    // Alocar memória inicial
    cardapio = malloc(capacidade_cardapio * sizeof(item));
    if (cardapio == NULL) {
        printf("Erro ao alocar memória para o cardápio.\n");
        return 1; // Sair do programa em caso de erro
    }

    pedidos = malloc(capacidade_pedidos * sizeof(Pedido));
    if (pedidos == NULL) {
        printf("Erro ao alocar memória para os pedidos.\n");
        free(cardapio); // Liberar memória do cardápio antes de sair
        return 1; // Sair do programa em caso de erro
    }

    int opcao;
    while (1) {
        printf("\n=========================================== Gerenciamento do Restaurante ===================================\n\n");
        printf("(1) Cadastrar item \n(2) Exibir cardápio\n(3) Atualizar cardápio\n(4) Remover itens do cardápio\n");
        printf("(5) Criar pedido\n(6) Gerenciar pedidos\n(7) Alterar status de pedidos\n(8) Alterar pedido\n(9) Remover pedido\n(10) Sair\n\n");
        
        while(1) {
            printf("<< Informe a opção: ");
            if(scanf("%d", &opcao) != 1) {
                printf("Valor inválido. Por favor, insira um número válido.\n");
                while(getchar() != '\n');
            } else {
                break;
            }
        }

        switch (opcao) {
            case 1: // Cadastrar itens no cardápio
                if (codigo >= capacidade_cardapio) {
                    redimensionar_cardapio();
                }
                printf("\n============================================== Cadastrar Item ==============================================\n\n");
                cadastro_card(&cardapio[codigo]);
                codigo++;
                printf(">> Item cadastrado com sucesso.\n");
                break;
            case 2:
                exibir_card();
                break;
            case 3:
                if (codigo > 0) {
                    int num;
                    printf("\n>> Preencha com as informações do item que deseja atualizar.\n");
                    while(1) {
                        printf("Código do item: ");
                        if(scanf("%d", &num) != 1 || num < 1 || num > codigo) {
                            printf(">> Código inválido, tente novamente.\n");    
                            while(getchar() != '\n');
                        } else {
                            break;
                        }
                    }
                    num--; // Ajustar para índice
                    printf("\n============================================= Atualizar Cardápio ============================================\n\n");
                    cadastro_card(&cardapio[num]);
                    printf(">> Item atualizado com sucesso.\n");
                } else {
                    printf(">> Nenhum item cadastrado no momento.\n");
                }
                break;
            case 4:
                remover_card();
                break;
            case 5:
                criar_pedido_menu();
                break;
            case 6:
                gerenciar_pedidos();
                break;
            case 7:
                alterar_status();
                break;
            case 8:
                alterar_pedido();
                break;
            case 9:
                remover_pedido();
                break;
            case 10:
                // Liberar memória antes de sair
                for (int i = 0; i < num_pedidos; i++) {
                    free(pedidos[i].itens);
                }
                free(cardapio);
                free(pedidos);
                printf(">> Obrigado, volte sempre!\n");
                return 0;
            default:
                printf(">> Número inválido, tente novamente.\n");
                break;
        }
    }
    return 0;
}
