#ifndef TEMPO_H_INCLUDED
#define TEMPO_H_INCLUDED

typedef struct {
    int hh;
    int mm;
} Hora;

typedef struct {
    int dd;
    int mm;
    int aa;
} Data;

Data dataAtual();

int validarHora(Hora hora);
int validarData(Data data);
int compararData(Data dataA, Data dataB);
int compararHora(Hora horaA, Hora horaB);

#endif // TEMPO_H_INCLUDED
