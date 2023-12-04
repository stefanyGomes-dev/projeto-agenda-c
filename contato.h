#ifndef CONTATO_H_INCLUDED
#define CONTATO_H_INCLUDED

#include "tempo.h"
#include "telefone.h"

typedef struct {
    char nome[50];
    char localTrab[100];
    Telefone telefones[3];
    char endereco[100];
    char observacao[100];
    Data dataNasc;
} Contato;

int confirmarOperacao();
int novaOperacao();
void listaDeContatos();
void aniversarianteDoMes();
void inclusaoDeContato();
void alteracaoDeContato();
void consultaDeContato();
void exclusaoDeContato();
void exibirContato(Contato contato);

#endif // CONTATO_H_INCLUDED
