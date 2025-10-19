#include <stdio.h>
#include <stdlib.h>
#include "Jogo.h"
#include "backtracking.h"

Jogo *Criar_Jogo() {
    Jogo *jogo = (Jogo*)malloc(sizeof(Jogo));
    if (jogo == NULL){
        exit(1);
    }

    jogo->nave_atual = (Nave*)malloc(sizeof(Nave));
    jogo->dados = (Dados*)malloc(sizeof(Dados));
    jogo->mapa_atual = NULL;
    jogo->caminhoSolucao = NULL;
    jogo->caminhoFinal = NULL;

    return jogo;
}

void Destruir_Jogo(Jogo *jogo) {
    if (jogo == NULL) return;
    
    if (jogo->nave_atual != NULL) {
        free(jogo->nave_atual);
    }
    if (jogo->dados != NULL) {
        free(jogo->dados);
    }

    free(jogo);
}

void Iniciar_Jogo(Jogo *jogo) {
    char nome_arquivo[100];
    char continuar_loop = 's';

    do
    { 
        printf("Digite o nome do arquivo de entrada: ");
        scanf("%99s", nome_arquivo);

        jogo->mapa_atual = Criar_Mapa();
        if (!Carregar_Mapa_Arquivo(nome_arquivo, jogo->mapa_atual, jogo->nave_atual))
        {
            printf("Deseja tentar carregar outro mapa? (s/n): ");
            scanf(" %c", &continuar_loop);
            printf("\n");
            Destruir_Mapa(jogo->mapa_atual); 
            jogo->mapa_atual = NULL;
            continue;
        }

        jogo->num_inimigos = 0;
        for (int i = 0; i < jogo->mapa_atual->altura; i++) {
            for (int j = 0; j < jogo->mapa_atual->largura; j++) {
                if (jogo->mapa_atual->grid[i][j] == 'I') {
                    jogo->num_inimigos++;
                }
            }
        }

       
        if (jogo->num_inimigos > 0) {
            jogo->inimigos = (Inimigo*)malloc(jogo->num_inimigos * sizeof(Inimigo));
        } else {
            jogo->inimigos = NULL;
        }

        
        int inimigo_atual = 0;
        if (jogo->num_inimigos > 0) {
            for (int i = 0; i < jogo->mapa_atual->altura; i++) {
                for (int j = 0; j < jogo->mapa_atual->largura; j++) {
                    if (jogo->mapa_atual->grid[i][j] == 'I') {
                        jogo->inimigos[inimigo_atual].linha = i;
                        jogo->inimigos[inimigo_atual].coluna = j;
                        jogo->inimigos[inimigo_atual].status = ATIVO;
                        jogo->inimigos[inimigo_atual].dano = 10; 
                        inimigo_atual++;
                    }
                }
            }
        }

        int max_passos = jogo->mapa_atual->altura * jogo->mapa_atual->largura;
        jogo->caminhoSolucao = (int**)malloc(max_passos * sizeof(int*));
        jogo->caminhoFinal = (int**)malloc(max_passos * sizeof(int*));
        for (int i = 0; i < max_passos; i++) {
            jogo->caminhoSolucao[i] = (int*)malloc(4 * sizeof(int));
            jogo->caminhoFinal[i] = (int*)malloc(4 * sizeof(int));
        }
        jogo->tamanhoAtual = 0;
        jogo->tamanhoFinal = 0;

        int linha = jogo->nave_atual->posicao.linha;
        int coluna = jogo->nave_atual->posicao.coluna;
        int profundidade_atual = 0;
        jogo->dados->chamadas_recursivas = 0;
        jogo->dados->max_recursao = 0;
        char analisar;

        printf("Deseja ativar a analise detalhada? (s/n): ");
        scanf(" %c", &analisar);

        int status = movimentar(jogo, linha, coluna, profundidade_atual);

        imprimirResultado(jogo, status, analisar);

        if (jogo->caminhoSolucao != NULL) {
            for (int i = 0; i < max_passos; i++) {
                free(jogo->caminhoSolucao[i]);
            }
            free(jogo->caminhoSolucao);
            jogo->caminhoSolucao = NULL;
        }

        if (jogo->caminhoFinal != NULL) {
            for (int i = 0; i < max_passos; i++) {
                free(jogo->caminhoFinal[i]);
            }
            free(jogo->caminhoFinal);
            jogo->caminhoFinal = NULL;
        }
        
        Destruir_Mapa(jogo->mapa_atual);
        jogo->mapa_atual = NULL;

        printf("Deseja executar um novo mapa? (s/n): ");
        scanf(" %c", &continuar_loop);
        printf("\n");

    } while (continuar_loop == 's' || continuar_loop == 'S');
}

void imprimirResultado(Jogo* jogo, int status, char analise) {
    
    if (jogo->caminhoFinal != NULL){
        for (int i = 0; i < jogo->tamanhoFinal; i++) {
            printf("Linha: %d, Coluna: %d; D: %d, pecas restantes: %d\n", 
                jogo->caminhoFinal[i][0], 
                jogo->caminhoFinal[i][1], 
                jogo->caminhoFinal[i][2], 
                jogo->caminhoFinal[i][3]);
        }
    }
    
    switch (status) {
        case 0:
            printf("\nA tripulacao falhou em sua jornada e o expresso espacial foi destruido.\n");
            break;
        case 1:
            printf("\nParabens! A tripulacao finalizou sua jornada.\n");
            break;
        default:
            printf("\nExpresso restaurado, a jornada sera finalizada sem mais desafios.\n");
            break;
    }

    if (analise == 's' || analise == 'S') {
        printf("\n--- Analise de Execucao ---\n");
        printf("Chamadas Recursivas: %d\n", jogo->dados->chamadas_recursivas);
        printf("Maxima Profundidade de Recursao: %d\n", jogo->dados->max_recursao);
    }
}

void copiarCaminho(Jogo* jogo) {
    jogo->tamanhoFinal = jogo->tamanhoAtual;
    for (int i = 0; i < jogo->tamanhoFinal; i++) {
        jogo->caminhoFinal[i][0] = jogo->caminhoSolucao[i][0];
        jogo->caminhoFinal[i][1] = jogo->caminhoSolucao[i][1];
        jogo->caminhoFinal[i][2] = jogo->caminhoSolucao[i][2];
        jogo->caminhoFinal[i][3] = jogo->caminhoSolucao[i][3];
    }   
}