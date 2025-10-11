#include <stdio.h>
#include <stdlib.h>
#include "Jogo.h"
#include "backtracking.h"

Jogo *Criar_Jogo() {
    Jogo *jogo = (Jogo *)malloc(sizeof(Jogo));
    if (jogo == NULL){
        exit(1);
    }

    jogo->mapa_atual = NULL;
    jogo->caminhoSolucao = NULL;
    jogo->caminhoFinal = NULL;

    return jogo;
}

void Destruir_Jogo(Jogo *jogo) {
    if (jogo == NULL) return;
    
    int max_passos = jogo->mapa_atual->altura * jogo->mapa_atual->largura;
    for (int i = 0; i < max_passos; i++) {
        free(jogo->caminhoSolucao[i]);
    }
    free(jogo->caminhoSolucao);

    if (jogo->caminhoFinal != NULL) {
        for (int i = 0; i < jogo->tamanhoFinal; i++) {
            free(jogo->caminhoFinal[i]);
        }
        free(jogo->caminhoFinal);
    }

    Destruir_Mapa(jogo->mapa_atual);
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
        // Tenta carregar o mapa do arquivo
        if (!Carregar_Mapa_Arquivo(nome_arquivo, jogo->mapa_atual, &jogo->nave_atual))
        {
            printf("Deseja tentar carregar outro mapa? (s/n): ");
            scanf(" %c", &continuar_loop);
            printf("\n");
            Destruir_Mapa(jogo->mapa_atual); // Limpa o mapa que falhou ao carregar
            jogo->mapa_atual = NULL;
            continue;
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

        int linha = jogo->mapa_atual->linhaAtual;
        int coluna = jogo->mapa_atual->colunaAtual;
        int profundidade_atual = 0;
        jogo->chamadas_recursivas = 0;
        jogo->max_recursao = 0;
        char analisar;

        printf("Deseja ativar a análise detalhada? (s/n): ");
        scanf(" %c", &analisar);

        int status = movimentar(jogo, linha, coluna, profundidade_atual);

        imprimirResultado(jogo, status, analisar);

        // Libera o mapa atual
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
            printf("\nA tripulação falhou em sua jornada e o expresso espacial foi destruído.\n");
            break;
        case 1:
            printf("\nParabéns! A tripulação finalizou sua jornada.\n");
            break;
        default:
            printf("\nExpresso restaurado, a jornada será finalizada sem mais desafios.\n");
            break;
    }

    if (analise == 's' || analise == 'S') {
        printf("\n--- Análise de Execução ---\n");
        printf("Chamadas Recursivas: %d\n", jogo->chamadas_recursivas);
        printf("Máxima Profundidade de Recursão: %d\n", jogo->max_recursao);
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