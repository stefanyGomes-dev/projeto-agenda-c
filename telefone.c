#include <string.h>
#include "telefone.h"

int compararTelefone(char telA[14], char telB[14]) {
    int comparacao;

    comparacao = strcmp(telA, telB);

    if(comparacao == 0)
        return 1;
    else
        return 0;
}

int validarTelefone(char tel[14]) {
    int i;
    int tamanho = strlen(tel);

    for(i = 0; i < tamanho; i++) {
        if(!(tel[i] >= 48 && tel[i] <= 57))
            return 0;
    }

    return 1;
}
