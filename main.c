#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

#include "contato.h"
#include "compromisso.h"

void menuContato()
{
    int opcao, loop = 1;

    while(loop)
    {
        printf("\tCADASTRO DE CONTATOS\n");
        printf("1 - INCLUSÃO\n");
        printf("2 - ALTERAÇÃO\n");
        printf("3 - CONSULTA\n");
        printf("4 - EXCLUSÃO\n");
        printf("0 - RETORNAR\n");
        printf("\tOPCAO : ");

        scanf("%d", &opcao);

        system("cls");

        switch(opcao)
        {
        case 0:
            loop = 0;
            break;
        case 1:
            inclusaoDeContato();
            break;
        case 2:
            alteracaoDeContato();
            break;
        case 3:
            consultaDeContato();
            break;
        case 4:
            exclusaoDeContato();
            break;
        }

        system("cls");
    }
}

void menuCompromisso() {
    int opcao, loop = 1;

    while(loop)
    {
        printf("\tCADASTRO DE COMPROMISSOS\n");
        printf("1 - INCLUSÃO\n");
        printf("2 - ALTERAÇÃO\n");
        printf("3 - CONSULTA\n");
        printf("4 - EXCLUSÃO\n");
        printf("0 - RETORNAR\n");
        printf("\tOPCAO : ");

        scanf("%d", &opcao);

        system("cls");

        switch(opcao)
        {
        case 0:
            loop = 0;
            break;
        case 1:
            inclusaoDeCompromisso();
            break;
        case 2:
            alteracaoDeCompromisso();
            break;
        case 3:
            consultaDeCompromisso();
            break;
        case 4:
            exclusaoDeCompromisso();
            break;
        }

        system("cls");
    }
}

void menuPrincipal()
{
    int opcao;
    int loop = 1;

    while(loop)
    {

        printf("\tMENU PRINCIPAL\n\n");
        printf("1 - CADASTRO DE CONTATOS\n");
        printf("2 - CADASTRO DE COMPROMISSOS\n");
        printf("3 - COMPROMISSOS DO DIA\n");
        printf("4 - LISTA DE CONTATOS\n");
        printf("5 - ANIVERSARIANTES DO MÊS\n");
        printf("0 - FINALIZAR\n");
        printf("\tOPCAO: ");

        scanf("%d", &opcao);

        system("cls");

        switch(opcao)
        {
        case 0:
            loop = 0;
            break;
        case 1:
            menuContato();
            break;
        case 2:
            menuCompromisso();
            break;
        case 3:
            compromissosDoDia();
            break;
        case 4:
            listaDeContatos();
            break;
        case 5:
            aniversarianteDoMes();
            break;
        }

        system("cls");
    }
}

int main()
{
    setlocale(LC_ALL, "Portuguese_Brazil");
    menuPrincipal();
    return 0;
}
