#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "compromisso.h"
#include "contato.h"
#include "tempo.h"

void exibirCompromisso(Compromisso comp)
{
    printf("DATA INICIO (dd/mm/aaaa) : %02d/%02d/%04d\n", comp.dInicio.dd, comp.dInicio.mm, comp.dInicio.aa);
    printf("HORA INICIO (hh:mm) : %02d:%02d\n", comp.hInicio.hh, comp.hInicio.mm);
    printf("HORA TÉRMINO (hh:mm) : %02d:%02d\n", comp.hTermino.hh, comp.hTermino.mm);
    printf("DESCRIÇÃO : %s\n", comp.descricao);
    printf("LOCAL : %s\n", comp.descricao);
    printf("OBSERVAÇÃO : %s\n", comp.obs);
    printf("--\n\n");
}

void compromissosDoDia() {

    int contador = 0;
    FILE * arquivo;
    Compromisso comp;
    Data data = dataAtual();

    arquivo = fopen("regCompromisso.bin", "rb");

    system("cls");
    printf("\tCOMPROMISSOS DO DIA %02d/%02d/%04d\n\n", data.dd, data.mm, data.aa);
    printf("----------------------------------------------------------\n");
    printf("HORA   DESCRIÇÃO            LOCAL               OBSERVAÇÃO\n");

    if(arquivo != NULL)
    {
        while(fread(&comp, sizeof(Compromisso), 1, arquivo))
        {
            if(compararData(comp.dInicio, data)) {
                contador++;
                printf("%02d:%02d  %s                %s               %s\n", comp.hInicio.hh, comp.hInicio.mm, comp.descricao, comp.local, comp.obs);
            }
        }
    }

    if(contador == 0)
        printf("\n\n\tNENHUM COMPROMISSO REGISTRADO PARA HOJE\n");

    fclose(arquivo);

    printf("\n");
    system("pause");
}

Compromisso buscarCompromisso(Data data, Hora horaI, Hora horaT) {
    int busca;
    FILE * arquivo;
    Compromisso comp, compEncontrado;

    arquivo = fopen("regCompromisso.bin", "rb");

    if(arquivo != NULL)
    {
        while(fread(&comp, sizeof(Compromisso), 1, arquivo))
        {
            busca = compararData(data, comp.dInicio) && compararHora(horaI, comp.hInicio) && compararHora(horaT, comp.hTermino);

            if(busca) {
                compEncontrado = comp;
                break;
            }
        }
    }

    fclose(arquivo);

    return compEncontrado;
}

int colisaoCompromisso(Data data, Hora inicio, Hora fim) {

    FILE * arquivo;
    Compromisso comp;
    int busca, retorno, tempoInicialA, tempoInicialB, tempoFinalA, tempoFinalB;

    arquivo = fopen("regCompromisso.bin", "rb");

    if(arquivo != NULL)
    {
        tempoInicialA = inicio.hh * 60 + inicio.mm;
        tempoFinalA = fim.hh * 60 + fim.mm;


        if(tempoFinalA <= tempoInicialA) {
            if(data.dd < 30) {
                data.dd += 1;
            } else {
                data.dd = 1;

                if(data.mm < 12)
                    data.mm += 1;
                else {
                    data.mm = 1;
                    data.aa += 1;
                }
            }
        }

        while(fread(&comp, sizeof(Compromisso), 1, arquivo))
        {
            busca = compararData(data, comp.dInicio);

            if(busca) {

                tempoInicialB = comp.hInicio.hh * 60 + comp.hInicio.mm;
                tempoFinalB = comp.hTermino.hh * 60 + comp.hTermino.mm;

                if(tempoInicialA <= tempoInicialB && (tempoFinalA >= tempoInicialB && tempoFinalA <= tempoFinalB)) {
                    retorno = 1;
                    break;
                }

                if(tempoInicialA >= tempoInicialB && tempoInicialA <= tempoFinalB) {
                    retorno = 1;
                    break;
                }

                if(tempoFinalA >= tempoInicialB && tempoFinalA <= tempoFinalB) {
                    retorno = 1;
                    break;
                }
            }
        }
    }

    fclose(arquivo);

    return retorno;

}

void inclusaoDeCompromisso()
{
    FILE * arquivo;
    Compromisso comp;
    int colisao, confirmacao, loop = 1;

    while(loop) {
        system("cls");
        printf("\tINCLUSÃO DE COMPROMISSO\n");

        do {
            do {
                printf("DATA INICIO (dd/mm/aaaa): ");
                fflush(stdin);
                scanf("%d/%d/%d", &comp.dInicio.dd, &comp.dInicio.mm, &comp.dInicio.aa);

                if(validarData(comp.dInicio) != 1) {
                    printf("DATA INVÁLIDA! INFOMRE NOVAMENTE\n");
                } else {
                    break;
                }
            } while(1);

            do {
                printf("HORA INICIO (hh:mm) : ");
                fflush(stdin);
                scanf("%d:%d", &comp.hInicio.hh, &comp.hInicio.mm);

                if(validarHora(comp.hInicio) != 1) {
                    printf("HORA INVÁLIDA! INFORME NOVAMENTE\n");
                } else {
                    break;
                }
            } while(1);

            do {
                printf("HORA TÉRMINO (hh:mm) : ");
                fflush(stdin);
                scanf("%d:%d", &comp.hTermino.hh, &comp.hTermino.mm);

                if(validarHora(comp.hInicio) != 1) {
                    printf("HORA INVÁLIDA! INFORME NOVAMENTE\n");
                } else {
                    break;
                }
            } while(1);

            arquivo = fopen("regCompromisso.bin", "rb");

            if(arquivo == NULL) {
                colisao = 0;
            } else {
                colisao = colisaoCompromisso(comp.dInicio, comp.hInicio, comp.hTermino);

                if(colisao) {
                     printf("COLISÃO DE COMPROMISSO! INFORME UM OUTRO HORÁRIO E TENTE NOVAMENTE!\n");
                }
            }

            fclose(arquivo);
        } while(colisao);

        printf("DESCRIÇÃO : ");
        fflush(stdin);
        gets(comp.descricao);

        printf("LOCAL : ");
        fflush(stdin);
        gets(comp.local);

        printf("OBSERVAÇÃO : ");
        fflush(stdin);
        gets(comp.obs);

        confirmacao = confirmarOperacao("INCLUSÃO");

        if(confirmacao) {
            arquivo = fopen("regCompromisso.bin", "ab");
            fwrite(&comp, sizeof(Compromisso), 1, arquivo);
            fclose(arquivo);
        }

        loop = novaOperacao("INCLUSÃO");
    }
}

void consultaDeCompromisso() {
    int loop;
    Data data;
    Hora horaI, horaT;
    Compromisso comp;

    do
    {
        system("cls");
        printf("\tCONSULTA DE COMPROMISSO\n");

        do {
            printf("DATA INICIO (dd/mm/aaaa): ");
            fflush(stdin);
            scanf("%d/%d/%d", &data.dd, &data.mm, &data.aa);

            if(validarData(data) != 1) {
                printf("DATA INVÁLIDA! INFOMRE NOVAMENTE\n");
            } else {
                break;
            }
        } while(1);

        do {
            printf("HORA INICIO (hh:mm) : ");
            fflush(stdin);
            scanf("%d:%d", &horaI.hh, &horaI.mm);

            if(validarHora(horaI) != 1) {
                printf("HORA INVÁLIDA! INFORME NOVAMENTE\n");
            } else {
                break;
            }
        } while(1);

        do {
            printf("HORA TÉRMINO (hh:mm) : ");
            fflush(stdin);
            scanf("%d:%d", &horaT.hh, &horaT.mm);

            if(validarHora(horaT) != 1) {
                printf("HORA INVÁLIDA! INFORME NOVAMENTE\n");
            } else {
                break;
            }
        } while(1);

        comp = buscarCompromisso(data, horaI, horaT);

        if(validarData(comp.dInicio)) {
            system("cls");
            printf("\tCONSULTA DE COMPROMISSO\n");
            exibirCompromisso(comp);
        } else
            printf("\nCOMPROMISSO NÃO ENCONTRADO\n");

        loop = novaOperacao("CONSULTA");

    }
    while(loop);
}

void excluirCompReg(Data data, Hora horaI, Hora horaT)
{

    int busca;
    Compromisso comp;
    FILE * arquivoReg = fopen("regCompromisso.bin", "rb");
    FILE * arquivoTemp = fopen("regTempCompromisso.bin", "ab");

    if(arquivoReg != NULL)
    {

        while(fread(&comp, sizeof(Compromisso), 1, arquivoReg))
        {
            busca = compararData(data, comp.dInicio) && compararHora(horaI, comp.hInicio) && compararHora(horaT, comp.hTermino);

            if(busca != 1)
            {
                fwrite(&comp, sizeof(Compromisso), 1, arquivoTemp);
            }
        }

        fclose(arquivoReg);
        fclose(arquivoTemp);

        remove("regCompromisso.bin");
        rename("regTempCompromisso.bin", "regCompromisso.bin");
    }
}

void exclusaoDeCompromisso() {
    int loop;
    Data data;
    Hora horaI, horaT;
    Compromisso comp;

    do
    {
        system("cls");
        printf("\tEXCLUSÃO DE COMPROMISSO\n");

        do {
            printf("DATA INICIO (dd/mm/aaaa) : ");
            fflush(stdin);
            scanf("%d/%d/%d", &data.dd, &data.mm, &data.aa);

            if(validarData(data) != 1) {
                printf("DATA INVÁLIDA! INFOMRE NOVAMENTE\n");
            } else {
                break;
            }
        } while(1);

        do {
            printf("HORA INICIO (hh:mm) : ");
            fflush(stdin);
            scanf("%d:%d", &horaI.hh, &horaI.mm);

            if(validarHora(horaI) != 1) {
                printf("HORA INVÁLIDA! INFORME NOVAMENTE\n");
            } else {
                break;
            }
        } while(1);

        do {
            printf("HORA TÉRMINO (hh:mm) : ");
            fflush(stdin);
            scanf("%d:%d", &horaT.hh, &horaT.mm);

            if(validarHora(horaT) != 1) {
                printf("HORA INVÁLIDA! INFORME NOVAMENTE\n");
            } else {
                break;
            }
        } while(1);

        comp = buscarCompromisso(data, horaI, horaT);

        if(validarData(comp.dInicio)) {
            system("cls");
            exibirCompromisso(comp);
            if(confirmarOperacao("EXCLUSÃO")) {
                excluirCompReg(data, horaI, horaT);
            }
        }
        else
            printf("\nCOMPROMISSO NÃO ENCONTRADO\n");

        loop = novaOperacao("EXCLUSÃO");

    }
    while(loop);
}

void alterarCompromisso(Compromisso comp) {

    int busca, opcao, colisao;
    Compromisso compAux;
    FILE * arquivoReg;
    FILE * arquivoTemp;

    system("cls");

    printf("\tALTERAR\n");
    printf("1 - DATA INICIO\n");
    printf("2 - HORA INICIO\n");
    printf("3 - HORA TÉRMINO\n");
    printf("4 - DESCRIÇÃO\n");
    printf("5 - LOCAL\n");
    printf("6 - OBSERVAÇÃO\n");
    printf("0 - VOLTAR\n");
    printf("\tOPÇÃO : ");

    fflush(stdin);
    scanf("%d", &opcao);

    printf("\n");
    switch(opcao) {
        case 0:
            break;
        case 1:
            do {
                printf("DATA INICIO (dd/mm/aaaa): ");
                fflush(stdin);
                scanf("%d/%d/%d", &comp.dInicio.dd, &comp.dInicio.mm, &comp.dInicio.aa);

                if(validarData(comp.dInicio) != 1) {
                    printf("DATA INVÁLIDA! INFOMRE NOVAMENTE\n");
                }
                else {
                    break;
                }
            } while(1);
            break;
        case 2:
            do {
                printf("HORA INICIO (hh:mm) : ");
                fflush(stdin);
                scanf("%d:%d", &comp.hInicio.hh, &comp.hInicio.mm);

                if(validarHora(comp.hInicio) != 1) {
                    printf("HORA INVÁLIDA! INFORME NOVAMENTE\n");
                } else {
                    break;
                }
            } while(1);
            break;
        case 3:
            do {
                printf("HORA TÉRMINO (hh:mm) : ");
                fflush(stdin);
                scanf("%d:%d", &comp.hTermino.hh, &comp.hTermino.mm);

                if(validarHora(comp.hInicio) != 1) {
                    printf("HORA INVÁLIDA! INFORME NOVAMENTE\n");
                } else {
                    break;
                }
            } while(1);
            break;
        case 4:
            printf("DESCRIÇÃO : ");
            fflush(stdin);
            gets(comp.descricao);
            break;
        case 5:
            printf("LOCAL : ");
            fflush(stdin);
            gets(comp.local);
            break;
        case 6:
            printf("OBSERVAÇÃO : ");
            fflush(stdin);
            gets(comp.obs);
            break;
    }

    if(opcao != 0 && confirmarOperacao("ALTERAÇÃO")) {

        colisao = colisaoCompromisso(comp.dInicio, comp.hInicio, comp.hTermino);

        if(colisao) {
            printf("COLISÃO DE HORÁRIOS! INFORME UM OUTRO HORÁRIO E TENTE NOVAMENTE!\n");
        } else {
            arquivoReg = fopen("regCompromisso.bin", "rb");
            arquivoTemp = fopen("regTempCompromisso.bin", "ab");

            if(arquivoReg != NULL)
            {

                while(fread(&compAux, sizeof(Compromisso), 1, arquivoReg))
                {
                    busca = compararData(comp.dInicio, compAux.dInicio) && compararHora(comp.hInicio, compAux.hInicio) && compararHora(comp.hTermino, compAux.hTermino);

                    if(busca != 1)
                    {
                        fwrite(&compAux, sizeof(Compromisso), 1, arquivoTemp);
                    } else {
                        fwrite(&comp, sizeof(Compromisso), 1, arquivoTemp);
                    }
                }

                fclose(arquivoReg);
                fclose(arquivoTemp);

                remove("regCompromisso.bin");
                rename("regTempCompromisso.bin", "regCompromisso.bin");
            }
        }
    }
}

void alteracaoDeCompromisso() {
    int loop;
    Data data;
    Hora horaI, horaT;
    Compromisso comp;

    do
    {
        system("cls");
        printf("\tALTERAÇÃO DE COMPROMISSO\n");

        do {
            printf("DATA INICIO (dd/mm/aaaa) : ");
            fflush(stdin);
            scanf("%d/%d/%d", &data.dd, &data.mm, &data.aa);

            if(validarData(data) != 1) {
                printf("DATA INVÁLIDA! INFOMRE NOVAMENTE\n");
            } else {
                break;
            }
        } while(1);

        do {
            printf("HORA INICIO (hh:mm) : ");
            fflush(stdin);
            scanf("%d:%d", &horaI.hh, &horaI.mm);

            if(validarHora(horaI) != 1) {
                printf("HORA INVÁLIDA! INFORME NOVAMENTE\n");
            } else {
                break;
            }
        } while(1);

        do {
            printf("HORA TÉRMINO (hh:mm) : ");
            fflush(stdin);
            scanf("%d:%d", &horaT.hh, &horaT.mm);

            if(validarHora(horaT) != 1) {
                printf("HORA INVÁLIDA! INFORME NOVAMENTE\n");
            } else {
                break;
            }
        } while(1);

        comp = buscarCompromisso(data, horaI, horaT);

        if(validarData(comp.dInicio)) {
            system("cls");
            exibirCompromisso(comp);
            system("pause");
            alterarCompromisso(comp);
        }
        else
            printf("\nCOMPROMISSO NÃO ENCONTRADO\n");

        loop = novaOperacao("ALTERAÇÃO");

    }
    while(loop);
}
