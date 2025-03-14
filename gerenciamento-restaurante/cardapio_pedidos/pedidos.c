#include "pedidos.h"

// Variáveis globais
pedido* pedidos = NULL; // Armazenar pedidos
int num_pedidos = 0; // Contador de pedidos
int capacidade_pedidos = 2; // Capacidade inicial para pedidos

// Função para criar um novo pedido
void criar_pedido_menu() {
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
        novo_pedido.status = PENDENTE;  // Status inicial do pedido
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

}

// Função para gerenciar pedidos
void gerenciar_pedidos() {
    if (num_pedidos > 0) { // verifica se há pedidos para exibir
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
        printf(">> Não há pedidos para exibir.\n\n"); // caso não haja pedidos cadastrados
    }
}

// Função para alterar o status de um pedido
void alterar_status() {
    if (num_pedidos > 0) { // verifica se há pedido para alterar
        printf("\n>> Preencha com as informações do pedido que deseja atualizar.\n");
        int cod_pedido;
        while(1) { // Repetição até um valor válido ser inserido
            printf("Número do pedido: "); // solicita o número do pedido
            if(scanf("%d", &cod_pedido) != 1 || cod_pedido <= 0 || cod_pedido > num_pedidos){ // garante que o valor inserido seja válido
                printf(">> Número inválido. Verifique se está correto e corresponde a um pedido cadastrado. Por favor, tente novamente.\n");
                while(getchar() != '\n'); // limpa o buffer de entrada
            } else {break;} // se o valor for válido, sai do loop
        }
        // Digitar o status do pedido
        cod_pedido--; // Ajuste do índice
        int opcao;
        while(1) { // repete até o usuário digitar um valor válido
            printf("\nStatus:\n");
            printf("(1) Pendente\n(2) Em preparo\n(3) Pronto\n(4) Entregue\n"); // exibe as opções
            printf("<< Informe o status: "); // solicita o valor referente ao status
            if(scanf("%d", &opcao) != 1 || opcao < 1 || opcao > 4) { // garante que o usuário digite um valor válido
                printf(">> Opção inválida. Por favor, tente novamente.\n");
                while(getchar() != '\n'); // limpa o buffer de entrada
            } else {break;} // se o valor for válido, sai do loop
        }
        pedidos[cod_pedido].status = (StatusPedido)(opcao - 1); // Atualiza o status do pedido
        printf(">> Status do pedido %d alterado para: %s\n", cod_pedido + 1, status_para_string(pedidos[cod_pedido].status)); // mensagem de confirmação

        // Verifica se o status foi alterado para "Entregue"
        if (pedidos[cod_pedido].status == ENTREGUE) {
            printf(">> O pedido %d foi finalizado e entregue ao cliente.\n", cod_pedido + 1); // mensagem de confirmação
        }
    } else {
        printf(">> Não há pedidos cadastrados.\n\n"); // caso não haja pedidos cadastrados
    }
}


// Função para alterar um pedido existente
void alterar_pedido() {
   if(num_pedidos > 0 && codigo > 0) { // verifica se há pedido ou item
        printf("\n>> Preencha com as informações do pedido que deseja atualizar.\n");
        int cod_pedido; // variável referente ao código do pedido
        while(1) { // Repetição até um valor válido ser inserido
            printf("Número do pedido: ");
            if(scanf("%d", &cod_pedido) != 1 || cod_pedido <= 0 || cod_pedido > num_pedidos){ // garante que o valor inserido seja válido
                printf(">> Número inválido. Verifique se está correto e corresponde a um pedido cadastrado. Por favor, tente novamente.\n");
                while(getchar() != '\n'); // limpa o buffer de entrada
            } else {break;} // se o valor inserido for válido, sai do loop
        }
        cod_pedido--; // Ajuste do índice
        Pedido *pedido = &pedidos[cod_pedido]; // Pega o pedido correspondente
        printf("\n>> Alterando o pedido %d de %s:\n", pedido->cod_pedido, pedido->nome_cliente);
        int num_itens_pedido;
        printf("Quantidade de itens: "); // solicita a quantidade de itens
        while(1){ // repetir até o usuário digitar um valor válido
            if(scanf("%d", &num_itens_pedido) != 1){ // garante que o usuário só digite int
                printf(">> Valor inválido. Por favor, tente novamente.\n");
                while(getchar() != '\n'); // limpa o buffer de entrada
            }else{break;} // se o valor inserido for válido, sai do loop
        }
        
        if (num_itens_pedido > 0) {
            pedido->num_itens = num_itens_pedido; // Atualiza o número de itens do pedido
            // Receber os novos itens do pedido
            for (int i = 0; i < num_itens_pedido; i++) {
                int codigo_item;
                while(1) { // repete até o usuário digitar um valor válido
                    printf("Código do item %d do pedido: ", i + 1); // solicita o código do item do pedido
                    if(scanf("%d", &codigo_item) != 1 || codigo_item <= 0 || codigo_item > codigo){ // garante que o valor inserido seja válido
                        printf(">> Código inválido. Verifique se está correto e corresponde a um item cadastrado. Por favor, tente novamente.\n");
                        while(getchar() != '\n'); // limpa o buffer de entrada
                    } else {break;} // se o valor inserido for válido, sai do loop
                }
                pedido->itens[i] = cardapio[codigo_item - 1]; // Atualiza item do pedido
            }
            printf(">> Pedido %d atualizado com sucesso.\n", pedido->cod_pedido); // mensagem de confirmação
        } else {
            printf(">> Número de itens inválido. Operação cancelada.\n"); // caso o número de itens for inválido
        }
    } else if(num_pedidos <= 0){ // verifica se não há pedidos cadastrados
        printf(">> Não há pedidos cadastrados.\n");
    } else if(codigo <= 0){ // verifica se não há itens cadastrados
        printf(">> Não há itens cadastrados.\n");
    }
}


// Função para remover um pedido
void remover_pedido() {
    if(num_pedidos > 0){ // verifica se há pedidos para remover
        printf("\n>> Preencha com as informações do pedido que deseja remover.\n");
        int cod_pedido;
        while(1){ // repete até o usuário digitar um valor válido
            printf("Número do pedido: "); // solicita o número do pedido
            if(scanf("%d", &cod_pedido) != 1 || cod_pedido <= 0 || cod_pedido > num_pedidos){ // garante que o valor seja válido
                printf(">> Número inválido. Verifique se está correto e corresponde a um pedido cadastrado. Por favor, tente novamente.\n");
                while(getchar() != '\n'); // limpa o buffer de entrada
            }else{break;} // se o valor inserido for válido, sai do loop
        }
        cod_pedido--; // Ajuste do índice
        // Remover pedido e reorganizar lista
        for (int i = cod_pedido; i < num_pedidos - 1; i++) {
            pedidos[i] = pedidos[i + 1]; // Move os pedidos para preencher o espaço do pedido removido
        }
        num_pedidos--; // Diminui o contador de pedidos
        printf(">> Pedido removido com sucesso.\n"); // mensagem de confirmação
    } else {
        printf(">> Não há pedidos cadastrados.\n"); // caso não haja pedidos cadastrados
    }
}

// Função para inicializar um pedido
void inicializar_pedido(pedido* p) {
    p->numero_pedido = 0;
    p->itens = NULL;
    p->total_itens = 0;
    p->total_pedido = 0.0;
}

// Função para adicionar um item ao pedido
void adicionar_item_pedido(pedido* p, int codigo_item, int quantidade, float preco_unitario) {
    p->itens = realloc(p->itens, (p->total_itens + 1) * sizeof(pedido_item));
    if (p->itens == NULL) {
        printf(">> Erro ao alocar memória para os itens do pedido.\n");
        exit(1);
    }
    p->itens[p->total_itens].codigo_item = codigo_item;
    p->itens[p->total_itens].quantidade = quantidade;
    p->itens[p->total_itens].preco_unitario = preco_unitario;
    p->total_pedido += quantidade * preco_unitario;
    p->total_itens++;
}

// Função para remover um item do pedido
void remover_item_pedido(pedido* p, int codigo_item) {
    for (int i = 0; i < p->total_itens; i++) {
        if (p->itens[i].codigo_item == codigo_item) {
            p->total_pedido -= p->itens[i].quantidade * p->itens[i].preco_unitario;
            for (int j = i; j < p->total_itens - 1; j++) {
                p->itens[j] = p->itens[j + 1];
            }
            p->total_itens--;
            p->itens = realloc(p->itens, p->total_itens * sizeof(pedido_item));
            return;
        }
    }
    printf(">> Item com código %d não encontrado no pedido.\n", codigo_item);
}

// Função para exibir o pedido
void exibir_pedido(const pedido* p) {
    printf("\n======================== Pedido ========================\n");
    printf("Número do Pedido: %d\n", p->numero_pedido);
    printf("%-10s %-10s %-15s %-10s\n", "Código", "Quantidade", "Preço Unitário", "Subtotal");
    printf("-------------------------------------------------------\n");
    for (int i = 0; i < p->total_itens; i++) {
        float subtotal = p->itens[i].quantidade * p->itens[i].preco_unitario;
        printf("%-10d %-10d %-15.2f %-10.2f\n", p->itens[i].codigo_item, p->itens[i].quantidade, p->itens[i].preco_unitario, subtotal);
    }
    printf("-------------------------------------------------------\n");
    printf("Total do Pedido: R$ %.2f\n", p->total_pedido);
    printf("=======================================================\n");
}

// Função para liberar a memória do pedido
void liberar_pedido(pedido* p) {
    free(p->itens);
    p->itens = NULL;
    p->total_itens = 0;
    p->total_pedido = 0.0;
}
