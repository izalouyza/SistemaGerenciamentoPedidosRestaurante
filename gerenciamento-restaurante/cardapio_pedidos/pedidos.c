#include "pedidos.h"

// Variáveis globais para os pedidos
Pedido* pedidos = NULL;
int capacidade_pedidos = 2; // Capacidade inicial para pedidos
int num_pedidos = 0; // Contador de pedidos
item* cardapio = NULL; // Armazenar itens do cardápio
int codigo = 0; // Contador de itens no cardápio
int capacidade_cardapio = 2; // Capacidade inicial do cardápio

// Função para criar um novo pedido
void criar_pedido_menu() {
    printf("Número de itens no cardápio: %d\n", codigo); // Debugging
    if (codigo > 0) { // verificar se há itens a oferecer ao cliente
        char nome_cliente[100];
        printf("Nome do cliente: "); // solicita o nome do cliente
        getchar(); // Limpar o buffer
        fgets(nome_cliente, sizeof(nome_cliente), stdin); // recebe o nome do cliente
        nome_cliente[strcspn(nome_cliente, "\n")] = 0; // Remover a quebra de linha

        int num_itens_pedido; // determina quantos itens o cliente gostaria de consumir
        while(1) { // Repetição até um valor válido ser inserido
            printf("Quantidade de itens: "); // solicita a quantidade de itens
            if(scanf("%d", &num_itens_pedido) != 1 || num_itens_pedido <= 0) { // garante que o valor inserido seja válido
                printf(">> Quantidade inválida. A quantidade de itens não pode ser negativa ou incluir letras e caracteres especiais. Por favor, tente novamente.\n");
                while(getchar() != '\n'); // limpa o buffer de entrada
            } else {break;} // se o valor for válido, sai do loop
        }
        
        // Verifica se é necessário redimensionar a lista de pedidos
        if (num_pedidos >= capacidade_pedidos) { 
            capacidade_pedidos *= 2; // Dobra a capacidade dos pedidos
            Pedido* temp = realloc(pedidos, capacidade_pedidos * sizeof(Pedido)); // Tenta realocar a memória
            if (temp == NULL) {
                printf(">> Erro ao redimensionar os pedidos.\n");
                exit(1); // Sair do programa em caso de erro
            }
            pedidos = temp; // Atualiza o ponteiro dos pedidos
        }
        
        Pedido novo_pedido; // Cria um novo pedido
        novo_pedido.cod_pedido = num_pedidos + 1; // Atribui um código ao pedido
        strncpy(novo_pedido.nome_cliente, nome_cliente, sizeof(novo_pedido.nome_cliente) - 1); // Copia o nome do cliente
        novo_pedido.num_itens = num_itens_pedido; // Define o número de itens no pedido
        novo_pedido.status = pendente;  // Status inicial do pedido
        novo_pedido.itens = malloc(num_itens_pedido * sizeof(item)); // Alocar memória para os itens do pedido

        // Loop para receber os itens do pedido
        for (int i = 0; i < num_itens_pedido; i++) {
            int codigo_item;
            while(1) { // Repetição até um valor válido ser inserido
                printf("Código do item %d: ", i + 1); // solicita o código do item
                if(scanf("%d", &codigo_item) != 1 || codigo_item < 1 || codigo_item > codigo) { // garante que o valor inserido seja válido
                    printf(">> Código inválido. Verifique se está correto e corresponde a um item cadastrado. Por favor, tente novamente.\n");
                    while(getchar() != '\n'); // limpa o buffer de entrada
                } else {
                    novo_pedido.itens[i] = cardapio[codigo_item - 1];  // Adiciona o item ao pedido
                    break; // Sai do loop se o código for válido
                }
            }
        }
        
        pedidos[num_pedidos] = novo_pedido; // Adiciona o novo pedido à lista de pedidos
        num_pedidos++; // Incrementa o contador de pedidos
        printf("\n>> Pedido %d criado com sucesso.\n", novo_pedido.cod_pedido);
        printf("Nome do cliente: %s\n", novo_pedido.nome_cliente);
        printf("Itens do Pedido:\n");
        for (int i = 0; i < novo_pedido.num_itens; i++) {
            printf("  %s - R$ %.2f\n", novo_pedido.itens[i].nome, novo_pedido.itens[i].preco); // Exibe os itens do pedido
        }
        printf("Status: Pendente\n\n"); // Exibe o status do pedido
    } else {
        printf(">> Operação inválida. Não há itens cadastrados no cardápio. Por favor, tente novamente.\n");
    }
}

// Função para gerenciar os pedidos (exibir todos os pedidos)
void gerenciar_pedidos() {
    if (num_pedidos > 0) {
        printf("\n=========================================== Pedidos Realizados ============================================\n\n");
        for (int i = 0; i < num_pedidos; i++) {
            printf("\nPedido %d:\n", pedidos[i].cod_pedido); // exibe o código do pedido
            printf("Status: %s\n", status_para_string(pedidos[i].status)); // exibe o status do pedido
            printf("Cliente: %s\n", pedidos[i].nome_cliente); // exibe o nome do cliente
            printf("Itens do Pedido:\n");
            float total = 0; // variável para acumular o valor a ser pago
            for (int j = 0; j < pedidos[i].num_itens; j++) { // calcula o valor total a pagar
                printf("-> %s - R$ %.2f\n", pedidos[i].itens[j].nome, pedidos[i].itens[j].preco);
                total += pedidos[i].itens[j].preco; // Acumula o preço dos itens
            }
            printf("Total: R$ %.2f\n", total); // exibe o total que o cliente deve pagar
            printf("\n===========================================================================================================\n\n");
        }
    } else {
        printf(">> Não há pedidos cadastrados.\n");
    }
}

// Função para alterar o status do pedido
void alterar_status() {
    if (num_pedidos > 0) {
        int cod_pedido;
        printf("Informe o código do pedido a ser alterado: ");
        if (scanf("%d", &cod_pedido) != 1 || cod_pedido <= 0 || cod_pedido > num_pedidos) {
            printf(">> Código inválido. Operação cancelada.\n");
            while (getchar() != '\n');
            return;
        }
        cod_pedido--; // Ajuste do índice
        printf("Informe o novo status (0: PENDENTE, 1: EM_PREPARO, 2: PRONTO, 3: ENTREGUE): ");
        int novo_status;
        if (scanf("%d", &novo_status) != 1 || novo_status < 0 || novo_status > 3) {
            printf(">> Status inválido. Operação cancelada.\n");
            while (getchar() != '\n');
            return;
        }
        pedidos[cod_pedido].status = (StatusPedido)novo_status; // Atualiza o status do pedido
        printf(">> Status do pedido %d alterado com sucesso.\n", cod_pedido + 1);
    } else {
        printf(">> Não há pedidos cadastrados.\n");
    }
}

// Função para alterar um pedido existente
void alterar_pedido() {
    if (num_pedidos > 0) {
        int cod_pedido;
        printf("Informe o código do pedido a ser alterado: ");
        if (scanf("%d", &cod_pedido) != 1 || cod_pedido <= 0 || cod_pedido > num_pedidos) {
            printf(">> Código inválido. Operação cancelada.\n");
            while (getchar() != '\n');
            return;
        }
        cod_pedido--; // Ajuste do índice
        printf("Informe o novo nome do cliente: ");
        getchar(); // Limpar o buffer
        fgets(pedidos[cod_pedido].nome_cliente, sizeof(pedidos[cod_pedido].nome_cliente), stdin);
        pedidos[cod_pedido].nome_cliente[strcspn(pedidos[cod_pedido].nome_cliente, "\n")] = 0; // Remover a quebra de linha
        printf(">> Pedido %d atualizado com sucesso.\n", pedidos[cod_pedido].cod_pedido);
    } else {
        printf(">> Não há pedidos cadastrados.\n");
    }
}

// Função para remover um pedido pelo código
void remover_pedido() {
    if (num_pedidos > 0) {
        int cod_pedido;
        printf("Informe o código do pedido a ser removido: ");
        if (scanf("%d", &cod_pedido) != 1 || cod_pedido <= 0 || cod_pedido > num_pedidos) {
            printf(">> Código inválido. Operação cancelada.\n");
            while (getchar() != '\n');
            return;
        }
        cod_pedido--; // Ajuste do índice
        for (int i = cod_pedido; i < num_pedidos - 1; i++) {
            pedidos[i] = pedidos[i + 1]; // Move os pedidos para preencher o espaço do pedido removido
        }
        num_pedidos--; // Diminui o contador de pedidos
        printf(">> Pedido removido com sucesso.\n");
    } else {
        printf(">> Não há pedidos cadastrados.\n");
    }
}

// Função para converter o status do pedido para string
const char* status_para_string(StatusPedido status) {
    switch (status) {
        case pendente: return "Pendente";
        case em_preparo: return "Em preparo";
        case pronto: return "Pronto";
        case entregue: return "Entregue";
        default: return "Desconhecido";
    }
}