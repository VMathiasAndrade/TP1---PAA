#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "Jogo.h"
#include "backtracking.h"

int movimentar(Jogo* jogo, int linha, int coluna, int profundidade_atual) {
    jogo->dados->chamadas_recursivas++;
    if (profundidade_atual > jogo->dados->max_recursao) {
        jogo->dados->max_recursao = profundidade_atual;
    }

    Mapa* mapa = jogo->mapa_atual;
    Nave* nave = jogo->nave_atual;

    int durabilidade_anterior = nave->durabilidadeAtual;
    int pecas_coletadas_anterior = nave->pecasColetadas;
    int pecas_restantes_anterior = nave->pecasRestantes;

    int inimigo_index = -1;
    StatusInimigo status_anterior_inimigo;

    for (int i = 0; i < jogo->num_inimigos; i++) {
        if (jogo->inimigos[i].linha == linha && jogo->inimigos[i].coluna == coluna) {
            if (jogo->inimigos[i].status == ATIVO) {
                inimigo_index = i;
                status_anterior_inimigo = jogo->inimigos[i].status;
                nave->durabilidadeAtual -= jogo->inimigos[i].dano;
                jogo->inimigos[i].status = DERROTADO;
            }
            break;
        }
    }

    if (nave->durabilidadeAtual <= 0) {
        if (mapa->grid[linha][coluna] != 'F') {
            if (inimigo_index != -1) {
                jogo->inimigos[inimigo_index].status = status_anterior_inimigo;
            }
            
            return 0;
        }
    }

    mapa->visitados[linha][coluna] = true;
    jogo->caminhoSolucao[jogo->tamanhoAtual][0] = linha;
    jogo->caminhoSolucao[jogo->tamanhoAtual][1] = coluna;
    jogo->caminhoSolucao[jogo->tamanhoAtual][2] = nave->durabilidadeAtual;
    jogo->caminhoSolucao[jogo->tamanhoAtual][3] = nave->pecasRestantes;
    jogo->tamanhoAtual++;

    if (mapa->grid[linha][coluna] == 'P') {
        nave->pecasColetadas++;
        nave->durabilidadeAtual += nave->adDurabilidade;
        nave->pecasRestantes--;
    }

    if (mapa->grid[linha][coluna] == 'F') {
        copiarCaminho(jogo);
        int status_final = (nave->pecasColetadas == mapa->total_pecas) ? 2 : 1;
        jogo->tamanhoAtual--;
        mapa->visitados[linha][coluna] = false;
        nave->durabilidadeAtual = durabilidade_anterior;
        nave->pecasColetadas = pecas_coletadas_anterior;
        nave->pecasRestantes = pecas_restantes_anterior;
        if (inimigo_index != -1) {
            jogo->inimigos[inimigo_index].status = status_anterior_inimigo;
        }
        return status_final;
    }

    int melhorStatus = 0;

    if (melhorStatus < 2 && movimentarDireita(linha, coluna, jogo)) {
        if (nave->pecasColetadas != mapa->total_pecas) {
            nave->durabilidadeAtual -= nave->retiraDurabilidade;
        }
        int status = movimentar(jogo, linha, coluna + 1, profundidade_atual + 1);
        if (status > melhorStatus) {
            melhorStatus = status;
        }
        if (nave->pecasColetadas != mapa->total_pecas) {
            nave->durabilidadeAtual += nave->retiraDurabilidade;
        }
    }
    if (melhorStatus < 2 && movimentarEsquerda(linha, coluna, jogo)) {
        if (nave->pecasColetadas != mapa->total_pecas) {
            nave->durabilidadeAtual -= nave->retiraDurabilidade;
        }
        int status = movimentar(jogo, linha, coluna - 1, profundidade_atual + 1);
        if (status > melhorStatus) {
            melhorStatus = status;
        }
        if (nave->pecasColetadas != mapa->total_pecas) {
            nave->durabilidadeAtual += nave->retiraDurabilidade;
        }
    }
    if (melhorStatus < 2 && movimentarCima(linha, coluna, jogo)) {
        if (nave->pecasColetadas != mapa->total_pecas) {
            nave->durabilidadeAtual -= nave->retiraDurabilidade;
        }
        int status = movimentar(jogo, linha - 1, coluna, profundidade_atual + 1);
        if (status > melhorStatus) {
            melhorStatus = status;
        }
        if (nave->pecasColetadas != mapa->total_pecas) {
            nave->durabilidadeAtual += nave->retiraDurabilidade;
        }
    }
    if (melhorStatus < 2 && movimentarBaixo(linha, coluna, jogo)) {
        if (nave->pecasColetadas != mapa->total_pecas) {
            nave->durabilidadeAtual -= nave->retiraDurabilidade;
        }
        int status = movimentar(jogo, linha + 1, coluna, profundidade_atual + 1);
        if (status > melhorStatus) {
            melhorStatus = status;
        }
        if (nave->pecasColetadas != mapa->total_pecas) {
            nave->durabilidadeAtual += nave->retiraDurabilidade;
        }
    }

    jogo->tamanhoAtual--;
    mapa->visitados[linha][coluna] = false;
    nave->durabilidadeAtual = durabilidade_anterior;
    nave->pecasColetadas = pecas_coletadas_anterior;
    nave->pecasRestantes = pecas_restantes_anterior;
    if (inimigo_index != -1) {
        jogo->inimigos[inimigo_index].status = status_anterior_inimigo;
    }

    return melhorStatus;
}

bool movimentarDireita(int linha, int coluna, Jogo* jogo) {

    char posAtual = jogo->mapa_atual->grid[linha][coluna];
    if (posAtual != '-' && posAtual != '+' && posAtual != 'X' && posAtual != 'P' && posAtual != 'I') {
        return false;
    }

    int proxColuna = coluna + 1;
    if (proxColuna >= jogo->mapa_atual->largura) {
        return false;
    }

    char posDestino = jogo->mapa_atual->grid[linha][proxColuna];
    if (posDestino == '.') {
        return false;
    }

    if (jogo->mapa_atual->visitados[linha][proxColuna]) {
        return false;
    }

    return true;
}

bool movimentarEsquerda(int linha, int coluna, Jogo* jogo) {

    char posAtual = jogo->mapa_atual->grid[linha][coluna];
    if (posAtual != '-' && posAtual != '+' && posAtual != 'X' && posAtual != 'P' && posAtual != 'I') {
        return false;
    }

    int proxColuna = coluna - 1;
    if (proxColuna < 0) {
        return false;
    }

    char posDestino = jogo->mapa_atual->grid[linha][proxColuna];
    if (posDestino == '.') {
        return false;
    }

    if (jogo->mapa_atual->visitados[linha][proxColuna]) {
        return false;
    }

    return true;
}

bool movimentarCima(int linha, int coluna, Jogo* jogo) {

    char posAtual = jogo->mapa_atual->grid[linha][coluna];
    if (posAtual != '|' && posAtual != '+' && posAtual != 'X' && posAtual != 'P' && posAtual != 'I') {
        return false;
    }

    int proxLinha = linha - 1;
    if (proxLinha < 0) {
        return false;
    }

    char posDestino = jogo->mapa_atual->grid[proxLinha][coluna];
    if (posDestino == '.') {
        return false;
    }

    if (jogo->mapa_atual->visitados[proxLinha][coluna]) {
        return false;
    }

    return true;
}


bool movimentarBaixo(int linha, int coluna, Jogo* jogo) {

    char posAtual = jogo->mapa_atual->grid[linha][coluna];
    if (posAtual != '|' && posAtual != '+' && posAtual != 'X' && posAtual != 'P' && posAtual != 'I') {
        return false;
    }

    int proxLinha = linha + 1;
    if (proxLinha >= jogo->mapa_atual->altura) {
        return false;
    }

    char posDestino = jogo->mapa_atual->grid[proxLinha][coluna];
    if (posDestino == '.') {
        return false;
    }

    if (jogo->mapa_atual->visitados[proxLinha][coluna]) {
        return false;
    }

    return true;
}