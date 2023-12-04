#include <time.h>
#include <stdio.h>
#include "tempo.h"


Data dataAtual() {

    Data data;
    time_t segundos;
    struct tm * dataAtual;

    time(&segundos);
    dataAtual = localtime(&segundos);

    data.dd = dataAtual->tm_mday;
    data.mm = dataAtual->tm_mon+1;
    data.aa = dataAtual->tm_year+1900;

    return data;
}

int compararData(Data dataA, Data dataB) {
    int d = dataA.dd == dataB.dd;
    int m = dataA.mm == dataB.mm;
    int a = dataA.aa == dataB.aa;

    return d && m && a;
}

int compararHora(Hora horaA, Hora horaB) {
    int h = horaA.hh == horaB.hh;
    int m = horaA.mm == horaB.mm;

    return h && m;
}

int validarHora(Hora hora) {

    int validarHora = hora.hh >= 0 && hora.hh <= 23;
    int validarMin = hora.mm >= 0 && hora.mm <= 59;

    return validarHora && validarMin;
}

int validarData(Data data) {

    int verificarDia = (data.dd > 0 && data.dd <= 30);
    int verificarMes = (data.mm > 0 && data.mm <= 12);
    int verificarAno =  data.aa >= 1000;

    return verificarDia && verificarMes && verificarAno;
}
