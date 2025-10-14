#ifndef BACKTRACKING_H
#define BACKTRACKING_H

struct Jogo;
struct Mapa;

int movimentar(Jogo* jogo, int linha, int coluna, int profundidade_atual);

bool movimentarDireita(int linha, int coluna, Jogo* jogo);
bool movimentarEsquerda(int linha, int coluna, Jogo* jogo);
bool movimentarCima(int linha, int coluna, Jogo* jogo);
bool movimentarBaixo(int linha, int coluna, Jogo* jogo);

#endif
