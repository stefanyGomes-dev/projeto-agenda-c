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
int colisaoDeHorario(Data data, Hora hora);

#endif // TEMPO_H_INCLUDED
