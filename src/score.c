#include "score.h"
#include <stdlib.h>
#include <string.h>

#define ARQUIVO_SCORE "leaderboard.txt"

ScoreNode* CriarNo(char* nome, float tempo) {
    ScoreNode* novo = (ScoreNode*) malloc(sizeof(ScoreNode));
    if (novo) {
        strcpy(novo->nome, nome);
        novo->tempo = tempo;
        novo->next = NULL;
    }
    return novo;
}

ScoreNode* InserirOrdenado(ScoreNode* head, ScoreNode* novo) {
    if (head == NULL || novo->tempo > head->tempo) {
        novo->next = head;
        return novo; 
    }


    ScoreNode* atual = head;
    while (atual->next != NULL && atual->next->tempo >= novo->tempo) {
        atual = atual->next;
    }

    novo->next = atual->next;
    atual->next = novo;

    return head; 
}

void SalvarTempoRun(float segundos) {
    FILE *file = fopen(ARQUIVO_SCORE, "a");
    if (file == NULL){
        return;
    } 

    fprintf(file, "Player %.2f\n", segundos);
    fclose(file);
}

ScoreNode* CarregarListaScores() {
    FILE *file = fopen(ARQUIVO_SCORE, "r");
    if (file == NULL){
        return NULL;
    } 

    ScoreNode *head = NULL;
    char nomeTemp[20];
    float tempoTemp;

    while (fscanf(file, "%s %f", nomeTemp, &tempoTemp) == 2) {
        ScoreNode* novoNo = CriarNo(nomeTemp, tempoTemp);
        
        if (novoNo) {
            head = InserirOrdenado(head, novoNo);
        }
    }
    
    fclose(file);
    return head; 
}

void LiberarLista(ScoreNode *head) {
    ScoreNode *atual = head;
    while (atual != NULL) {
        ScoreNode *temp = atual;
        atual = atual->next; 
        free(temp);          
    }
}

void FormatarTempo(float segundos, char *buffer) {
    int min = (int)segundos / 60;
    int sec = (int)segundos % 60;
    sprintf(buffer, "%02d:%02ds", min, sec);
}