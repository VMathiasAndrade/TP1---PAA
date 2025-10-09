#include "Mapa/Jogo.h"

int main()
{
    Jogo *jogo = Criar_Jogo();
    Iniciar_Jogo(jogo);
    Destruir_Jogo(jogo);
    return 0;
}