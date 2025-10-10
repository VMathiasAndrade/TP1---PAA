#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "backtracking.h"

bool movimentar(Jogo* jogo, int linha, int coluna, int profundidade_atual) {
    jogo->chamadas_recursivas++;

    if (profundidade_atual > jogo->max_recursao) {
        jogo->max_recursao = profundidade_atual;
    }
    
    Mapa* mapa = jogo->mapa_atual;
    Nave* nave = &(jogo->nave_atual);

    if (nave->durabilidadeAtual <= 0) {
        return false;
    }

    jogo->caminhoSolucao[jogo->tamanho_caminho][0] = linha;
    jogo->caminhoSolucao[jogo->tamanho_caminho][1] = coluna;
    jogo->tamanho_caminho++;

    if (mapa->grid[linha][coluna] == 'F') {
        for (int i = 0; i < jogo->tamanho_caminho; i++) {
            printf("Linha: %d, Coluna: %d; D: %d, pecas restantes: %d\n", jogo->caminhoSolucao[i][0], jogo->caminhoSolucao[i][1], nave->durabilidadeAtual, nave->pecasRestantes);
        }
        return (nave->pecasColetadas == mapa->total_pecas) ? 2 : 1;
    }

    mapa->visitados[linha][coluna] = true;

    if (mapa->grid[linha][coluna] == 'P') {
        nave->pecasColetadas++;
        nave->durabilidadeAtual += nave->adDurabilidade;
        nave->pecasRestantes = mapa->total_pecas - nave->pecasColetadas;
    }

    if (movimentarDireita(linha, coluna, mapa)) {
        if (nave->pecasColetadas != mapa->total_pecas){
            nave->durabilidadeAtual -= nave->retiraDurabilidade;
        }
        if (movimentar(jogo, linha, coluna + 1, profundidade_atual + 1)) {
            return true;
        }
        if (nave->pecasColetadas != mapa->total_pecas){
            nave->durabilidadeAtual += nave->retiraDurabilidade;
        }
    }
    if (movimentarEsquerda(linha, coluna, mapa)) {
        if (nave->pecasColetadas != mapa->total_pecas){
            nave->durabilidadeAtual -= nave->retiraDurabilidade;
        }
        if (movimentar(jogo, linha, coluna - 1, profundidade_atual + 1)) {
            return true;
        }
        if (nave->pecasColetadas != mapa->total_pecas){
            nave->durabilidadeAtual += nave->retiraDurabilidade;
        }
    }
    if (movimentarCima(linha, coluna, mapa)) {
        if (nave->pecasColetadas != mapa->total_pecas){
            nave->durabilidadeAtual -= nave->retiraDurabilidade;
        }
        if (movimentar(jogo, linha - 1, coluna, profundidade_atual + 1)) {
            return true;
        }
        if (nave->pecasColetadas != mapa->total_pecas){
            nave->durabilidadeAtual += nave->retiraDurabilidade;
        }
    }
    if (movimentarBaixo(linha, coluna, mapa)) {
        if (nave->pecasColetadas != mapa->total_pecas){
            nave->durabilidadeAtual -= nave->retiraDurabilidade;
        }
        if (movimentar(jogo, linha + 1, coluna, profundidade_atual + 1)) {
            return true;
        }
        if (nave->pecasColetadas != mapa->total_pecas){
            nave->durabilidadeAtual += nave->retiraDurabilidade;
        }
    }

    if (mapa->grid[linha][coluna] == 'P') {
        nave->pecasColetadas--;
        nave->durabilidadeAtual -= nave->adDurabilidade;
        nave->pecasRestantes += 1;
    }

    jogo->tamanho_caminho--;
    mapa->visitados[linha][coluna] = false;
    return false;
}

bool movimentarDireita(int linha, int coluna, Mapa* mapa) {

    char posAtual = mapa->grid[linha][coluna];
    if (posAtual != '-' && posAtual != '+' && posAtual != 'X' && posAtual != 'P') {
        return false;
    }

    int proxColuna = coluna + 1;
    if (proxColuna >= mapa->largura) {
        return false;
    }

    char posDestino = mapa->grid[linha][proxColuna];
    if (posDestino == '.') {
        return false;
    }

    if (mapa->visitados[linha][proxColuna]) {
        return false;
    }

    return true;
}

bool movimentarEsquerda(int linha, int coluna, Mapa* mapa) {

    char posAtual = mapa->grid[linha][coluna];
    if (posAtual != '-' && posAtual != '+' && posAtual != 'X' && posAtual != 'P') {
        return false;
    }

    int proxColuna = coluna - 1;
    if (proxColuna < 0) {
        return false;
    }

    char posDestino = mapa->grid[linha][proxColuna];
    if (posDestino == '.') {
        return false;
    }

    if (mapa->visitados[linha][proxColuna]) {
        return false;
    }

    return true;
}

bool movimentarCima(int linha, int coluna, Mapa* mapa) {

    char posAtual = mapa->grid[linha][coluna];
    if (posAtual != '|' && posAtual != '+' && posAtual != 'X' && posAtual != 'P') {
        return false;
    }

    int proxLinha = linha - 1;
    if (proxLinha < 0) {
        return false;
    }

    char posDestino = mapa->grid[proxLinha][coluna];
    if (posDestino == '.') {
        return false;
    }

    if (mapa->visitados[proxLinha][coluna]) {
        return false;
    }

    return true;
}


bool movimentarBaixo(int linha, int coluna, Mapa* mapa) {

    char posAtual = mapa->grid[linha][coluna];
    if (posAtual != '|' && posAtual != '+' && posAtual != 'X' && posAtual != 'P') {
        return false;
    }

    int proxLinha = linha + 1;
    if (proxLinha >= mapa->altura) {
        return false;
    }

    char posDestino = mapa->grid[proxLinha][coluna];
    if (posDestino == '.') {
        return false;
    }

    if (mapa->visitados[proxLinha][coluna]) {
        return false;
    }

    return true;
}