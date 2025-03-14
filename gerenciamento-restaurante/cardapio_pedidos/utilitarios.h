#ifndef UTILITARIOS_H
#define UTILITARIOS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Função para limpar o buffer de entrada
void limpar_buffer();

// Função para ler um inteiro com validação
int ler_inteiro(const char* mensagem);

// Função para ler um float com validação
float ler_float(const char* mensagem);

// Função para formatar uma string (remove a quebra de linha)
void formatar_string(char* str, size_t tamanho);

#endif // UTILITARIOS_H
