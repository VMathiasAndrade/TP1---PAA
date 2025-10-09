// estrutura apenas para interface do jogo
#ifndef JOGO_H
#define JOGO_H

#include <stdbool.h>
#include "mapa.h"

typedef struct caminhos {
    int posicaoCaminho[2];  
}caminhos;

typedef struct Jogo{
    Mapa* mapa_atual;
    Nave nave_atual;
    bool analise; // Indica se a análise detalhada está ativada
    caminhos* caminhosPossiveis;
} Jogo;

Jogo* Criar_Jogo();
void Destruir_Jogo(Jogo* jogo);
void Iniciar_Jogo(Jogo* jogo);
void movimentar(Jogo* jogo); 
bool caminhoValido(Jogo* jogo);
void imprimirPassos(int linha, int coluna, int durabilidade, int pecas_restantes);
void imprimirResultado(int status, int chamadas_recursivas, int max_recursao, bool analise);

#endif