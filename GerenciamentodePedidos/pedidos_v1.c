#include <stdio.h>
#include <locale.h>
#include <stdlib.h>
#include <string.h>

#define max 10 // Total de itens no cardápio

// Enum de categorias do cardápio
typedef enum {entrada, principal, sobremesa, bebida} categoria;
char* categs[] = {"Entrada", "Principal", "Sobremesa", "Bebida"};

// Struct para representar um item do cardápio
typedef struct {
    char nome[20];
    char descri[50];
    float preco;
    categoria catego;
} item;

item cardapio[max]; // Armazenar itens do cardápio
int codigo = 0;     // Contador de itens no cardápio

// Enum para status dos pedidos
typedef enum {PENDENTE, EM_PREPARO, PRONTO, ENTREGUE} StatusPedido;

// Struct para representar um pedido
typedef struct {
    int id_pedido;           // Identificador único do pedido
    char nome_cliente[100];  // Nome do cliente
    item itens[max];         // Armazenar os itens do pedido
    int num_itens;           // Número de itens no pedido
    StatusPedido status;     // Status do pedido
} Pedido;

Pedido pedidos[max];  // Armazenar os pedidos
int num_pedidos = 0;  // Contador de pedidos

// Função para exibir o cardápio com alinhamento
void exibir_card() {
    if(codigo > 0) {
        printf("\n=================== Cardápio ============================================================\n");
        printf("%-10s %-20s %-40s %-15s %-10s\n", "Código", "Nome", "Descrição", "Preço R$", "Categoria");
        printf("============================================================================================\n");
        
        for(int i = 0; i < codigo; i++) {
            printf("%-10d %-20s %-40s %-15.2f %-10s\n", i + 1, cardapio[i].nome, cardapio[i].descri, cardapio[i].preco, categs[cardapio[i].catego]);
        }
        
        printf("============================================================================================\n\n");
    } else {
        printf("Nenhum item cadastrado ainda.\n\n");
    }
}

// Função para cadastrar itens no cardápio
void cadastro_card(item *p) { //cadastrar e atualizar itens do card
    getchar(); //limpar o buffer
    printf("Digite o nome do item: "); 
    fgets(p->nome, sizeof(p->nome), stdin);
    p->nome[strcspn(p->nome, "\n")] = 0; // Remover a quebra de linha

    printf("Digite a descrição [max.: 50 letras]: ");
    fgets(p->descri, sizeof(p->descri), stdin);
    p->descri[strcspn(p->descri, "\n")] = 0; // Remover a quebra de linha

    printf("Digite o preço em R$: ");
    scanf("%f", &p->preco);

    int n = 0;
    printf("Digite o número correspondente a categoria: \n");
    printf("(1) Entrada\n(2) Principal\n(3) Sobremesa\n(4) Bebida\n");
    while (n < 1 || n > 4) {
        scanf("%d", &n);
        if (n < 1 || n > 4) {
            printf("Número inválido, tente novamente.\n\n");
        }
    }
    n--;
    p->catego = (categoria)n;
}

// Função para remover itens do cardápio
void remover_card() {
    int num = 0;
    printf("Digite o código do item que deseja remover: ");
    scanf("%d", &num);
    num--;

    if(num >= 0 && num < codigo) {
        for(int i = num; i < codigo-1; i++) { // Remover item
            cardapio[i] = cardapio[i+1];
        }
        codigo--;
        printf("Item removido com sucesso!\n\n");
    }else {
        printf("Código inválido, tente novamente!\n\n");
    }
}

// Função para criar um novo pedido
void criar_pedido_menu() {
    int num_itens_pedido;
    char nome_cliente[100];
    
    // Recebe o nome do cliente
    printf("Digite o nome do cliente: ");
    getchar(); // Limpar o buffer
    fgets(nome_cliente, sizeof(nome_cliente), stdin);
    nome_cliente[strcspn(nome_cliente, "\n")] = 0; // Remover a quebra de linha

    // Perguntar quantos itens o pedido terá
    printf("Quantos itens o pedido terá? ");
    scanf("%d", &num_itens_pedido);

    if (num_itens_pedido > 0 && num_itens_pedido <= max) {
        Pedido novo_pedido;
        novo_pedido.id_pedido = num_pedidos + 1;
        strncpy(novo_pedido.nome_cliente, nome_cliente, sizeof(novo_pedido.nome_cliente) - 1);
        novo_pedido.num_itens = num_itens_pedido;
        novo_pedido.status = PENDENTE;  // Status inicial como PENDENTE

        // Receber os itens do pedido
        for (int i = 0; i < num_itens_pedido; i++) {
            int codigo_item;
            printf("Escolha o código do item %d do pedido: ", i + 1);
            scanf("%d", &codigo_item);
            
            if (codigo_item > 0 && codigo_item <= codigo) {
                novo_pedido.itens[i] = cardapio[codigo_item - 1]; // Adicionar item ao pedido
            } else {
                printf("Código inválido! Tente novamente.\n");
                i--; // Tentar novamente o mesmo item
            }
        }

        pedidos[num_pedidos] = novo_pedido;
        num_pedidos++;

        // Exibir o pedido
        printf("\nPedido %d criado com sucesso!\n", novo_pedido.id_pedido);
        printf("Cliente: %s\n", novo_pedido.nome_cliente);
        printf("Itens do Pedido:\n");
        for (int i = 0; i < novo_pedido.num_itens; i++) {
            printf("  %s - R$ %.2f\n", novo_pedido.itens[i].nome, novo_pedido.itens[i].preco);
        }
        printf("Status: Pendente\n\n");
    } else {
        printf("Número de itens inválido. Tente novamente.\n");
    }
}

// Função para exibir o status do pedido
const char* status_para_string(StatusPedido status) {
    switch (status) {
        case PENDENTE: return "Pendente";
        case EM_PREPARO: return "Em preparo";
        case PRONTO: return "Pronto";
        case ENTREGUE: return "Entregue";
        default: return "Desconhecido";
    }
}

// Função para gerenciar os pedidos (exibir todos os pedidos)
void gerenciar_pedidos() {
    if (num_pedidos > 0) {
        printf("\n===== Pedidos Realizados =====\n");
        for (int i = 0; i < num_pedidos; i++) {
            printf("\nPedido %d:\n", pedidos[i].id_pedido);
            printf("Status: %s\n", status_para_string(pedidos[i].status));
            printf("Cliente: %s\n", pedidos[i].nome_cliente);
            printf("Itens do Pedido:\n");
            float total = 0;
            for (int j = 0; j < pedidos[i].num_itens; j++) {
                printf("  %s - R$ %.2f\n", pedidos[i].itens[j].nome, pedidos[i].itens[j].preco);
                total += pedidos[i].itens[j].preco;
            }
            printf("Total: R$ %.2f\n", total);
            printf("\n===========================\n");
        }
    } else {
        printf("Não há pedidos para exibir.\n\n");
    }
}

// Função para alterar o status do pedido
void alterar_status() {
    int id_pedido;
    printf("Digite o código do pedido que deseja alterar o status: ");
    scanf("%d", &id_pedido);

    if (id_pedido > 0 && id_pedido <= num_pedidos) {
        int opcao;
        printf("\nEscolha o novo status:\n");
        printf("(1) Pendente\n(2) Em preparo\n(3) Pronto\n(4) Entregue\n");
        printf("Digite a opção: ");
        scanf("%d", &opcao);

        if (opcao >= 1 && opcao <= 4) {
            pedidos[id_pedido - 1].status = (StatusPedido)(opcao - 1);
            printf("Status do pedido %d alterado para: %s\n", id_pedido, status_para_string(pedidos[id_pedido - 1].status));
        } else {
            printf("Opção inválida!\n");
        }
    } else {
        printf("Pedido não encontrado!\n");
    }
}

int main() {
    setlocale(LC_ALL, "Portuguese");
    int opcion = 0;
    while (opcion != 8) {  // Alterei para 8 para incluir as novas opções
        printf("\n===== Gerenciamento do restaurante, o que deseja fazer? =====\n");
        printf("(1) Cadastrar cardápio\n(2) Exibir cardápio\n(3) Atualizar cardápio\n(4) Remover itens do cardápio\n(5) Criar pedido\n(6) Gerenciar pedidos\n(7) Alterar status de pedidos\n(8) Sair\n\n");
        scanf("%d", &opcion);

        switch (opcion) {
            case 1: // Cadastrar itens no cardápio
                if (codigo < max) {
                    printf("============= Cadastrar cardápio =============\n");
                    cadastro_card(&cardapio[codigo]);
                    codigo++;
                    printf("Item cadastrado com sucesso!\n");
                } else {
                    printf("Espaço insuficiente!\n");
                    break;
                }
                break;
            case 2: // Exibir o cardápio
                exibir_card();
                break;
            case 3: // Atualizar cardápio
                if (codigo > 0) {
                    int num;
                    printf("Digite o código do item que deseja atualizar: ");
                    scanf("%d", &num);
                    num--;
                    if(num >= 0 && num < codigo) {
                        printf("============= Atualizar cardápio =============\n");
                        cadastro_card(&cardapio[num]);
                        printf("Item atualizado com sucesso!\n");
                    } else {
                        printf("Código inválido, tente novamente!\n");
                    }
                } else {
                    printf("Nenhum item a ser atualizado!\n");
                }
                break;
            case 4: // Remover itens do cardápio
                exibir_card();
                remover_card();
                break;
            case 5: // Criar pedido
                criar_pedido_menu();
                break;
            case 6: // Gerenciar pedidos
                gerenciar_pedidos();
                break;
            case 7: // Alterar status de pedidos
                alterar_status();
                break;
            case 8: // Sair
                printf("Obrigado, volte sempre!\n");
                break;
            default:
                printf("Número inválido, tente novamente!\n");
                break;
        }
    }
    return 0;
}
