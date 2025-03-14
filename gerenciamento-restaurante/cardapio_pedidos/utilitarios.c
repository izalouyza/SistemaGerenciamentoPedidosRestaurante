#include <stdio.h>      // Para funções de entrada e saída
#include <stdlib.h>     // Para funções de alocação de memória (se necessário)
#include "utilitarios.h" // Para a declaração da função limpar_buffer

void limpar_buffer() {
    while(getchar() != '\n'); // Limpa o buffer até encontrar uma nova linha
}
