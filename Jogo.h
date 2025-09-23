// estrutura apenas para interface do jogo


#ifndef JOGO_H
#define JOGO_H

#include <stdbool.h>

typedef struct Jogo Jogo;

Jogo* Criar_Jogo();
void Destruir_Jogo(Jogo* jogo);
void Iniciar_Jogo(Jogo* jogo);
void imprimirPassos(int linha, int coluna, int durabilidade, int pecas_restantes);
void imprimirResultado(int status, int chamadas_recursivas, int max_recursao, bool analise);


#endif // JOGO_H