#include <stdio.h>
#include <locale.h>
#include <stdlib.h>
#include <string.h>

// Enumeração de categorias do cardápio
typedef enum {entrada, principal, sobremesa, bebida} categoria;
char* categs[] = {"Entrada", "Principal", "Sobremesa", "Bebida"};

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
    item *itens;             // Armazenar os itens do pedido dinamicamente
    int num_itens;           // Número de itens no pedido
    StatusPedido status;     // Status do pedido
} Pedido;

// Enum para status dos pedidos
typedef enum {PENDENTE, EM_PREPARO, PRONTO, ENTREGUE} StatusPedido;

int codigo = 0;  // Contador de itens no cardápio
int num_pedidos = 0;  // Contador de pedidos
item *cardapio = NULL; // Inicializando o ponteiro de cardápio dinamicamente
Pedido *pedidos = NULL; // Inicializando o ponteiro de pedidos dinamicamente

// Função para alocar espaço para o cardápio
void inicializar_cardapio(int max) {
    cardapio = (item *)malloc(max * sizeof(item));
    if (cardapio == NULL) {
        printf("Erro ao alocar memória para o cardápio.\n");
        exit(1);  // Finaliza o programa se não conseguir alocar
    }
}

// Função para alocar espaço para os pedidos
void inicializar_pedidos(int max) {
    pedidos = (Pedido *)malloc(max * sizeof(Pedido));
    if (pedidos == NULL) {
        printf("Erro ao alocar memória para os pedidos.\n");
        exit(1);  // Finaliza o programa se não conseguir alocar
    }
}

// Função para exibir o cardápio
void exibir_card() {
    if(codigo > 0) {
        printf("\n================================================= Cardápio ================================================\n\n");
        printf("%-10s %-20s %-40s %-15s %-10s\n", "Código", "Nome", "Descrição", "Preço R$", "Categoria");
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

    while (1) {  // Repetição até um preço válido ser inserido
        printf("Preço em R$: ");
        
        // Tenta ler o preço como um float
        if (scanf("%f", &p->preco) != 1) {
            // Se a leitura falhar, limpa o buffer e solicita novamente
            printf("Valor inválido. Por favor, insira um número válido.\n");
            while(getchar() != '\n');  // Limpar o buffer de entrada
        } else if (p->preco < 0) {
            printf("O preço não pode ser negativo. Tente novamente.\n");
        } else {
            // Se o valor for válido e não negativo, sai do loop
            break;
        }
    }
    
    int n = 0;
    printf("\nCategoria: \n");
    printf("(1) Entrada\n(2) Principal\n(3) Sobremesa\n(4) Bebida\n");
    while (n < 1 || n > 4) {
        printf("Informe a opção: ");
        scanf("%d", &n);
        if (n < 1 || n > 4) {
            printf(">> Opção inválida, tente novamente.\n\n");
        }
    }
    n--;
    p->catego = (categoria)n;
}

// Função para remover um item do cardápio
void remover_card() {
    if(codigo > 0){
        int num = 0;
        printf("\n>> Preencha com as informações do item que deseja remover.\n");
        printf("Código do item: ");
        scanf("%d", &num);
        num--;
    
        if(num >= 0 && num < codigo) {
            for(int i = num; i < codigo-1; i++) { // Remover item
                cardapio[i] = cardapio[i+1];
            }
            codigo--;
            printf(">> Item removido com sucesso.\n\n");
        }else {
            printf(">> Código inválido, tente novamente.\n\n");
        }
    }else{
        printf(">> Não há itens cadastrados.\n\n");
    }
}

// Função para criar um novo pedido
void criar_pedido_menu() {
    if (codigo > 0){ // Se tiver itens cadastrados
        int num_itens_pedido;
        char nome_cliente[100];
        
        // Recebe o nome do cliente
        printf("Nome do cliente: ");
        getchar(); // Limpar o buffer
        fgets(nome_cliente, sizeof(nome_cliente), stdin);
        nome_cliente[strcspn(nome_cliente, "\n")] = 0; // Remover a quebra de linha
    
        // Perguntar quantos itens o pedido terá
        printf("Quantidade de itens: ");
        scanf("%d", &num_itens_pedido);
    
        if (num_itens_pedido > 0 && num_itens_pedido <= max) {
            Pedido novo_pedido;
            novo_pedido.cod_pedido = num_pedidos + 1;
            strncpy(novo_pedido.nome_cliente, nome_cliente, sizeof(novo_pedido.nome_cliente) - 1);
            novo_pedido.num_itens = num_itens_pedido;
            novo_pedido.status = PENDENTE;  // Status inicial como PENDENTE
            
            // Alocar memória dinamicamente para os itens do pedido
            novo_pedido.itens = (item *)malloc(num_itens_pedido * sizeof(item));
            if (novo_pedido.itens == NULL) {
                printf("Erro ao alocar memória para os itens do pedido.\n");
                exit(1);  // Finaliza o programa se não conseguir alocar
            }

            // Receber os itens do pedido
            for (int i = 0; i < num_itens_pedido; i++) {
                int codigo_item;
                printf("Código do item %d do pedido: ", i + 1);
                scanf("%d", &codigo_item);
                
                if (codigo_item > 0 && codigo_item <= codigo) {
                    novo_pedido.itens[i] = cardapio[codigo_item - 1]; // Adicionar item ao pedido
                } else {
                    printf(">> Código inválido, tente novamente.\n");
                    i--; // Tentar novamente o mesmo item
                }
            }
    
            pedidos[num_pedidos] = novo_pedido;
            num_pedidos++;
    
            // Exibir o pedido
            printf("\n>> Pedido %d criado com sucesso.\n", novo_pedido.cod_pedido);
            printf("Nome do cliente: %s\n", novo_pedido.nome_cliente);
            printf("Itens do Pedido:\n");
            for (int i = 0; i < novo_pedido.num_itens; i++) {
                printf("  %s - R$ %.2f\n", novo_pedido.itens[i].nome, novo_pedido.itens[i].preco);
            }
            printf("Status: Pendente\n\n");
        } else {
            printf(">> Número de itens inválido. Tente novamente.\n");
        }
    }else{
        printf(">> Não há pedidos a oferecer ao cliente, por favor cadastre algum item antes.\n");
    }
}

// Função para liberar a memória alocada para os pedidos
void liberar_pedidos() {
    for (int i = 0; i < num_pedidos; i++) {
        free(pedidos[i].itens);  // Libera a memória de cada item de pedido
    }
    free(pedidos);  // Libera a memória dos pedidos
    pedidos = NULL;  // Evita acesso inválido após a liberação
}

// Função principal
int main() {
    setlocale(LC_ALL, "Portuguese");

    int max = 10;  // Tamanho máximo do cardápio e pedidos
    
    // Inicializa o cardápio e pedidos
    inicializar_cardapio(max);
    inicializar_pedidos(max);
    
    int opcion = 0;
    while (opcion != 10) {
        printf("\n=========================================== Gerenciamento do Restaurante ===================================\n\n");
        printf("(1) Cadastrar item \n(2) Exibir cardápio\n(3) Atualizar cardápio\n(4) Remover itens do cardápio\n");
        printf("(5) Criar pedido\n(6) Gerenciar pedidos\n(7) Alterar status de pedidos\n(8) Alterar pedido\n(9) Remover pedido\n(10) Sair\n\n");
        printf("<< Informe a opção: ");
        scanf("%d", &opcion);

        switch (opcion) {
            case 1:
                if (codigo < max) {
                    printf("\n============================================== Cadastrar Item ==============================================\n\n");
                    cadastro_card(&cardapio[codigo]);
                    codigo++;
                    printf(">> Item cadastrado com sucesso.\n");
                } else {
                    printf(">> Espaço insuficiente.\n");
                }
                break;
            case 2:
                exibir_card();
                break;
            case 3:
                if (codigo > 0) {
                    int num;
                    printf("\n>> Preencha com as informações do item que deseja atualizar.\n");
                    printf("Código do item: ");
                    scanf("%d", &num);
                    num--;
                    if(num >= 0 && num < codigo) {
                        printf("\n============================================= Atualizar Cardápio ============================================\n\n");
                        cadastro_card(&cardapio[num]);
                        printf(">> Item atualizado com sucesso.\n");
                    } else {
                        printf(">> Código inválido, tente novamente.\n");
                    }
                } else {
                    printf(">> Nenhum item cadastrado no momento.\n");
                }
                break;
            case 4:
                if(codigo > 0){
                    exibir_card();
                }
                remover_card();
                break;
            case 5:
                criar_pedido_menu();
                break;
            case 6:
                // Exibir os pedidos
                break;
            case 7:
                // Alterar status do pedido
                break;
            case 8:
                // Alterar pedido
                break;
            case 9:
                // Remover pedido
                break;
            case 10:
                // Liberar memória
                liberar_pedidos();
                free(cardapio);  // Liberar memória do cardápio
                printf(">> Obrigado, volte sempre!\n");
                break;
            default:
                printf(">> Número inválido, tente novamente.\n");
                break;
        }
    }

    return 0;
}
