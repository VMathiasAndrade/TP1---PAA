#ifndef MAPA_H
#define MAPA_H

#include <stdbool.h>

typedef struct {
    int durabilidadeAtual; // D
    int retiraDurabilidade; // D'
    int adDurabilidade; // A
    int pecasColetadas;
    int pecasRestantes;
} Nave;

typedef struct{
    int altura, largura;
    int linhaAtual, colunaAtual;
    int total_pecas;
    char** grid;
    bool** visitados;
} Mapa;

Mapa* Criar_Mapa();
void Destruir_Mapa(Mapa* mapa);
bool Carregar_Mapa_Arquivo(const char* nome_arquivo, Mapa* mapa, Nave* nave);
int getAltura(const Mapa* mapa);
int getLargura(const Mapa* mapa);
char getElemento(const Mapa* mapa, int linha, int coluna);

#endif