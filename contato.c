#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "contato.h"
#include "tempo.h"

void exibirContato(Contato contatato)
{
    printf("NOME : %s\n", contatato.nome);
    printf("LOCAL DE TRAB. : %s\n", contatato.localTrab);
    printf("TEL. P/ CONTATO : %s\n", contatato.telefones[0].num);
    printf("ENDEREÇO COMPLETO : %s\n", contatato.endereco);
    printf("OBSERVAÇÃO : %s\n", contatato.observacao);
    printf("DATA DE NASC (dd/mm/aaaa) : %d/%d/%d\n", contatato.dataNasc.dd, contatato.dataNasc.mm, contatato.dataNasc.aa);
    printf("--\n\n");
}

void listaDeContatos() {

    FILE * arquivo;
    Contato contato;

    arquivo = fopen("regContato.bin", "rb");

    if(arquivo != NULL)
    {
        system("cls");
        printf("\tLISTA DE CONTATOS\n\n");
        printf("-------------------------\n");
        printf("NOME               TEL. PARA CONTATO\n");
        while(fread(&contato, sizeof(Contato), 1, arquivo))
        {
            printf("%s                %s  %s  %s\n", contato.nome, contato.telefones[0].num, contato.telefones[1].num, contato.telefones[2].num);
        }
    }

    fclose(arquivo);

    system("pause");
}

void aniversarianteDoMes() {

    int idade;
    FILE * arquivo;
    Contato contato;
    Data data = dataAtual();

    arquivo = fopen("regContato.bin", "rb");

    if(arquivo != NULL)
    {
        system("cls");
        printf("\tANIVERSARIANTES DO MÊS\n\n");
        printf("--------------------------------\n");
        printf("NOME                 DATA DE ANIVERSÁRIO        IDADE\n");
        while(fread(&contato, sizeof(Contato), 1, arquivo))
        {
            if(data.mm == contato.dataNasc.mm) {

                idade = data.aa - contato.dataNasc.aa;

                if(contato.dataNasc.dd >= data.dd)
                    idade++;

                printf("%s                %d/%d               %d\n", contato.nome, contato.dataNasc.dd, contato.dataNasc.mm, idade);
            }
        }
    }

    fclose(arquivo);

    printf("\n");
    system("pause");

}

int novaOperacao(char operacao[10])
{

    char novaOperacao;

    do
    {
        printf("NOVA %s (S/N) ? ", operacao);
        fflush(stdin);
        scanf("%c", &novaOperacao);

        if(novaOperacao == 'N' || novaOperacao == 'n')
        {
            return 0;
        }
        else if(novaOperacao == 'S' || novaOperacao == 's')
        {
            return 1;
        }
        else
        {
            printf("OPÇÃO INVÁLIDA! INFORME NOVAMENTE\n");
        }
    }
    while(1);
}

int confirmarOperacao(char operacao[10])
{

    char confirmar;

    do
    {
        printf("\nCONFIRMAR %s (S/N) ? ", operacao);
        fflush(stdin);
        scanf("%c", &confirmar);

        if(confirmar == 'N' || confirmar == 'n')
        {
            return 0;
        }
        else if(confirmar == 'S' || confirmar == 's')
        {
            return 1;
        }
        else
        {
            printf("OPÇÃO INVÁLIDA! INFORME NOVAMENTE\n");
        }
    }
    while(1);
}

Contato buscarContato(char telBusca[14])
{
    int busca, i;
    FILE * arquivo;
    Contato contato, contatoEncontrado;

    arquivo = fopen("regContato.bin", "rb");

    if(arquivo != NULL)
    {
        while(fread(&contato, sizeof(Contato), 1, arquivo))
        {
            for(i = 0; i < 3; i++) {
                busca = compararTelefone(telBusca, contato.telefones[i].num);
                if(busca)
                {
                    contatoEncontrado = contato;
                    break;
                }
            }

            if(busca) {
                break;
            }
        }
    }

    fclose(arquivo);

    return contatoEncontrado;
}

void inclusaoDeContato()
{

    int i, loop = 1;
    Contato contato, aux;

    while(loop)
    {
        system("cls");
        printf("\tINCLUSÃO DE CONTATO\n");

        do {
            printf("NOME : ");
            fflush(stdin);
            gets(contato.nome);

            if(contato.nome[0] == '\0') {
                printf("É NECESSÁRIO INFORMAR UM NOME! INFORME NOVAMENTE");
            } else {
                break;
            }
        }while(1);

        printf("LOCAL DE TRAB. : ");
        fflush(stdin);
        gets(contato.localTrab);

        for(i = 0; i < 3; i++)
        {
            printf("%d° TEL. P/ CONTATO: ", (i+1));
            fflush(stdin);
            gets(contato.telefones[i].num);

            if(contato.telefones[0].num[0] == '\0') {
                printf("É NECESSÁRIO TER PELO MENOS 1 NÚMERO DE TEL. CADASTRADO! INFORME UM NÚMERO\n");
                i--;
            } else if(validarTelefone(contato.telefones[i].num) != 1)
            {
                printf("TEL. INVÁLIDO! INFORME NOVAMENTE\n");
                i--;
            } else {
                aux = buscarContato(contato.telefones[i].num);

                if(aux.nome[0] == '\0') {
                    printf("TEL. JÁ ESTÁ CADASTRADO! INFORME UM NÚMERO NOVAMENTE\n");
                    i--;
                }
            }
        }

        printf("ENDEREÇO COMPLETO : ");
        fflush(stdin);
        gets(contato.endereco);

        printf("OBSERVAÇÃO : ");
        fflush(stdin);
        gets(contato.observacao);

        do
        {
            printf("DATA DE NASC (dd/mm/aaaa) : ");
            fflush(stdin);
            scanf("%d/%d/%d", &contato.dataNasc.dd, &contato.dataNasc.mm, &contato.dataNasc.aa);

            if(validarData(contato.dataNasc))
            {
                break;
            }
            else
            {
                printf("DATA INCORRETA! INFORME NOVAMENTE\n");
            }
        }
        while(1);

        FILE * arquivo = fopen("regContato.bin", "ab");
        fwrite(&contato, sizeof(Contato), 1, arquivo);
        fclose(arquivo);

        loop = novaOperacao("INCLUSÃO");
    }
}

void consultaDeContato()
{
    int loop;
    Contato contato;
    char telBusca[14];

    do
    {
        system("cls");

        printf("\tCONSULTA DE CONTATO\n");
        printf("TEL. : ");
        fflush(stdin);
        gets(telBusca);

        contato = buscarContato(telBusca);

        if(contato.nome[0] != '\0')
            exibirContato(contato);
        else
            printf("\nCONTATO NÃO ENCONTRADO\n");

        loop = novaOperacao("CONSULTA");

    }
    while(loop);
}

void excluir(char telBusca[14])
{

    int busca, i;
    Contato contato;
    FILE * arquivoReg = fopen("regContato.bin", "rb");
    FILE * arquivoTemp = fopen("regTempContato.bin", "ab");

    if(arquivoReg != NULL)
    {

        while(fread(&contato, sizeof(Contato), 1, arquivoReg))
        {
            for(i = 0; i < 3; i++)
            {
                busca = compararTelefone(contato.telefones[i].num, telBusca);

                if(busca)
                {
                    break;
                }
            }

            if(busca != 1)
            {
                fwrite(&contato, sizeof(Contato), 1, arquivoTemp);
            }
        }

        fclose(arquivoReg);
        fclose(arquivoTemp);

        remove("regContato.bin");
        rename("regTempContato.bin", "regContato.bin");
    }
}

void exclusaoDeContato()
{

    Contato contato;
    char telBusca[14];
    int confirmacao, loop;

    do
    {
        system("cls");
        printf("\tEXCLUSÃO DE CONTATO\n");

        printf("TEL. : ");
        fflush(stdin);
        gets(telBusca);

        contato = buscarContato(telBusca);

        if(contato.nome[0] != '\0')
        {
            exibirContato(contato);
            confirmacao = confirmarOperacao("EXCLUSÃO");

            if(confirmacao)
            {
                excluir(telBusca);
            }
        }
        else
            printf("\nCONTATO NÃO ENCONTRADO\n");

        loop = novaOperacao("EXCLUSÃO");

    }
    while(loop);
}

void alterar(Contato contato, char chave[14])
{

    int i, busca, opcao;
    Contato contatoArq;
    FILE * arquivoReg;
    FILE * arquivoTemp;

    system("cls");

    printf("\tALTERAR\n");
    printf("1 - NOME\n");
    printf("2 - LOCAL DE TRABALHO\n");
    printf("3 - TEL. 1\n");
    printf("4 - TEL. 2\n");
    printf("5 - TEL. 3\n");
    printf("6 - ENDEREÇO COMPLETO\n");
    printf("7 - OBSERVAÇÃO\n");
    printf("8 - DATA DE NASC.\n");
    printf("0 - VOLTAR\n");
    printf("\tOPÇÃO : ");

    fflush(stdin);
    scanf("%d", &opcao);

    fflush(stdin);

    switch(opcao)
    {
    case 0:
        break;
    case 1:
        printf("NOVO NOME : ");
        gets(contato.nome);
        break;
    case 2:
        printf("NOVO LOCAL DE TRABALHO : ");
        gets(contato.localTrab);
        break;
    case 3:
        do
        {
            printf("NOVO TEL.1 : ");
            gets(contato.telefones[0].num);

            if(validarTelefone(contato.telefones[0].num) != 0)
                printf("TEL. INVÁLIDO! INFORME NOVAMENTE\n");
            else
                break;
        }
        while(1);

        break;
    case 4:
        do
        {
            printf("NOVO TEL.2 : ");
            gets(contato.telefones[1].num);

            if(validarTelefone(contato.telefones[1].num) != 0)
                printf("TEL. INVÁLIDO! INFORME NOVAMENTE\n");
            else
                break;
        }
        while(1);

        break;
    case 5:
        do
        {
            printf("NOVO TEL.3 : ");
            gets(contato.telefones[2].num);

            if(validarTelefone(contato.telefones[2].num) != 0)
                printf("TEL. INVÁLIDO! INFORME NOVAMENTE\n");
            else
                break;
        }
        while(1);

        break;
    case 6:
        printf("NOVO ENDEREÇO COMPLETO : ");
        gets(contato.endereco);
        break;
    case 7:
        printf("NOVA OBSERVAÇÃO : ");
        gets(contato.observacao);
        break;
    case 8:
        do
        {
            printf("DATA DE NASC (dd/mm/aaaa) : ");
            fflush(stdin);
            scanf("%d/%d/%d", &contato.dataNasc.dd, &contato.dataNasc.mm, &contato.dataNasc.aa);

            if(validarData(contato.dataNasc))
            {
                break;
            }
            else
            {
                printf("DATA INCORRETA! INFORME NOVAMENTE\n");
            }
        }
        while(1);
    }

    if(opcao != 0 && confirmarOperacao("ALTERAÇÃO"))
    {

        arquivoReg = fopen("regContato.bin", "rb");
        arquivoTemp = fopen("regTempContato.bin", "ab");

        if(arquivoReg != NULL)
        {

            while(fread(&contatoArq, sizeof(Contato), 1, arquivoReg))
            {
                for(i = 0; i < 3; i++)
                {
                    busca = compararTelefone(contatoArq.telefones[i].num, chave);

                    if(busca)
                    {
                        break;
                    }
                }

                if(busca != 1)
                {
                    fwrite(&contatoArq, sizeof(Contato), 1, arquivoTemp);
                }
                else
                {
                    fwrite(&contato, sizeof(Contato), 1, arquivoTemp);
                }
            }

            fclose(arquivoReg);
            fclose(arquivoTemp);

            remove("regContato.bin");
            rename("regTempContato.bin", "regContato.bin");
        }
    }
}

void alteracaoDeContato()
{

    int loop;
    Contato contato;
    char telBusca[14];

    do
    {
        system("cls");

        printf("\tALTERAÇÃO DE CONTATO\n");
        printf("TEL. : ");
        fflush(stdin);
        gets(telBusca);

        contato = buscarContato(telBusca);

        if(contato.nome[0] != '\0')
        {
            exibirContato(contato);
            alterar(contato, telBusca);

        }
        else
            printf("\nCONTATO NÃO ENCONTRADO\n");

        loop = novaOperacao("ALTERAÇÃO");

    }
    while(loop);
}
