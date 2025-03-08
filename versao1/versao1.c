#include <stdio.h>
#include <locale.h>

#define max 10 //Total de itens

typedef enum {entrada, principal, sobremesa, bebida} categoria;
char* categs[] = {"Entrada", "Principal", "Sobremesa", "Bebida"};

typedef struct{
	char nome[20];
    char descri[50];
	float preco;
	categoria catego;
} item;

item cardapio[max]; //guardar itens do cardapio
int codigo = 0;

void exibir_card(){ //exibir o cardápio
	if(codigo > 0){
		printf("\n=================== Cardápio ===================\n");
		printf("Código - Nome - Descrição - Preço R$ - Categoria\n");
		printf("================================================\n");
		for(int i = 0; i < codigo; i++){
			printf("%d - %s - %s ........ %.2f - %s\n", i+1, cardapio[i].nome, cardapio[i].descri, cardapio[i].preco, categs[cardapio[i].catego]);
		}
		printf("================================================\n\n");
	} else{
		printf("Nenhum item cadastrado ainda.\n\n");
	}
}

void cadastro_card(item *p){ //cadastrar e atualizar itens do card pio
	getchar(); //limpar o buffer
	printf("Digite o nome do item: "); 
	gets(p->nome);
	printf("Digite a descrição [max.: 50 letras]: ");
	gets(p->descri);
	printf("Digite o preço em R$: ");
	scanf("%f", &p->preco);
	int n = 0;
	printf("Digite o número correspondente a categoria: \n");
	printf("(1) Entrada\n(2) Principal\n(3) Sobremesa\n(4) Bebida\n");
	while (n < 1 || n > 4){
		scanf("%d", &n);
		if (n < 1 || n > 4){
			printf("Número inválido, tente novamente.\n\n");
		}
	}
	n--;
	p->catego = (categoria)n;
}

void remover_card(){
	int num = 0;
	printf("Digite o código do item que deseja remover: ");
	scanf("%d", &num);
	num--;

	if(num >= 0 || num < codigo){
		for(int i = num; i < codigo; i++){ //removedor
			cardapio[i] = cardapio[i+1];
		}
		codigo--;
		printf("Item removido com sucesso!\n\n");
	}else{
		printf("Código inválido, tente novamente!\n\n");
	}
}

int main(){
	setlocale(LC_ALL, "Portuguese");
	int opcion = 0;
	int num = 0;
	while (opcion != 5){
		printf("\n===== Gerenciamento do restaurante, o que deseja fazer? =====\n");
		printf("(1) Cadastrar cardápio\n(2) Remover itens do cardápio\n(3) Exibir cardápio\n(4) Atualizar cardápio\n(5) Sair\n\n");
		scanf("%d", &opcion);
		switch (opcion)
		{
		case 1: //cadastrar itens do card pio
			if (codigo < max){
				printf("============= Cadastrar cardápio =============\n");
				cadastro_card(&cardapio[codigo]);
				codigo++;
				printf("Item cadastrado com sucesso!\n");
			}else{
				printf("Espaço insuficiente!\n");
				break;
			}
			break;
		case 2: //remover itens do card pio
			if (codigo > 0){
				remover_card();
			}else{
				printf("Nenhum item a ser removido!\n");
			}
			break;
		case 3: //exibir card pio
			exibir_card();
			break;
		case 4: //atualizar card pio
			if (codigo > 0){
				printf("Digite o código do item que deseja atualizar: ");
				scanf("%d", &num);
				num--;
				if(num >= 0 && num < codigo){
					printf("============= Atualizar cardápio =============\n");
					cadastro_card(&cardapio[num]);
					printf("Item atualizado com sucesso!\n");
				}else{
					printf("Código inválido, tente novamente!\n");
				}
			}else{
				printf("Nenhum item a ser atualizado!\n");
			}
			break;
		case 5:
			printf("Obrigado, volte sempre!\n");
			break;
		default:
			printf("Número inválido, tente novamente!\n");
			break;
		}
	}
	return 0;
}
