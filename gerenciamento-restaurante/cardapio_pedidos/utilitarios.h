#ifndef UTILITARIOS_H
#define UTILITARIOS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Funções utilitárias
void limpar_buffer();
int ler_inteiro(const char* mensagem);
float ler_float(const char* mensagem);
void formatar_string(char* str, size_t tamanho);

#endif // UTILITARIOS_H
