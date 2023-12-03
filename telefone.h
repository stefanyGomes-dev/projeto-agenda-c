#ifndef TELEFONE_H_INCLUDED
#define TELEFONE_H_INCLUDED


typedef struct {
    char num[14];
} Telefone;

int validarTelefone(char tel[14]);
int compararTelefone(char telA[14], char telB[14]);

#endif // TELEFONE_H_INCLUDED
