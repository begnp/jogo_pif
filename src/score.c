#include "score.h"
#include <stdlib.h>
#include <string.h>

#define ARQUIVO_SCORE "leaderboard.txt"

void SalvarTempoRun(float segundos) {
    FILE *file = fopen(ARQUIVO_SCORE, "a");
    if (file == NULL) {
        return;
    }
    fprintf(file, "Player %.2f\n", segundos);
    
    fclose(file);
}

int CarregarTopTempos(RunRecord *records, int max) {
    FILE *file = fopen(ARQUIVO_SCORE, "r");
    if (file == NULL) return 0;

    int count = 0;
    
    RunRecord buffer[100]; 
    int totalLido = 0;

    while (totalLido < 100 && fscanf(file, "%s %f", buffer[totalLido].nome, &buffer[totalLido].tempoSegundos) == 2) {
        totalLido++;
    }
    fclose(file);

    for (int i = 0; i < totalLido - 1; i++) {
        for (int j = 0; j < totalLido - i - 1; j++) {
            if (buffer[j].tempoSegundos < buffer[j+1].tempoSegundos) {
                RunRecord temp = buffer[j];
                buffer[j] = buffer[j+1];
                buffer[j+1] = temp;
            }
        }
    }

    int limite = (totalLido > max) ? max : totalLido;
    for (int i = 0; i < limite; i++) {
        records[i] = buffer[i];
    }

    return limite;
}

void FormatarTempo(float segundos, char *buffer) {
    int min = (int)segundos / 60;
    int sec = (int)segundos % 60;
    sprintf(buffer, "%02d:%02ds", min, sec);
}