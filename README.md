# Desenvolvimento de um Sistema de Gerenciamento de Pedidos para Restaurante

#include <stdio.h>
#include <locale.h>

enum categoria{entrada, principal, sobremesa, bebida};
char* categs[] = {"Entrada", "Principal", "Sobremesa", "Bebida"};

typedef struct{
	char nome[20];
    char descri[50];
	float preco;
	int cod;
} cardapio;

void cadastro(cardapio *p){
	printf("============= Cadastro de cardápio =============\n");
	getchar(); //limpar o buffer
	printf("Digite o nome do produto: "); 
	gets(p->nome);
	printf("Digite a descrição [max.: 50 letras]: ");
	gets(p->descri);
	printf("Digite o preço em R$: ");
	scanf("%f", &p->preco);
	p->cod += 1;
}

typedef struct{
	char nome[15];
	int num; //numero da mesa
	int itens;
};

/*-Cada pedido deve conter um identificador, dados do cliente, itens do pedido
 (referenciando os itens do cardápio) e status (utilizando enumerações, 
 ex.: PENDENTE, EM_PREPARO, PRONTO, ENTREGUE).
-Implementar funcionalidades para a criação, alteração e finalização de pedidos.*/

int main(){
	setlocale(LC_ALL, "Portuguese");
	int opcion = 0;
	cardapio c;
	enum categoria cat;
	printf("===== Gerenciamento do restaurante, o que deseja fazer? =====\n\n");
	while (opcion != 4){
		printf("(1) Cadastro do cardápio\n(2) Gerenciar pedidos\n(3) Gerenciamento de dados\n(4) Sair\n\n");
		scanf("%d", &opcion);
		switch (opcion)
		{
		case 1: //ok
			cadastro(&c);
			int n = 0;
			printf("Digite o número correspondente a categoria: \n");
			printf("(1) Entrada\n(2) Principal\n(3) Sobremesa\n(4) Bebida\n");
			while (n < 1 || n > 4){
				scanf("%d", &n);
				if (n < 1 || n > 4){
					printf("Número inválido, tente novamente.\n\n");
				}
			}
			n -= 1;
			cat = (enum categoria)n;
			printf("Nome do produto: %s\nDescrição: %s\nPreço: R$%.2f\nCategoria: %s\nCódigo: %d", c.nome, c.descri, c.preco, categs[cat], c.cod);
			break;
		case 2:
			
		case 4:
			printf("Obrigado, volte sempre.\n");
		default:
			printf("Número inválido, tente novamente.\n\n");
			break;
		}
	}
	return 0;
}
