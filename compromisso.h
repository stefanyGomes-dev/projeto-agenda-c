#ifndef COMPROMISSO_H_INCLUDED
#define COMPROMISSO_H_INCLUDED

#include "tempo.h"

typedef struct {
    Data dInicio;
    Hora hInicio;
    Hora hTermino;
    char descricao[150];
    char local[100];
    char obs[100];
} Compromisso;

void compromissosDoDia();
void inclusaoDeCompromisso();
void consultaDeCompromisso();
void exclusaoDeCompromisso();
void alteracaoDeCompromisso();

#endif // COMPROMISSO_H_INCLUDED
