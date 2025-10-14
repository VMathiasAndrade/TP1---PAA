// estrutura apenas para interface do jogo
#ifndef JOGO_H
#define JOGO_H

#include <stdbool.h>
#include "mapa.h"

typedef enum {
    ATIVO,
    DERROTADO
} StatusInimigo;

typedef struct {
    int linha;
    int coluna;
    int dano;
    StatusInimigo status;
} Inimigo;

typedef struct Dados {
    int chamadas_recursivas;
    int max_recursao;
}Dados;


typedef struct Jogo {
    Mapa* mapa_atual;
    Nave* nave_atual;
    Dados* dados;
    int** caminhoSolucao;
    int** caminhoFinal;
    int tamanhoAtual;
    int tamanhoFinal;

    Inimigo* inimigos;
    int num_inimigos;
} Jogo;

Jogo* Criar_Jogo();
void Destruir_Jogo(Jogo* jogo);
void Iniciar_Jogo(Jogo* jogo);
void imprimirResultado(Jogo* jogo, int status, char analise);
void copiarCaminho(Jogo* jogo);

#endif