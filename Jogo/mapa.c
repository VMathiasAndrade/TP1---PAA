#include "mapa.h"
#include <stdio.h>
#include <stdlib.h>

Mapa* Criar_Mapa() {
    Mapa* mapa = (Mapa*)malloc(sizeof(Mapa));
    if (mapa == NULL) {
       exit(1);
    }
    mapa->altura = 0;
    mapa->largura = 0;
    mapa->grid = NULL;
    mapa->total_pecas = 0;
    return mapa;
}

void Destruir_Mapa(Mapa* mapa) {
    if (mapa == NULL) return;

    if (mapa->grid != NULL) {
        for (int i = 0; i < mapa->altura; i++) {
            free(mapa->grid[i]);
        }
        free(mapa->grid);
    }

    if (mapa->visitados != NULL) {
        for (int i = 0; i < mapa->altura; i++) {
            free(mapa->visitados[i]);
        }
        free(mapa->visitados);
    }
    free(mapa);
}

bool Carregar_Mapa_Arquivo(const char* nome_arquivo, Mapa* mapa, Nave* nave) {
    FILE* arquivo = fopen(nome_arquivo, "r");
    if (arquivo == NULL) {
        printf("Erro: Não foi possível abrir o arquivo '%s'.\n", nome_arquivo);
        return false;
    }
    fscanf(arquivo, "%d %d %d", &nave->durabilidadeAtual, &nave->retiraDurabilidade, &nave->adDurabilidade);
    fscanf(arquivo, "%d %d", &mapa->altura, &mapa->largura);
    // Aloca memória para as linhas do mapa
    mapa->grid = (char **)malloc(mapa->altura * sizeof(char *));
    mapa->visitados = (bool**)malloc(mapa->altura * sizeof(bool*));
    for (int i = 0; i < mapa->altura; i++) {
        // Aloca memória para as colunas de cada linha (+2 para o '\n' e '\0')
        mapa->grid[i] = (char *)malloc((mapa->largura + 2) * sizeof(char));
        mapa->visitados[i] = (bool*)malloc(mapa->largura * sizeof(bool));
    }
    fgetc(arquivo);

    // Lê o mapa e identifica os componentes
    mapa->total_pecas = 0;
    for (int i = 0; i < mapa->altura; i++) {
        fgets(mapa->grid[i], mapa->largura + 2, arquivo);
        for (int j = 0; j < mapa->largura; j++) {
            if (mapa->grid[i][j] == 'X') {
                nave->posicao.linha = i;
                nave->posicao.coluna = j;
            } else if (mapa->grid[i][j] == 'P') {
                mapa->total_pecas++;
            }
        }
    }

    nave->pecasRestantes = mapa->total_pecas;

    for (int i = 0; i < mapa->altura; i++) {
        for (int j = 0; j < mapa->largura; j++) {
            mapa->visitados[i][j] = false;
        }
    }
    
    fclose(arquivo);
    // testa para ver se o map foi carregado, pode apagar depois
    printf("Mapa '%s' carregado com sucesso!\n", nome_arquivo);
    printf("Nave inicia em (%d, %d) com %d de durabilidade. Total de pecas: %d.\n\n", 
           nave->posicao.linha, nave->posicao.coluna, nave->durabilidadeAtual, mapa->total_pecas);
           
    return true;
} //feito usando boolean para evitar erros se o nao conseguir ler o arquivo

int getAltura(const Mapa* mapa) {
    return mapa->altura;
}

int getLargura(const Mapa* mapa) {
    return mapa->largura;
}

char getElemento(const Mapa* mapa, int linha, int coluna) {
    if (linha >= 0 && linha < mapa->altura && coluna >= 0 && coluna < mapa->largura) {
        return mapa->grid[linha][coluna];
    }
    return '\0'; // Retorna um caractere nulo para posição inválida
}