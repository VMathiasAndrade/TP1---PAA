// estrutura apenas para interface do jogo
#ifndef JOGO_H
#define JOGO_H

#include <stdbool.h>
#include "mapa.h"
#include "backtracking.h"

typedef struct Jogo {
    Mapa* mapa_atual;
    Nave nave_atual;
    bool analise; // Indica se a análise detalhada está ativada
    int chamadas_recursivas;
    int max_recursao;
    int** caminhoSolucao;
    int tamanho_caminho
} Jogo;

Jogo* Criar_Jogo();
void Destruir_Jogo(Jogo* jogo);
void Iniciar_Jogo(Jogo* jogo);
void imprimirPassos(Mapa* mapa, Nave* nave);
void imprimirResultado(int status, int chamadas_recursivas, int max_recursao, bool analise);

#endif