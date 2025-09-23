#include <stdio.h>
#include <stdlib.h>
#include "Jogo.h"

struct Jogo
{
    bool analise;
};

Jogo *Criar_Jogo()
{
    Jogo *jogo = (Jogo *)malloc(sizeof(Jogo));
    if (jogo == NULL)
    {
        exit(1);
    }

    jogo->analise = false; // Inicializa analise como false
    return jogo;
}

void Destruir_Jogo(Jogo *jogo)
{
    free(jogo);
}

void Iniciar_Jogo(Jogo *jogo)
{
    char nome_arquivo[100];
    char continuar_loop = 's';

    do
    {
        printf("Digite o nome do arquivo de entrada: ");
        scanf("%99s", nome_arquivo);

        char analisar;
        printf("Deseja ativar a análise detalhada? (s/n): ");
        scanf(" %c", &analisar);

        jogo->analise = (analisar == 's' || analisar == 'S');

        printf("LÓGICA DE RESOLUÇÃO DO JOGO AQUI\n");
        imprimirResultado(1, 100, 10, jogo->analise);

        printf("Deseja executar um novo mapa? (s/n): ");
        scanf(" %c", &continuar_loop);
        printf("\n");

    } while (continuar_loop == 's' || continuar_loop == 'S');
}

void imprimirPassos(int linha, int coluna, int durabilidade, int pecas_restantes)
{
    printf("Posição: (%d, %d), Durabilidade: %d, Peças Restantes: %d\n", linha, coluna, durabilidade, pecas_restantes);
}

void imprimirResultado(int status, int chamadas_recursivas, int max_recursao, bool analise)
{
    switch (status)
    {
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

    if (analise)
    {
        printf("Chamadas Recursivas: %d\n", chamadas_recursivas);
        printf("Máxima Profundidade de Recursão: %d\n", max_recursao);
    }
}