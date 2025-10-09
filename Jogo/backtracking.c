#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "backtracking.h"

bool caminhoValido(int i, int j, Jogo* jogo)
{
    int altura = jogo->mapa_atual->altura;
    int largura = jogo->mapa_atual->largura;

    return (i >= 0 && i < altura && j >= 0 && j < largura);
}

void movimentar(Jogo* jogo) {
    
    int proxLinha = jogo->mapa_atual->linhaAtual;
    int proxColuna = jogo->mapa_atual->colulaAtual + 1;

    if(caminhoValido(proxLinha, proxColuna, jogo)) {
        char elemento = jogo->mapa_atual->grid[proxLinha][proxColuna];
        if (elemento != '.') {
            if (!(jogo->mapa_atual->visitados[proxLinha][proxColuna])) {
                jogo->mapa_atual->colulaAtual += 1;
                jogo->nave_atual.durabilidadeAtual -= jogo->nave_atual.retiraDurabilidade;
                jogo->mapa_atual->visitados[proxLinha][proxColuna] = true;
                
                if (jogo->nave_atual.durabilidadeAtual >= 0 || !(jogo->mapa_atual->grid[proxLinha][proxColuna] == 'F')) {
                    movimentar(jogo);
                }
            }
        }
    }

    int proxLinha = jogo->mapa_atual->linhaAtual;
    int proxColuna = jogo->mapa_atual->colulaAtual - 1;

    if(caminhoValido(proxLinha, proxColuna, jogo)) {
        char elemento = jogo->mapa_atual->grid[proxLinha][proxColuna];
        if (elemento != '.') {
            if (!jogo->mapa_atual->visitados[proxLinha][proxColuna]) {
                
            }
        }
        
    }

    int proxLinha = jogo->mapa_atual->linhaAtual + 1;
    int proxColuna = jogo->mapa_atual->colulaAtual;

    if(caminhoValido(proxLinha, proxColuna, jogo)) {
        char elemento = jogo->mapa_atual->grid[proxLinha][proxColuna];
        if (elemento != '.') {
            if (!jogo->mapa_atual->visitados[proxLinha][proxColuna]) {
                
            }
        }
        
    }

    int proxLinha = jogo->mapa_atual->linhaAtual - 1;
    int proxColuna = jogo->mapa_atual->colulaAtual;

    if(caminhoValido(proxLinha, proxColuna, jogo)) {
        char elemento = jogo->mapa_atual->grid[proxLinha][proxColuna];
        if (elemento != '.') {
            if (!jogo->mapa_atual->visitados[proxLinha][proxColuna]) {
                
            }
        }
        
    }
}

bool movimentar(Jogo* jogo, int linha, int coluna, int pecas_coletadas, int profundidade_atual) {
    // 1. Contabilizar chamadas recursivas e profundidade (Modo Análise)
    // chamadas_recursivas++;
    // if (profundidade_atual > max_recursao) max_recursao = profundidade_atual;

    // 2. Verificar Casos Base de Falha
    if (jogo->nave_atual.durabilidadeAtual <= 0) {
        return false; // Fim do caminho, sem durabilidade
    }

    // 3. Verificar Caso Base de Sucesso
    if (jogo->mapa_atual->grid[linha][coluna] == 'F') {
        imprimirPassos();
        // Imprimir mensagem final de sucesso
        return true;
    }

    // 4. Marcar a posição atual como visitada
    jogo->mapa_atual->visitados[linha][coluna] = true;
    
    // 5. Atualizar estado (coletar peça, etc.)
    // ...

    // Imprimir o passo atual
    imprimirPassos(linha, coluna, jogo->nave_atual.durabilidadeAtual, total_pecas - pecas_coletadas);

    // 6. Tentar os próximos movimentos (Norte, Sul, Leste, Oeste)
    // Verifique se o movimento é válido (dentro do mapa, não visitado, caminho permite)
    
    // Exemplo para mover para a DIREITA:
    if (movimentoValidoParaDireita(linha, coluna, jogo)) {
        // Salvar estado atual (durabilidade, peças) para o backtracking
        // Atualizar estado para o próximo passo (diminuir durabilidade, etc.)
        if (movimentar(jogo, linha, coluna + 1, pecas_coletadas, profundidade_atual + 1)) {
            return true; // Se o caminho deu certo, propague o sucesso
        }
        // Se chegou aqui, o caminho falhou. RESTAURE o estado (backtrack).
    }

    // ... Fazer o mesmo para os outros movimentos (Esquerda, Cima, Baixo) ...

    // 7. Se nenhum movimento a partir daqui levou à solução, desmarque e retorne falha
    jogo->mapa_atual->visitados[linha][coluna] = false; // Backtrack
    return false;
}