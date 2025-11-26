#ifndef SCORE_H
#define SCORE_H

#include <stdio.h>


typedef struct ScoreNode {
    char nome[20];
    float tempo;
    struct ScoreNode *next; 
} ScoreNode;


void SalvarTempoRun(float segundos);


ScoreNode* CarregarListaScores();

void LiberarLista(ScoreNode *head);


void FormatarTempo(float segundos, char *buffer);

#endif