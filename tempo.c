#include <time.h>

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

int validarData(Data data) {

    int verificarDia = (data.dd > 0 && data.dd <= 30);
    int verificarMes = (data.mm > 0 && data.mm <= 12);
    int verificarAno =  data.aa >= 1000;

    return verificarDia && verificarMes && verificarAno;
}
