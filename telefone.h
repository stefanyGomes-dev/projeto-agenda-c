#ifndef TELEFONE_H_INCLUDED
#define TELEFONE_H_INCLUDED


typedef struct {
    char num[10];
} Telefone;

int validarTelefone(char tel[10]);
int compararTelefone(char telA[10], char telB[10]);

#endif // TELEFONE_H_INCLUDED
