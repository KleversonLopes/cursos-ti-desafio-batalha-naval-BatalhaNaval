// Desafio Batalha Naval - MateCheck
// Este código inicial serve como base para o desenvolvimento do sistema de Batalha Naval.
// Siga os comentários para implementar cada parte do desafio.

// Nível Novato - Posicionamento dos Navios
    // Sugestão: Declare uma matriz bidimensional para representar o tabuleiro (Ex: int tabuleiro[5][5];).
    // Sugestão: Posicione dois navios no tabuleiro, um verticalmente e outro horizontalmente.
    // Sugestão: Utilize `printf` para exibir as coordenadas de cada parte dos navios.

// Nível Aventureiro - Expansão do Tabuleiro e Posicionamento Diagonal
    // Sugestão: Expanda o tabuleiro para uma matriz 10x10.
    // Sugestão: Posicione quatro navios no tabuleiro, incluindo dois na diagonal.
    // Sugestão: Exiba o tabuleiro completo no console, mostrando 0 para posições vazias e 3 para posições ocupadas.

// Nível Mestre - Habilidades Especiais com Matrizes
    // Sugestão: Crie matrizes para representar habilidades especiais como cone, cruz, e octaedro.
    // Sugestão: Utilize estruturas de repetição aninhadas para preencher as áreas afetadas por essas habilidades no tabuleiro.
    // Sugestão: Exiba o tabuleiro com as áreas afetadas, utilizando 0 para áreas não afetadas e 1 para áreas atingidas.

    // Exemplos de exibição das habilidades:
    // Exemplo para habilidade em cone:
    // 0 0 1 0 0
    // 0 1 1 1 0
    // 1 1 1 1 1
    
    // Exemplo para habilidade em octaedro:
    // 0 0 1 0 0
    // 0 1 1 1 0
    // 0 0 1 0 0

    // Exemplo para habilidade em cruz:
    // 0 0 1 0 0
    // 1 1 1 1 1
    // 0 0 1 0 0

/**
 * author: Kleverson
 * description: Implementação do sistema de simulação de batalha naval.
 * data: 28-08-2025
 * intituição: Faculdade Estácio de Sá - Vitória - ES
 * nivel novato - 28-08-2025
 */

#include <stdio.h>
#include <stdlib.h>

void LimpaTela() {
    // Limpar a tela
    #ifdef __linux__ // se o SO for linux
        system("clear");
    #elif _WIN32 // se o SO for Windows
        system("cls");
    #endif
}

void Espera() {
    printf("\n*** Pressione ENTER para continuar...");
    int c;
    // Limpa qualquer entrada residual
    while ((c = getchar()) != '\n' && c != EOF);
    // Espera o ENTER
    getchar();
}

int tabuleiro[10][10];

void iniciaTabuleiro() {
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            tabuleiro[i][j] = 0;
        }
    }
}

void mostraTabuleiro() {
    printf("\nTabuleiro atual:\n");
    /*
    * Exibe o tabuleiro com as posições dos navios
    */
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            printf("%d ", tabuleiro[i][j]);
        }
        printf("\n");
    }
}

const int navio1[3] = {3,3,3}, navio2[3] = {3,3,3};

// posicionamento dos navios no tabuleiro
void posicionaNavio(int x, int y, char orientacao, int* navio, char* nomeNavio){
    // validação das coordenadas

    // testa ocupação do tabuleiro
    if (orientacao == 'v') {
        if (tabuleiro[x][y] != 0 || tabuleiro[x][y+1] != 0 || tabuleiro[x][y+2] != 0) {
            printf("\nPosição inválida para o [ %s ]: (%d, %d)! Já ocupado\n", nomeNavio, x, y);
            return;
        }

        if (x > 7) {
            printf("\nPosição inválida para o [ %s ]: (%d, %d)! Vertical\n", nomeNavio, x, y);
            return;
        }
    }

    // testa limites da área do tabuleiro
    if (orientacao == 'h') {
        if (tabuleiro[x][y] != 0 || tabuleiro[x+1][y] != 0 || tabuleiro[x+2][y] != 0) {
            printf("\nPosição inválida para o [ %s ]: (%d, %d)! Já ocupado\n", nomeNavio, x, y);
            return;
        }

        if (y > 7) {
            printf("\nPosição inválida para o [ %s ]: (%d, %d)! Horizontal\n", nomeNavio, x, y);
            return;
        }
    }

    // preenche o tabuleiro com o navio informado na orientação escolhida
    for (int i = 1; i <= 3; i++) {
        tabuleiro[x][y] = navio[i-1];
        orientacao == 'v' ? x++ : y++;
    }
}

void partida() {
    // Lógica da partida
    LimpaTela();

    printf("\n*** Iniciando nova partida...\n");

    iniciaTabuleiro();

    int x = 0, y = 0;

    char orientacao;

    // recebe dados do navio 1 para processar
    printf("\n*** Navio 1\n");
    printf("Coordenada X : ");
    scanf("%d", &x);
    printf("Coordenada Y : ");
    scanf("%d", &y);
    printf("Orientação (v)ertical (h)orizontal : ");
    scanf(" %c", &orientacao);

    posicionaNavio(x, y, orientacao, navio1, "Navio 1"); // navio 1 recebe coordenadas e orientação

    // recebe dados do navio 2 para processar
    printf("\n*** Navio 2\n");
    printf("Coordenada X : ");
    scanf("%d", &x);
    printf("Coordenada Y : ");
    scanf("%d", &y);
    printf("Orientação (v)ertical (h)orizontal : ");
    scanf(" %c", &orientacao);

    posicionaNavio(x, y, orientacao, navio2, "Navio 2"); // navio 2 recebe coordenadas e orientação

    mostraTabuleiro();
}

void main() {
    // menu principal de opções do jogo
    do {
        LimpaTela();

        printf("*** Desafio de Batalha Naval ***\n\n");
        printf("1. Iniciar nova partida\n");
        printf("0. Sair\n");
        printf("Escolha uma opção: ");

        int opcao;
        
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                partida();
                break;
            case 0:
                printf("Saindo...\n");
                return;
            default:
                printf("Opção inválida!\n");
        }

        Espera();

    } while (1);
}
