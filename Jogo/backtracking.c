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

    mapa->visitados[linha][coluna] = true;
    jogo->caminhoSolucao[jogo->tamanhoAtual][0] = linha;
    jogo->caminhoSolucao[jogo->tamanhoAtual][1] = coluna;
    jogo->caminhoSolucao[jogo->tamanhoAtual][2] = nave->durabilidadeAtual;
    jogo->caminhoSolucao[jogo->tamanhoAtual][3] = nave->pecasRestantes;
    jogo->tamanhoAtual++;

    if (nave->durabilidadeAtual <= 0) {
        copiarCaminho(jogo);
        mapa->visitados[linha][coluna] = false; 
        jogo->tamanhoAtual--;                  
        nave->durabilidadeAtual = durabilidade_anterior;
        nave->pecasColetadas = pecas_coletadas_anterior;
        nave->pecasRestantes = pecas_restantes_anterior;

        return 0;
    }

    
    if (mapa->grid[linha][coluna] == 'P') {
        nave->pecasColetadas++;
        nave->durabilidadeAtual += nave->adDurabilidade;
        nave->pecasRestantes--;
    }

    if (mapa->grid[linha][coluna] == 'F') {
        copiarCaminho(jogo);
        return (nave->pecasColetadas == mapa->total_pecas) ? 2 : 1;
    }
    
    if (movimentarDireita(linha, coluna, mapa)) {
        if (nave->pecasColetadas != mapa->total_pecas){
            nave->durabilidadeAtual -= nave->retiraDurabilidade;
        }
        int status = movimentar(jogo, linha, coluna + 1, profundidade_atual + 1);
        if (status != 0) {
            return status;
        }
        if (nave->pecasColetadas != mapa->total_pecas){
            nave->durabilidadeAtual += nave->retiraDurabilidade;
        }
    }
    if (movimentarEsquerda(linha, coluna, mapa)) {
        if (nave->pecasColetadas != mapa->total_pecas){
            nave->durabilidadeAtual -= nave->retiraDurabilidade;
        }
        int status = movimentar(jogo, linha, coluna - 1, profundidade_atual + 1);
        if (status != 0) {
            return status;
        }
        if (nave->pecasColetadas != mapa->total_pecas){
            nave->durabilidadeAtual += nave->retiraDurabilidade;
        }
    }
    if (movimentarCima(linha, coluna, mapa)) {
        if (nave->pecasColetadas != mapa->total_pecas){
            nave->durabilidadeAtual -= nave->retiraDurabilidade;
        }
        int status = movimentar(jogo, linha - 1, coluna, profundidade_atual + 1);
        if (status != 0) {
            return status;
        }
        if (nave->pecasColetadas != mapa->total_pecas){
            nave->durabilidadeAtual += nave->retiraDurabilidade;
        }
    }
    if (movimentarBaixo(linha, coluna, mapa)) {
        if (nave->pecasColetadas != mapa->total_pecas){
            nave->durabilidadeAtual -= nave->retiraDurabilidade;
        }
        int status = movimentar(jogo, linha + 1, coluna, profundidade_atual + 1);
        if (status != 0) {
            return status;
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

    jogo->tamanhoAtual--;
    mapa->visitados[linha][coluna] = false;
    nave->durabilidadeAtual = durabilidade_anterior;
    nave->pecasColetadas = pecas_coletadas_anterior;
    nave->pecasRestantes = pecas_restantes_anterior;
    return 0;
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