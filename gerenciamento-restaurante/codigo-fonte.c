#include <stdio.h> // biblioteca padrão
#include <locale.h> // biblioteca para configurar o código para português
#include <stdlib.h> // biblioteca para uso de alocações dinâmicas
#include <string.h> // biblioteca para tratamento de strings

// Enumeração de categorias do cardápio
typedef enum {entrada, principal, sobremesa, bebida} categoria;
char* categs[] = {"Entrada", "Principal", "Sobremesa", "Bebida"};
// Enumeração das strings para a interface
char* strings[] = {"Código", "Nome", "Descrição", "Preço R$", "Categoria"};

// Struct para representar um item do cardápio
typedef struct {
    char nome[100]; // nome do item
    char descri[100]; // descrição do item
    float preco; // preço em R$ do item
    categoria catego; // Categoria do item
} item;

// Enum para status dos pedidos
typedef enum {PENDENTE, EM_PREPARO, PRONTO, ENTREGUE} StatusPedido;

// Struct para representar um pedido
typedef struct {
    int cod_pedido;          // Identificador do pedido
    char nome_cliente[100];  // Nome do cliente
    item* itens;            // Armazenar os itens do pedido
    int num_itens;          // Número de itens no pedido
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
    if(codigo > 0) { //Verifica se há itens para exibir
        printf("\n================================================= Cardápio ================================================\n\n");
        printf("%-10s %-20s %-40s %-15s %-10s\n", strings[0], strings[1], strings[2], strings[3], strings[4]);
        printf("___________________________________________________________________________________________________________\n\n");
        for(int i = 0; i < codigo; i++) {
            printf("%-10d %-20s %-40s %-15.2f %-10s\n", i + 1, cardapio[i].nome, cardapio[i].descri, cardapio[i].preco, categs[cardapio[i].catego]);
        }
        printf("___________________________________________________________________________________________________________\n\n");
    } else {
        printf(">> Não há itens cadastrados.\n\n"); // caso não haja itens cadastrados
    }
}

// Função para cadastrar itens no cardápio
void cadastro_card(item *p) { // Cadastrar e atualizar itens do cardápio
    getchar(); // Limpar o buffer
    printf("Nome do item: "); // solicita o nome do item
    fgets(p->nome, sizeof(p->nome), stdin); //recebe o nome do item
    p->nome[strcspn(p->nome, "\n")] = 0; // Remover a quebra de linha

    printf("Descrição [máx.: 100 caracteres]: "); // solicita a descrição do item
    fgets(p->descri, sizeof(p->descri), stdin); //recebe a descrição do item
    p->descri[strcspn(p->descri, "\n")] = 0; // Remover a quebra de linha

    while (1) {  // Repetição até um valor válido ser inserido
        printf("Preço em R$: ");
        // Tenta ler o preço como um float
        if (scanf("%f", &p->preco) != 1) { //garante que o usuário digite um valor float
            // Se a leitura falhar, limpa o buffer e solicita novamente
            printf(">> Valor inválido. O preço não pode incluir letras e caracteres especiais. Por favor, tente novamente.\n");
            while(getchar() != '\n');  // Limpar o buffer de entrada
        } else if (p->preco < 0) { // evitar que o preço seja negativo
            printf(">> Valor inválido. O preço não pode ser um valor negativo. Por favor, tente novamente.\n");
        } else {break;} // Se o valor for válido e não negativo, sai do loop
    }
    // Escolha da categoria do item
    printf("\nCategoria: \n");
    while(1){ // Repetição até um valor válido ser inserido
        printf("(1) Entrada\n(2) Principal\n(3) Sobremesa\n(4) Bebida\n"); //mostrar as opções
        printf("<< Informe a opção: "); // solicita ao usuário a escolher a opção
        int n;
        if(scanf("%d", &n) != 1 || n < 1 || n > 4) { //garante que o usuário digite um valor int
            printf(">> Opção inválida. Por favor, tente novamente.\n");
            while(getchar() != '\n'); // limpar o buffer de entrada
        } else {
            p->catego = (categoria)(n - 1); //converte o int para categoria
            break; // se o valor for válido, sai do loop
        }
    }
}

// Função para redimensionar o cardápio 
void redimensionar_cardapio() {
    capacidade_cardapio *= 2;
    item* temp = realloc(cardapio, capacidade_cardapio * sizeof(item));
    if (temp == NULL) {
        printf(">> Erro ao redimensionar o cardápio.\n");
        exit(1); // Sair do programa em caso de erro
    }
    cardapio = temp;
}

// Função para remover itens do cardápio
void remover_card() {
    if(codigo > 0){ //verifica se há itens para remover
        int num;  // Usar um inteiro simples
        printf("\n>> Preencha com as informações do item que deseja remover.\n");
        while(1) { // Repetição até um valor válido ser inserido
            printf("Código do item: "); // solicita o código do item
            if(scanf("%d", &num) != 1 || num < 1 || num > codigo) {  // garante que o valor inserido seja válido
                printf(">> Código inválido. Verifique se está correto e corresponde a um item cadastrado. Por favor, tente novamente.\n");
                while(getchar() != '\n'); // limpa o buffer de entrada
            } else {break;} //se o valor for válido, sai do loop
        }
        num--;  // Ajuste do índice
        for(int i = num; i < codigo - 1; i++) { // Remover item
            cardapio[i] = cardapio[i + 1];
        }
        codigo--; // Diminui o contador de itens
        printf(">> Item removido com sucesso.\n\n"); // mensagem de confirmação
    } else {
        printf(">> Não há itens cadastrados.\n\n"); // caso não haja itens cadastrados
    }
}

// Função para criar um novo pedido
void criar_pedido_menu() {
    if (codigo > 0) { // verificar se há itens a oferecer ao cliente
        char nome_cliente[100];
        printf("Nome do cliente: "); //solicita o nome do cliente
        getchar(); // Limpar o buffer
        fgets(nome_cliente, sizeof(nome_cliente), stdin); //recebe o nome do clinete
        nome_cliente[strcspn(nome_cliente, "\n")] = 0; // Remover a quebra de linha

        int num_itens_pedido; //determina quantos itens o cliente gostaria de consumir
        while(1) { // Repetição até um valor válido ser inserido
            printf("Quantidade de itens: "); //solicita a quantidade de itens
            if(scanf("%d", &num_itens_pedido) != 1 || num_itens_pedido <= 0) { //garante que o valor inserido seja válido
                printf(">> Quantidade inválida. A quantidade de itens não pode ser negativa ou incluir letras e caracteres especiais. Por favor, tente novamente.\n");
                while(getchar() != '\n'); // limpa o buffer de entrada
            } else {break;} //se o valor for válido, sai do loop
        }
        if (num_pedidos >= capacidade_pedidos) { 
            capacidade_pedidos *= 2;
            Pedido* temp = realloc(pedidos, capacidade_pedidos * sizeof(Pedido));
            if (temp == NULL) {
                printf(">> Erro ao redimensionar os pedidos.\n");
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
            while(1) { // Repetição até um valor válido ser inserido
                printf("Código do item %d: ", i + 1); // solicita o código do item
                if(scanf("%d", &codigo_item) != 1 || codigo_item < 1 || codigo_item > codigo) { // garante que o valor inserido seja válido
                    printf(">> Código inválido. Verifique se está correto e corresponde a um item cadastrado. Por favor, tente novamente.\n");
                    while(getchar() != '\n'); // limpa o buffer de entrada
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
        printf(">> Operação inválida. Não há itens cadastrados no cardápio. Por favor, tente novamente.\n");
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
    if (num_pedidos > 0) { //verifica se há pedidos para exibir
        printf("\n=========================================== Pedidos Realizados ============================================\n\n");
        for (int i = 0; i < num_pedidos; i++) {
            printf("\nPedido %d:\n", pedidos[i].cod_pedido); //exibir o código do pedido, exemplo: (pedido 1, pedido 2, [...], pedido n)
            printf("Status: %s\n", status_para_string(pedidos[i].status)); //exibir o status do pedido
            printf("Cliente: %s\n", pedidos[i].nome_cliente); //exibir o nome do cliente
            printf("Itens do Pedido:\n");
            float total = 0; // variável para acumular o valor a ser pago
            for (int j = 0; j < pedidos[i].num_itens; j++) { //calcular o valor total a pagar
                printf("-> %s - R$ %.2f\n", pedidos[i].itens[j].nome, pedidos[i].itens[j].preco);
                total += pedidos[i].itens[j].preco;
            }
            printf("Total: R$ %.2f\n", total); //exibe o total que o cleinte deve pagar
            printf("\n===========================================================================================================\n\n");
        }
    } else {
        printf(">> Não há pedidos para exibir.\n\n"); // caso não haja pedidos cadastrados
    }
}
// Função para alterar o status do pedido
void alterar_status() {
    if (num_pedidos > 0) { //verifica se há pedido para alterar
        printf("\n>> Preencha com as informações do pedido que deseja atualizar.\n");
        int cod_pedido;
        while(1) { // Repetição até um valor válido ser inserido
            printf("Número do pedido: "); // solicita o número do pedido
            if(scanf("%d", &cod_pedido) != 1 || cod_pedido <= 0 || cod_pedido > num_pedidos){ // garante que o valor inserido seja válido
                printf(">> Número inválido. Verifique se está correto e corresponde a um pedido cadastrado. Por favor, tente novamente.\n");
                while(getchar() != '\n');
            } else {break;} // se o valor for válido, sai do loop
        }
        //Digitar o status do pedido
        cod_pedido--; // Ajuste do índice
        int opcao;
        while(1) { //repete até o usuário digitar um valor válido
            printf("\nStatus:\n");
            printf("(1) Pendente\n(2) Em preparo\n(3) Pronto\n(4) Entregue\n"); // exibe as opções
            printf("<< Informe o status: "); // solicita o valor referente ao status
            if(scanf("%d", &opcao) != 1 || opcao < 1 || opcao > 4) { //garante que o usuário digite um valor válido
                printf(">> Opção inválida. Por favor, tente novamente.\n");
                while(getchar() != '\n'); // limpa o buffer de entrada
            } else {break;} // se o valor for válido, sai do loop
        }
        pedidos[cod_pedido].status = (StatusPedido)(opcao - 1);
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
    if(num_pedidos > 0 && codigo > 0) { //verifica se há pedido ou item
        printf("\n>> Preencha com as informações do pedido que deseja atualizar.\n");
        int cod_pedido; // variável referente ao código do pedido
        while(1) { // Repetição até um valor válido ser inserido
            printf("Número do pedido: ");
            if(scanf("%d", &cod_pedido) != 1 || cod_pedido <= 0 || cod_pedido > num_pedidos){ // garante que o valor inserido seja válido
                printf(">> Número inválido. Verifique se está correto e corresponde a um pedido cadastrado. Por favor, tente novamente.\n");
                while(getchar() != '\n'); //limpa o buffer de entrada
            } else {break;} // se o valor inserido for válido, sai do loop
        }
        cod_pedido--; // Ajuste do índice
        Pedido *pedido = &pedidos[cod_pedido];
        printf("\n>> Alterando o pedido %d de %s:\n", pedido->cod_pedido, pedido->nome_cliente);
        int num_itens_pedido;
        printf("Quantidade de itens: "); // solicita a quantidade de itens
        while(1){ //repetir até o usuário digitar um valor válido
            if(scanf("%d", &num_itens_pedido) != 1){ //garante que o usuário só digite int
                printf(">> Valor inválido. Por favor, tente novamente.\n");
                while(getchar() != '\n'); // limpa o buffer de entrada
            }else{break;} // se o valor inserido for válido, sai do loop
        }
        
        if (num_itens_pedido > 0) {
            pedido->num_itens = num_itens_pedido;
            // Receber os novos itens do pedido
            for (int i = 0; i < num_itens_pedido; i++) {
                int codigo_item;
                while(1) { //repete até o usuário digitar um valor válido
                    printf("Código do item %d do pedido: ", i + 1); // solicita o código do item do pedido
                    if(scanf("%d", &codigo_item) != 1 || codigo_item <= 0 || codigo_item > codigo){ // garante que o valor inserido seja válido
                        printf(">> Código inválido. Verifique se está correto e corresponde a um item cadastrado. Por favor, tente novamente.\n");
                        while(getchar() != '\n'); // limpa o buffer de entrada
                    } else {break;} // se o valor inserido for válido, sai do loop
                }
                pedido->itens[i] = cardapio[codigo_item - 1]; // Atualizar item do pedido
            }
            printf(">> Pedido %d atualizado com sucesso.\n", pedido->cod_pedido); // mensagem de confirmação
        } else {
            printf(">> Número de itens inválido. Operação cancelada.\n"); // caso o número de itens for inválido
        }
    } else if(num_pedidos <= 0){ // verifica se não há pedidos cadastrados
        printf(">> Não há pedidos cadastrados.\n");
    }else if(codigo <= 0){ // verifica se não há itens cadastrados
        printf(">> Não há itens cadastrados.\n");
    }
}

// Função para remover um pedido pelo código
void remover_pedido() {
    if(num_pedidos > 0){ //verifica se há pedidos para remover
        printf("\n>> Preencha com as informações do pedido que deseja remover.\n");
        int cod_pedido;
        while(1){ //repete até o usuário digitar um valor válido
            printf("Número do pedido: "); //solicita o número do pedido
            if(scanf("%d", &cod_pedido) != 1 || cod_pedido <= 0 || cod_pedido > num_pedidos){ //garante que o valor seja válido
                printf(">> Número inválido. Verifique se está correto e corresponde a um pedido cadastrado. Por favor, tente novamente.\n");
                while(getchar() != '\n'); //limpa o buffer de entrada
            }else{break;} // se o valor inserido for válido, sai do loop
        }
        cod_pedido--; // Ajuste do índice
        // Remover pedido e reorganizar lista
        for (int i = cod_pedido; i < num_pedidos - 1; i++) {
            pedidos[i] = pedidos[i + 1];
        }
        num_pedidos--; // ajuste do índice
        printf(">> Pedido removido com sucesso.\n"); // mensagem de confirmação
    }else{
        printf(">> Não há pedidos cadastrados.\n"); //caso não haja pedidos cadastrados
    }
}

int main() {
    setlocale(LC_ALL, "Portuguese"); //configurar sistema para o idioma português
    // variável dinâmica para interagir com a interface principal
    int *opcion = (int *)malloc(sizeof(int)); 
    // variável dinâmica para interagir com a interface de saída
    int *opc = (int *)malloc(sizeof(int));

    // Alocar memória inicial
    cardapio = malloc(capacidade_cardapio * sizeof(item));
    if (cardapio == NULL) { // verifica se foi alocado na memória corretamente
        printf(">> Erro ao alocar memória para o cardápio.\n");
        return 1; // Sair do programa em caso de erro
    }
    
    pedidos = malloc(capacidade_pedidos * sizeof(Pedido));
    if (pedidos == NULL) {
        printf(">> Erro ao alocar memória para os pedidos.\n");
        free(cardapio); // Liberar memória do cardápio antes de sair
        return 1; // Sair do programa em caso de erro
    }

    while (1) { //loop infinito que permite ao usuário interagir diversas vezes com a interface principal
        printf("\n========================================== Gerenciamento do Restaurante ===================================\n\n");
        printf("(1) Cadastrar item \n(2) Exibir cardápio\n(3) Atualizar cardápio\n(4) Remover itens do cardápio\n");
        printf("(5) Criar pedido\n(6) Gerenciar pedidos\n(7) Alterar status de pedidos\n(8) Alterar pedido\n(9) Remover pedido\n(10) Sair\n\n");
        while(1){ //repetir até o usuário digitar um valor válido
            printf("<< Informe a opção: "); // solicita ao usuário a opção
            if(scanf("%d", opcion) != 1){ //garante que o usuário digite um int
                printf(">> Opção inválida. Por favor, tente novamente.\n");
                while(getchar() != '\n'); // limpa o buffer de entrada
            }else{break;} // se o valor inserido for válido, sai do loop
        }
        switch (*opcion) { //permite ao usuário interagir com a interface
            case 1: // Cadastrar itens no cardápio
                if (codigo >= capacidade_cardapio) {
                    redimensionar_cardapio(); //função para redimensionar o cardápio
                }
                printf("\n============================================== Cadastrar Item ==============================================\n\n");
                cadastro_card(&cardapio[codigo]); // função para executar o processo de cadastro do item do cardápio
                codigo++; //atualiza o índice
                printf(">> Item cadastrado com sucesso.\n"); // mensagem de confirmação
                break;
            case 2: // Exibir o cardápio
                exibir_card(); // função para exibir o cardápio
                break;
            case 3: // Atualizar os itens do cardápio
                if (codigo > 0) { //verifica se há itens para atualizar
                    int num;
                    printf("\n>> Preencha com as informações do item que deseja atualizar.\n");
                    while(1) { // Repetição até um valor válido ser inserido
                        printf("Código do item: "); // solicita ao usuário o código do item
                        if(scanf("%d", &num) != 1 || num < 1 || num > codigo){ // garante que o valor inserido seja válido
                            printf(">> Código inválido. Verifique se está correto e corresponde a um item cadastrado. Por favor, tente novamente.\n");    
                            while(getchar() != '\n'); // limpa o buffer de entrada
                        } else {break;} // se o valor inserido for válido, sai do loop
                    }
                    num--; // Ajustar para índice
                    printf("\n============================================= Atualizar Cardápio ============================================\n\n");
                    cadastro_card(&cardapio[num]); //Função reaproveitada para atualizar o item escolhido
                    printf(">> Item atualizado com sucesso.\n"); // mensagem de confirmaão
                } else {
                    printf(">> Não há itens cadastrados.\n"); // caso não haja itens cadastrados
                }
                break;
            case 4: // remover itens do cardápio
                if(codigo > 0){
                    exibir_card(); // exibe o cardápio para saber o código do item que deseja remover
                }
                remover_card(); // chama a função para executar o processo de remoção de itens
                break;
            case 5:
                criar_pedido_menu(); //chama a função para executar o processo de criação de pedidos
                break;
            case 6:
                gerenciar_pedidos(); //chama a função para exibir os pedidos
                break;
            case 7:
                alterar_status(); //chama a função para executar o processo de atualização de status do pedido
                break;
            case 8:
                alterar_pedido(); //chama a função para executar o processo de alteração de pedidos
                break;
            case 9:
                remover_pedido(); //chama a função para executar o processo de remoção de pedidos
                break;
            case 10: // Sair do sistema
                while(1){ // repete até que o usuário digite um valor válido
                    printf("<< Tem certeza que deseja sair?\n[1] Sim\n[0] Não\n"); // pergunta se o usuário tem certeza
                    if(scanf("%d", opc) != 1){ // garante que o usuário só digite o valor rápido
                        printf("<< Opção inválida. Por favor, insira [1] Sim ou [0] Não.\n");
                        while(getchar() != '\n');    
                    }else if(*opc < 0 || *opc > 1){
                        printf("<< Opção inválida. Por favor, insira [1] Sim ou [0] Não.\n");
                    }else{break;} // se o valor inserido for válido, sai do loop
                }
                free(cardapio); // libera a variável dinâmica cardapio para evitar vazamento de memória
                free(pedidos); // libera a variável dinâmica pedidos para evitar vazamento de memória
                if(*opc == 1){ // verifica se o usuário escolheu a opção 1
                    printf(">> Obrigado, volte sempre.\n");
                    free(opcion); // libera a variável dinâmica opcion para evitar vazamento de memória
                    free(opc); // libera a variável dinâmica opc para evitar vazamento de memória
                    return 0; // fecha o sistema
                }
                break;
            default: // caso o usuário digite uma opção inválida
                printf(">> Opção inválida. Por favor, tente novamente.\n");
                break;
        }
    }
}
