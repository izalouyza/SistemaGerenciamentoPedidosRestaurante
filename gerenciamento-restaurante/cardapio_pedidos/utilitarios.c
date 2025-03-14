#include "utilitarios.h"

// Função para limpar o buffer de entrada
void limpar_buffer() {
    while (getchar() != '\n'); // Limpa o buffer até encontrar uma nova linha
}

// Função para ler um inteiro com validação
int ler_inteiro(const char* mensagem) {
    int valor;
    while (1) {
        printf("%s", mensagem);
        if (scanf("%d", &valor) != 1) {
            printf(">> Valor inválido. Por favor, insira um número inteiro.\n");
            limpar_buffer();
        } else {
            limpar_buffer(); // Limpa o buffer após a leitura
            return valor;
        }
    }
}

// Função para ler um float com validação
float ler_float(const char* mensagem) {
    float valor;
    while (1) {
        printf("%s", mensagem);
        if (scanf("%f", &valor) != 1) {
            printf(">> Valor inválido. Por favor, insira um número decimal.\n");
            limpar_buffer();
        } else {
            limpar_buffer(); // Limpa o buffer após a leitura
            return valor;
        }
    }
}

// Função para formatar uma string (remove a quebra de linha)
void formatar_string(char* str, size_t tamanho) {
    str[strcspn(str, "\n")] = 0; // Remove a quebra de linha
}
