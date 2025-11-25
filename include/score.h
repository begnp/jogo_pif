#ifndef SCORE_H
#define SCORE_H

#include <stdio.h>

typedef struct {
    char nome[20];
    float tempoSegundos;
} RunRecord;

void SalvarTempoRun(float segundos);

int CarregarTopTempos(RunRecord *records, int max);

void FormatarTempo(float segundos, char *buffer);

#endif