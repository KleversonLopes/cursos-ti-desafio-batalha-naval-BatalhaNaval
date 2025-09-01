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
#include <ctype.h>

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

#define LINHA 10
#define COLUNA 10

int tabuleiro[LINHA][COLUNA];

void iniciaTabuleiro() {
    for (int i = 0; i < LINHA; i++) {
        for (int j = 0; j < COLUNA; j++) {
            tabuleiro[i][j] = 0;
        }
    }
}

void mostraTabuleiro() {
    printf("\nTabuleiro atual:\n");
    /*
    * Exibe o tabuleiro com as posições dos navios
    */
    for (int i = 0; i < LINHA; i++) {
        for (int j = 0; j < COLUNA; j++) {
            printf("%d ", tabuleiro[i][j]);
        }
        printf("\n");
    }
}

const int 
    navio1[3] = {3,3,3}, 
    navio2[3] = {3,3,3}, 
    navio3[3] = {3,3,3}, 
    navio4[3] = {3,3,3};

//habilidades especiais
/**
 * centro dos ataques será sempre
 * entre as linhas 1 e 8, e
 * entre as colunas 2 e 7
 */
const int cone[3][5] = {
    {0, 0, 1, 0, 0},
    {0, 1, 1, 1, 0},
    {1, 1, 1, 1, 1}
};

const int cruz[3][5] = {
    {0, 0, 1, 0, 0},
    {1, 1, 1, 1, 1},
    {0, 0, 1, 0, 0}
};

const int octaedro[3][5] = {
    {0, 0, 1, 0, 0},
    {0, 1, 1, 1, 0},
    {0, 0, 1, 0, 0}
};

/**
 * Rotina para receber parâmetros de posicionamento do navio via teclado
 * @param x ponteiro para a coordenada x
 * @param y ponteiro para a coordenada y
 * @param orientacao ponteiro para a orientação do navio
 */
void recebeParametrosNavio(int* x, int* y, char* orientacao) {
    printf("Coordenada X : ");
    scanf("%d", x);
    printf("Coordenada Y : ");
    scanf("%d", y);
    printf("Orientação (v)ertical | (h)orizontal | diagonal (d)ireita | diagonal (e)squerda: ");
    scanf(" %c", orientacao);
}

/**
 *  posicionamento dos navios no tabuleiro
 * @param x coordenada x
 * @param y coordenada y
 * @param orientacao orientação do navio (v/h/d/e) - vertical/horizontal/diagonal direita/diagonal esquerda
 * @param navio ponteiro para o vetor do navio
 * @param nomeNavio nome do navio
 */
void posicionaNavio(int x, int y, char orientacao, int* navio, char* nomeNavio){
    // validação das coordenadas

    if (orientacao != 'v' && orientacao != 'h' && orientacao != 'd' && orientacao != 'e') {
        printf("\nOrientação inválida para o [ %s ]: %c! (v/h/d/e)\n", nomeNavio, orientacao);
        return;
    }

    if (orientacao == 'v' || orientacao == 'd' || orientacao == 'e') {
        // testa ocupação do tabuleiro

        // teste para vertical
        if (orientacao == 'v') {
            if (tabuleiro[x][y] != 0 || tabuleiro[x][y+1] != 0 || tabuleiro[x][y+2] != 0) {
                printf("\nPosição inválida para o [ %s ]: (%d, %d)! Já ocupado\n", nomeNavio, x, y);
                return;
            }
        }

        // teste para diagonal direita
        if (orientacao == 'd') {
            if (tabuleiro[x][y] != 0 || tabuleiro[x+1][y+1] != 0 || tabuleiro[x+2][y+2] != 0) {
                printf("\nPosição inválida para o [ %s ]: (%d, %d)! Já ocupado\n", nomeNavio, x, y);
                return;
            }
        }

        // teste para diagonal esquerda
        if (orientacao == 'e') {
            if (tabuleiro[x][y] != 0 || tabuleiro[x+1][y-1] != 0 || tabuleiro[x+2][y-2] != 0) {
                printf("\nPosição inválida para o [ %s ]: (%d, %d)! Já ocupado\n", nomeNavio, x, y);
                return;
            }
        }

        // testa limites da área do tabuleiro
        if (x > 7) {
            printf("\nPosição inválida para o [ %s ]: (%d, %d)! Vertical\n", nomeNavio, x, y);
            return;
        }
    }

    if (orientacao == 'h') {
        // testa ocupação do tabuleiro
        if (tabuleiro[x][y] != 0 || tabuleiro[x+1][y] != 0 || tabuleiro[x+2][y] != 0) {
            printf("\nPosição inválida para o [ %s ]: (%d, %d)! Já ocupado\n", nomeNavio, x, y);
            return;
        }

        // testa limites da área do tabuleiro
        if (y > 7) {
            printf("\nPosição inválida para o [ %s ]: (%d, %d)! Horizontal\n", nomeNavio, x, y);
            return;
        }
    }

    // preenche o tabuleiro com o navio informado na orientação conforme escolhido
    for (int i = 1; i <= 3; i++) {
        tabuleiro[x][y] = navio[i-1];

        // se a orientação for vertical ou diagonal desce uma linha no tabuleiro e continua o processo para colunas
        if (orientacao == 'v' || orientacao == 'd' || orientacao == 'e'){
            x++;
        }

        // se a orientação for horizontal ou diagonal direita avança uma coluna no tabuleiro
        if (orientacao == 'h' || orientacao == 'd'){
            y++;
        }

        // se a orientação for diagonal esquerda regride uma coluna no tabuleiro
        if (orientacao == 'e'){
            y--;
        }
    }
}

/**
 * Dispara o ataque
 * @param x coordenada x do ataque
 * @param y coordenada y do ataque
 * @param habilidade habilidade a ser utilizada
 */
void disparaAtaque(int x, int y, char habilidade) {
    // Lógica para disparar a habilidade do navio na posição (x, y)
    printf("Disparando habilidade do navio em (%d, %d) com habilidade %c\n", x, y, habilidade);
    // testa se o ataque esta dentro dos limites da área do tabuleiro
    if (verificaLimites(x, y)) {
        if (habilidade == 'c') {
            ataqueCone(x, y);
        } else if (habilidade == 'o') {
            ataqueOctaedro(x, y);
        } else if (habilidade == 'z') {
            ataqueCruz(x, y);
        }
    }
}

/**
 * centro dos ataques será sempre
 * entre as linhas 1 e 8, e
 * entre as colunas 2 e 7
 */
int verificaLimites(int x, int y) {
    if (x < 1 || x > (LINHA - 1) || y < 2 || y > (COLUNA - 2)) {
        printf("\n*** Ataque fora dos limites do tabuleiro! ***\n");
        return 0;
    }
    return 1;
}

void ataqueCone(int x, int y) {
    // Lógica para ataque em cone
    /**
     * posiciona o centro do cone e ajusta a área de ataque
     */
    printf("Ataque em cone na posição (%d, %d)\n", x, y);
    for (int i = 1; i <= 3; i++) {
        for (int j = 1; j <= 5; j++) {
            if (cone[i-1][j-1] == 1) {
                int ataqueX = x + (i - 2); // ajusta a linha do ataque
                int ataqueY = y + (j - 3); // ajusta a coluna do ataque
                tabuleiro[ataqueX][ataqueY] = 5; // marca o ataque no tabuleiro
            }
        }
    }
}

void ataqueCruz(int x, int y) {
    // Lógica para ataque em cruz
    printf("Ataque em cruz na posição (%d, %d)\n", x, y);
    for (int i = 1; i <= 3; i++) {
        for (int j = 1; j <= 5; j++) {
            if (cruz[i-1][j-1] == 1) {
                int ataqueX = x + (i - 2); // ajusta a linha do ataque
                int ataqueY = y + (j - 3); // ajusta a coluna do ataque
                tabuleiro[ataqueX][ataqueY] = 5; // marca o ataque no tabuleiro
            }
        }
    }
}

void ataqueOctaedro(int x, int y) {
    // Lógica para ataque em octaedro
    printf("Ataque em octaedro na posição (%d, %d)\n", x, y);
    for (int i = 1; i <= 3; i++) {
        for (int j = 1; j <= 5; j++) {
            if (octaedro[i-1][j-1] == 1) {
                int ataqueX = x + (i - 2); // ajusta a linha do ataque
                int ataqueY = y + (j - 3); // ajusta a coluna do ataque
                tabuleiro[ataqueX][ataqueY] = 5; // marca o ataque no tabuleiro
            }
        }
    }
}

/**
 * Recebe os parâmetros de ataque do jogador.
 * @param x coordenada x do ataque
 * @param y coordenada y do ataque
 * @param habilidade habilidade a ser utilizada
 */
char recebeParametrosAtaque(int* x, int* y, char* habilidade) {
    printf("Coordenada X do ataque: ");
    scanf("%d", x);
    printf("Coordenada Y do ataque: ");
    scanf("%d", y);
    printf("Habilidade a ser utilizada ");
    printf("(c)one | (o)ctaedro | cru(z) | (s)air: ");
    scanf(" %c", habilidade);
    return tolower(*habilidade);
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
    recebeParametrosNavio(&x, &y, &orientacao);
    posicionaNavio(x, y, orientacao, navio1, "Navio 1"); // posiciona navio 1 no tabuleiro

    // recebe dados do navio 2 para processar
    printf("\n*** Navio 2\n");
    recebeParametrosNavio(&x, &y, &orientacao);
    posicionaNavio(x, y, orientacao, navio2, "Navio 2"); // posiciona navio 2 no tabuleiro

    // recebe dados do navio 3 para processar
    printf("\n*** Navio 3\n");
    recebeParametrosNavio(&x, &y, &orientacao);
    posicionaNavio(x, y, orientacao, navio3, "Navio 3"); // posiciona navio 3 no tabuleiro

    // recebe dados do navio 4 para processar
    printf("\n*** Navio 4\n");
    recebeParametrosNavio(&x, &y, &orientacao);
    posicionaNavio(x, y, orientacao, navio4, "Navio 4"); // posiciona navio 4 no tabuleiro

    mostraTabuleiro();
    
    do {
        printf("\n");
        int x, y;
        char habilidade;

        if (recebeParametrosAtaque(&x, &y, &habilidade) == 's') {
            // Sair da partida
            break;
        }
        disparaAtaque(x, y, habilidade);
        mostraTabuleiro();
        Espera();
    } while (1);
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
