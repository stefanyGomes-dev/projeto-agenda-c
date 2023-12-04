#include <string.h>
#include "telefone.h"

int compararTelefone(char telA[10], char telB[10]) {
    int comparacao;

    comparacao = strcmp(telA, telB);

    if(comparacao == 0)
        return 1;
    else
        return 0;
}

int validarTelefone(char tel[10]) {
    int i;
    int tamanho = strlen(tel);

    if(tamanho < 10)
        return 0;

    for(i = 0; i < tamanho; i++) {
        if(!(tel[i] >= 48 && tel[i] <= 57) || tel[i] == 45)
            return 0;
    }

    return 1;
}
