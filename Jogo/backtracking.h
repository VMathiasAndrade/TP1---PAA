#ifndef BACKTRACKING_H
#define BACKTRACKING_H

struct Jogo;
struct Mapa;

int movimentar(Jogo* jogo, int linha, int coluna, int profundidade_atual);

bool movimentarDireita(int linha, int coluna, Mapa* mapa);
bool movimentarEsquerda(int linha, int coluna, Mapa* mapa);
bool movimentarCima(int linha, int coluna, Mapa* mapa);
bool movimentarBaixo(int linha, int coluna, Mapa* mapa);

#endif
