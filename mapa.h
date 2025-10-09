#ifndef MAPA_H
#define MAPA_H

#include <stdbool.h>

typedef struct {
    int durabilidade_inicial; // D
    int durabilidade_decr; // D'
    int durabilidade_acr; // A
} Nave;

typedef struct{
    int altura;
    int largura;
    char **grid;
    int linha_inicial;
    int coluna_inicial;
    int total_pecas;
} Mapa;

Mapa* Criar_Mapa();
void Destruir_Mapa(Mapa* mapa);
bool Carregar_Mapa_Arquivo(const char* nome_arquivo, Mapa* mapa, Nave* nave);


int getAltura(const Mapa* mapa);
int getLargura(const Mapa* mapa);
char getElemento(const Mapa* mapa, int linha, int coluna);

#endif