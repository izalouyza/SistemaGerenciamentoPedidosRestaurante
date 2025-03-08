#include <stdio.h>
#include <locale.h>
#include <string.h>

#define max 10 // Total de itens

typedef enum {entrada, principal, sobremesa, bebida} categoria;
char* categs[] = {"Entrada", "Principal", "Sobremesa", "Bebida"};

typedef struct {
    char nome[20];
    char descri[50];
    float preco;
    categoria catego;
} item;

item cardapio[max]; // Guardar itens do cardápio
int codigo = 0;

void exibir_card() {
    if (codigo > 0) {
        puts("\n=================== Cardápio ===================");
        puts("Código - Nome - Descrição - Preço R$ - Categoria");
        puts("================================================");
        for (int i = 0; i < codigo; i++) {
            printf("%d - %s - %s ........ %.2f - %s\n", i + 1, cardapio[i].nome, cardapio[i].descri, cardapio[i].preco, categs[cardapio[i].catego]);
        }
        puts("================================================\n");
    } else {
        puts("Nenhum item cadastrado ainda.\n");
    }
}

void cadastro_card(item *p) {
    getchar(); // Limpar o buffer do teclado

    printf("Digite o nome do item: ");
    fgets(p->nome, sizeof(p->nome), stdin);
    p->nome[strcspn(p->nome, "\n")] = '\0'; // Remover '\n'

    printf("Digite a descrição [max.: 50 letras]: ");
    fgets(p->descri, sizeof(p->descri), stdin);
    p->descri[strcspn(p->descri, "\n")] = '\0'; // Remover '\n'

    printf("Digite o preço em R$: ");
    scanf("%f", &p->preco);

    int n = 0;
    puts("Digite o número correspondente à categoria:");
    puts("(1) Entrada\n(2) Principal\n(3) Sobremesa\n(4) Bebida");
    
    while (n < 1 || n > 4) {
        scanf("%d", &n);
        if (n < 1 || n > 4) {
            puts("Número inválido, tente novamente.");
        }
    }

    p->catego = (categoria)(n - 1);
}

void remover_card() {
    int num;
    printf("Digite o código do item que deseja remover: ");
    scanf("%d", &num);
    num--;

    if (num >= 0 && num < codigo) {
        for (int i = num; i < codigo - 1; i++) {
            cardapio[i] = cardapio[i + 1];
        }
        codigo--;
        puts("Item removido com sucesso!\n");
    } else {
        puts("Código inválido, tente novamente!\n");
    }
}

int main() {
    setlocale(LC_ALL, "pt_BR.UTF-8");

    int opcion = 0;
    int num;

    while (opcion != 5) {
        puts("\n===== Gerenciamento do restaurante, o que deseja fazer? =====");
        puts("(1) Cadastrar cardápio");
        puts("(2) Remover itens do cardápio");
        puts("(3) Exibir cardápio");
        puts("(4) Atualizar cardápio");
        puts("(5) Sair");

        scanf("%d", &opcion);

        switch (opcion) {
            case 1:
                if (codigo < max) {
                    puts("============= Cadastrar cardápio =============");
                    cadastro_card(&cardapio[codigo]);
                    codigo++;
                    puts("Item cadastrado com sucesso!");
                } else {
                    puts("Espaço insuficiente!");
                }
                break;

            case 2:
                if (codigo > 0) {
                    remover_card();
                } else {
                    puts("Nenhum item a ser removido!");
                }
                break;

            case 3:
                exibir_card();
                break;

            case 4:
                if (codigo > 0) {
                    printf("Digite o código do item que deseja atualizar: ");
                    scanf("%d", &num);
                    num--;
                    if (num >= 0 && num < codigo) {
                        puts("============= Atualizar cardápio =============");
                        cadastro_card(&cardapio[num]);
                        puts("Item atualizado com sucesso!");
                    } else {
                        puts("Código inválido, tente novamente!");
                    }
                } else {
                    puts("Nenhum item a ser atualizado!");
                }
                break;

            case 5:
                puts("Obrigado, volte sempre!");
                break;

            default:
                puts("Número inválido, tente novamente!");
                break;
        }
    }

    return 0;
}
