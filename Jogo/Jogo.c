#include <stdio.h>
#include <stdlib.h>
#include "Jogo.h"


Jogo *Criar_Jogo() {
    Jogo *jogo = (Jogo *)malloc(sizeof(Jogo));
    if (jogo == NULL)
    {
        exit(1);
    }

    jogo->mapa_atual = NULL; // Inicializa o mapa como NULL
    jogo->analise = false; // Inicializa analise como false
    return jogo;
}

void Destruir_Jogo(Jogo *jogo) {
    Destruir_Mapa(jogo->mapa_atual);
    free(jogo);

    int max_passos = jogo->mapa_atual->altura * jogo->mapa_atual->largura;

    for (int i = 0; i < max_passos; i++)
        free(jogo->caminhoSolucao[i]);

    free(jogo->caminhoSolucao);
    jogo->caminhoSolucao = NULL; 
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
        for (int i = 0; i < max_passos; i++) {
            jogo->caminhoSolucao[i] = (int*)malloc(2 * sizeof(int));
        }
        jogo->tamanho_caminho = 0;

        int linha = jogo->mapa_atual->linhaAtual;
        int coluna = jogo->mapa_atual->colunaAtual;
        int profundidade_atual = 0;
        jogo->chamadas_recursivas = 0;
        jogo->max_recursao = 0;
        char analisar;

        printf("Deseja ativar a análise detalhada? (s/n): ");
        scanf(" %c", &analisar);

        jogo->analise = (analisar == 's' || analisar == 'S');

        printf("LÓGICA DE RESOLUÇÃO DO JOGO AQUI\n");
        int status = movimentar(jogo, linha, coluna, profundidade_atual);

        imprimirResultado(1, jogo->chamadas_recursivas, jogo->max_recursao, jogo->analise);

        // Libera o mapa atual
        Destruir_Mapa(jogo->mapa_atual);
        jogo->mapa_atual = NULL;

        printf("Deseja executar um novo mapa? (s/n): ");
        scanf(" %c", &continuar_loop);
        printf("\n");

    } while (continuar_loop == 's' || continuar_loop == 'S');
}

void imprimirPassos(Mapa* mapa, Nave* nave) {
    printf("Posição: (%d, %d), Durabilidade: %d, Peças Restantes: %d\n", mapa->linhaAtual, mapa->colunaAtual, nave->durabilidadeAtual, (mapa->total_pecas - nave->pecasColetadas));
}

void imprimirResultado(int status, int chamadas_recursivas, int max_recursao, bool analise) {
    switch (status) {
    case 0:
        printf("A tripulação falhou em sua jornada e o expresso espacial foi destruído.\n");
        break;
    case 1:
        printf("Parabéns! A tripulação finalizou sua jornada.\n");
        break;
    default:
        printf("Expresso restaurado, a jornada será finalizada sem mais desafios.\n");
        break;
    }

    if (analise) {
        printf("Chamadas Recursivas: %d\n", chamadas_recursivas);
        printf("Máxima Profundidade de Recursão: %d\n", max_recursao);
    }
}

