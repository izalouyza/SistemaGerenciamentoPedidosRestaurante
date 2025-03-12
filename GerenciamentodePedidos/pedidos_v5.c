#include <stdio.h>
#include <locale.h>
#include <stdlib.h>
#include <string.h>

// Total de itens no cardápio
#define max 10 

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

item cardapio[max]; // Armazenar itens do cardápio
int codigo = 0;     // Contador de itens no cardápio

// Enum para status dos pedidos
typedef enum {PENDENTE, EM_PREPARO, PRONTO, ENTREGUE} StatusPedido;

// Struct para representar um pedido
typedef struct {
    int cod_pedido;          // Identificador do pedido
    char nome_cliente[100];  // Nome do cliente
    item itens[max];         // Armazenar os itens do pedido
    int num_itens;           // Número de itens no pedido
    StatusPedido status;     // Status do pedido
} Pedido;

Pedido pedidos[max];  // Armazenar os pedidos
int num_pedidos = 0;  // Contador de pedidos

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
void cadastro_card(item *p) { // Cadastrar e atualizar itens do cardápio
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
            break; // Se o valor for válido e não negativo, sai do loop
        }
    }
    
    int n = 0;
    printf("\nCategoria: \n");
    while(1){
        printf("(1) Entrada\n(2) Principal\n(3) Sobremesa\n(4) Bebida\n");
        printf("Informe a opção: ");
        if(scanf("%d", &n) != 1){
            printf("Valor inválido. Por favor, insira um número válido.\n");
            while(getchar() != '\n');
        } else if (n < 1 || n > 4) {
            printf(">> Opção inválida, tente novamente.\n\n");
        }else{
            n--;
            p->catego = (categoria)n;
            break;
        }
    }
}

// Função para remover itens do cardápio
void remover_card() {
    if(codigo > 0){
        int num = 0;
        printf("\n>> Preencha com as informações do item que deseja remover.\n");

        while(1){
            printf("Código do item: ");
            if(scanf("%d", &num) != 1){
                printf("Valor inválido. Por favor, insira um número válido.\n");
                while(getchar() != '\n');
            }else if(num >= 0 && num <= codigo){
                break;
            }
        }
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
        while(1){
            printf("Quantidade de itens: ");
            if(scanf("%d", &num_itens_pedido) != 1 || num_itens_pedido <= 0){
                printf("Valor inválido. Por favor, insira um número válido.\n");
                while(getchar() != '\n');
            }else{
                break;
            }
        }
    
        if (num_itens_pedido > 0 && num_itens_pedido <= max) {
            Pedido novo_pedido;
            novo_pedido.cod_pedido = num_pedidos + 1;
            strncpy(novo_pedido.nome_cliente, nome_cliente, sizeof(novo_pedido.nome_cliente) - 1);
            novo_pedido.num_itens = num_itens_pedido;
            novo_pedido.status = PENDENTE;  // Status inicial como PENDENTE
    
            // Receber os itens do pedido
            for (int i = 0; i < num_itens_pedido; i++) {
                int codigo_item;
                while(1){
                    printf("Código do item %d do pedido: ", i + 1);
                    if(scanf("%d", &codigo_item) != 1){
                        printf(">> Valor inválido. Por favor, insira um número válido.\n");
                        while(getchar() != '\n');
                    }else if((codigo_item > 0 && codigo_item <= codigo)){
                        novo_pedido.itens[i] = cardapio[codigo_item - 1];    
                        break;
                    }else{
                        printf(">> Código inválido, tente novamente.\n");
                    }
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
        for (int i = 0; i < num_pedidos; i++) {
            printf("\nPedido %d:\n", pedidos[i].cod_pedido);
            printf("Status: %s\n", status_para_string(pedidos[i].status));
            printf("Cliente: %s\n", pedidos[i].nome_cliente);
            printf("Itens do Pedido:\n");
            float total = 0;
            for (int j = 0; j < pedidos[i].num_itens; j++) {
                printf("  %s - R$ %.2f\n", pedidos[i].itens[j].nome, pedidos[i].itens[j].preco);
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
void alterar_status() {
    if(num_pedidos > 0){
    	printf("\n>> Preencha com as informações do pedido que deseja atualizar.\n");
        int cod_pedido;
        
        while(1){
            printf("Código do pedido: ");
            if(scanf("%d", &cod_pedido) != 1){
                printf("Valor inválido. Por favor, insira um número válido.\n");
                while(getchar() != '\n');
            }else if(cod_pedido < 0 || cod_pedido > num_pedidos){
                printf("Código inválido, tente novamente!\n");
            }else{
                break;
            }
        }
    
        if (cod_pedido > 0 && cod_pedido <= num_pedidos) {
            int opcao;
            while(1){
                printf("\nStatus:\n");
                printf("(1) Pendente\n(2) Em preparo\n(3) Pronto\n(4) Entregue\n");
                printf("Informe o status: ");
                if(scanf("%d", &opcao) != 1){
                    printf(">> Valor inválido. Por favor, insira um número válido.\n");
                    while(getchar() != '\n');
                }else if(opcao < 1 || opcao > 4){
                    printf(">> Opção inválida, tente novamente");
                }else{
                    break;
                }
            }
            pedidos[cod_pedido - 1].status = (StatusPedido)(opcao - 1);
            printf("Status do pedido %d alterado para: %s\n", cod_pedido, status_para_string(pedidos[cod_pedido - 1].status));
        } else {
            printf(">> Pedido não encontrado, tente novamente.\n");
        }
    }else{
        printf(">> Nenhum pedido cadastrado no momento.\n\n");
    }
}

// Função para alterar um pedido existente
void alterar_pedido() {
    if(num_pedidos > 0){
    	printf("\n>> Preencha com as informações do pedido que deseja atualizar.\n");
        int cod_pedido;
        while(1){
            printf("Código do pedido: ");
            if(scanf("%d", &cod_pedido) != 1){
                printf("Valor inválido. Por favor, insira um número válido.\n");
                while(getchar() != '\n');
            }else if(cod_pedido <= 0 || cod_pedido > num_pedidos){
                printf(">> Número de itens inválido. Operação cancelada.\n");
            }else{
                break;
            }
        }
    
        if (cod_pedido > 0 && cod_pedido <= num_pedidos) {
            Pedido *pedido = &pedidos[cod_pedido - 1];
            printf("\nAlterando o pedido %d de %s:\n", pedido->cod_pedido, pedido->nome_cliente);
    
            // Pergunta quantos itens deseja no pedido atualizado
            int num_itens_pedido;
            printf("Quantidade de itens: ");
            scanf("%d", &num_itens_pedido);
    
            if (num_itens_pedido > 0 && num_itens_pedido <= max){
                pedido->num_itens = num_itens_pedido;
    
                // Receber os novos itens do pedido
                for (int i = 0; i < num_itens_pedido; i++) {
                    int codigo_item;
                    while(1){
                        printf("Código do item %d do pedido: ", i + 1);
                        if(scanf("%d", &codigo_item) != 1){
                            printf("Valor inválido. Por favor, insira um número válido.\n");
                            while(getchar() != '\n');
                        }else if(codigo_item <= 0 || codigo_item > codigo){
                            printf(">> Código inválido, tente novamente");
                        }else{
                            break;
                        }

                    }
    
                    if (codigo_item > 0 && codigo_item <= codigo) {
                        pedido->itens[i] = cardapio[codigo_item - 1]; // Atualizar item do pedido
                    } else {
                        printf(">> Código inválido, tente novamente.\n");
                        i--; // Tentar novamente o mesmo item
                    }
                }
    
                printf(">> Pedido %d atualizado com sucesso.\n", pedido->cod_pedido);
            } else {
                printf(">> Número de itens inválido. Operação cancelada.\n");
            }
        } else {
            printf(">> Pedido não encontrado.\n");
        }
    }else{
        printf(">> Nenhum pedido cadastrado no momento.\n");
    }
}

// Função para remover um pedido pelo código
void remover_pedido() {
    if(num_pedidos > 0){
    	printf("\n>> Preencha com as informações do pedido que deseja remover.\n");
        int cod_pedido;

        while(1){
            printf("Código do pedido: ");
            if(scanf("%d", &cod_pedido) != 1){
                printf("Valor inválido. Por favor, insira um número válido.\n");
                while(getchar() != '\n');
            }else if(cod_pedido <= 0 || cod_pedido > num_pedidos){
                printf("Pedido não encontrado. \n");
            }else{
                break;
            }
        }
    
        if (cod_pedido > 0 && cod_pedido <= num_pedidos) {
            // Remover pedido e reorganizar lista
            for (int i = cod_pedido - 1; i < num_pedidos - 1; i++) {
                pedidos[i] = pedidos[i + 1];
            }
            num_pedidos--;
            printf("Pedido removido com sucesso.\n");
        } else {
            printf("Pedido não encontrado.\n");
        }
    }else{
        printf("Nenhum pedido cadastrado no momento.\n");
    }
}

int main() {
    setlocale(LC_ALL, "Portuguese");
    int opcion = 0;
    int opc = 0;
    while (1) {  // Altera para 10 para incluir as novas opções
        printf("\n=========================================== Gerenciamento do Restaurante ===================================\n\n");
        printf("(1) Cadastrar item \n(2) Exibir cardápio\n(3) Atualizar cardápio\n(4) Remover itens do cardápio\n");
        printf("(5) Criar pedido\n(6) Gerenciar pedidos\n(7) Alterar status de pedidos\n(8) Alterar pedido\n(9) Remover pedido\n(10) Sair\n\n");
        while(1){
            printf("<< Informe a opção: ");
            if(scanf("%d", &opcion) != 1){
                printf("Valor inválido. Por favor, insira um número válido.\n");
                while(getchar() != '\n');
            }else{
                break;
            }
        }
    switch (opcion) {
        case 1: // Cadastrar itens no cardápio
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
                while(1){
                    printf("Código do item: ");
                    if(scanf("%d", &num) != 1){
                        printf("Valor inválido. Por favor, insira um número válido.\n");
                        while(getchar() != '\n');
                    }else if(num < 0 || num > codigo){
                        printf(">> Código inválido, tente novamente.\n");    
                    }else{break;}
                }
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
            while(1){
                printf(">> Tem certeza que deseja sair?\n[1] Sim\n[0] Não\n");
                if(scanf("%d", &opc) != 1){
                    printf("Valor inválido. Por favor, insira um número válido.\n");
                    while(getchar() != '\n');    
                }else if(opc < 0 || opc > 1){
                    printf("Opção inválida, tente novamente.\n");
                }else{
                    break;
                }
            }
            if(opc == 1){
                printf(">> Obrigado, volte sempre!\n");
                return 0;
            }
            break;
        default:
            printf(">> Número inválido, tente novamente.\n");
            break;
        }
    }
    return 0;
}
