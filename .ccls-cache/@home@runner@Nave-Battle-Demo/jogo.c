#include "jogo.h"

// Variáveis globais para contagem de disparos
int disparosJogador = 0;
int disparosAdversario = 0;
int vencedor = 0; // 1 para jogador, 2 para adversário

// Variáveis globais para configuração do jogo
int TAMANHO_TABULEIRO = 4; // Tamanho padrão
int submarinos = 0;
int fragatas = 0;
int destroyers = 1;
int portaAvioes = 1;

void mostrarMenu() {
    limparTela();
    printf("=== BATALHA NAVAL ===\n");
    printf("1. Iniciar Jogo\n");
    printf("2. Regras do Jogo\n");
    printf("3. Ver Pontuação\n");
    printf("4. Sair\n");
}

void selecionarDificuldade() {
    int dificuldade;
    do {
        limparTela();
        printf("=== SELECIONAR DIFICULDADE ===\n");
        printf("1. Fácil (Tabuleiro 2x2)\n");
        printf("2. Médio (Tabuleiro 4x4)\n");
        printf("3. Difícil (Tabuleiro 8x8)\n");
        printf("Escolha a dificuldade: ");
        scanf("%d", &dificuldade);
    } while (dificuldade < 1 || dificuldade > 3);

    definirDificuldade(dificuldade);
}

void definirDificuldade(int dificuldade) {
    switch (dificuldade) {
        case 1:
            TAMANHO_TABULEIRO = 2;
            submarinos = 1;
            fragatas = 1;
            destroyers = 0;
            portaAvioes = 0;
            break;
        case 2:
            TAMANHO_TABULEIRO = 4;
            submarinos = 1;
            fragatas = 1;
            destroyers = 1;
            portaAvioes = 1;
            break;
        case 3:
            TAMANHO_TABULEIRO = 8;
            submarinos = 3;
            fragatas = 2;
            destroyers = 2;
            portaAvioes = 1;
            break;
    }
}

void regrasJogo() {
    limparTela();
    printf("=== REGRAS DO JOGO ===\n");
    printf("1. O objetivo do jogo é afundar todos os navios do adversário.\n");
    printf("2. Cada jogador posiciona seus navios no tabuleiro.\n");
    printf("3. Os jogadores se revezam para adivinhar a posição dos navios adversários.\n");
    printf("4. O jogo termina quando todos os navios de um jogador forem afundados.\n");
    printf("\nPressione ENTER para voltar ao menu...");
    getchar(); // Espera o ENTER
}

void iniciarJogo() {
    selecionarDificuldade();
    // Cria um tabuleiro para o jogador
    int tabuleiroJogador[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO];
    // Cria um tabuleiro para as jogadas do jogador
    int tabuleiroJogadasJogador[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO];
    // Cria um tabuleiro para o computador
    int tabuleiroAdversario[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO];
    // Avaliar se o jogo ainda está em execução ou se alguém ganhou
    int jogoContinua = 1;

    disparosJogador = 0;  // Reset disparos do jogador
    disparosAdversario = 0;  // Reset disparos do adversário
    vencedor = 0;  // Reset vencedor

    inicializarTabuleiro(tabuleiroJogador);
    inicializarTabuleiro(tabuleiroJogadasJogador);
    inicializarTabuleiro(tabuleiroAdversario);

    montarTabuleiroJogador(tabuleiroJogador);
    getchar(); // Espera o ENTER
    limparTela();

    printf("Montando o tabuleiro do adversário...\n");
    montarTabuleiroAdversario(tabuleiroAdversario);
    printf("\nPressione ENTER para continuar...");
    getchar(); // Espera o ENTER
    limparTela();

    while (jogoContinua) {
        printf("Seu tabuleiro:\n");
        mostrarTabuleiro(tabuleiroJogador);
        printf("\nSuas jogadas:\n");
        mostrarTabuleiro(tabuleiroJogadasJogador);
        printf("\nRealize sua jogada:\n");
        realizarJogadaJogador(tabuleiroAdversario, tabuleiroJogadasJogador, tabuleiroJogador);

        if (verificarNaviosAfundados(tabuleiroAdversario)) {
            printf("Parabéns! Você afundou todos os navios do adversário!\n");
            getchar(); // Espera o ENTER
            printf("Aguarde para jogar de novo!\n");
            delay(5);
            vencedor = 1; // Jogador venceu
            jogoContinua = 0;
            break;
        }

        printf("\nAguarde enquanto o adversário joga...\n");
        delay(3);
        limparTela();

        realizarJogadaAdversario(tabuleiroJogador);
        getchar(); // Espera o ENTER

        if (verificarNaviosAfundados(tabuleiroJogador)) {
            printf("Que pena! Todos os seus navios foram afundados!\n");
            getchar(); // Espera o ENTER
            printf("Aguarde para jogar de novo!\n");
            delay(5);
            vencedor = 2; // Adversário venceu
            jogoContinua = 0;
            break;
        }

        printf("\nPressione ENTER para continuar...");
        getchar(); // Espera o ENTER
        limparTela();
    }

    salvarResultados(vencedor, disparosJogador, disparosAdversario, TAMANHO_TABULEIRO);
}

void delay(int t) {
    // Adaptação para diferentes sistemas operacionais
    #ifdef _WIN32
        Sleep(t * 1000); // Atraso de 1 segundo (1000 milissegundos) para Windows
    #else
        usleep(t * 1000000); // Atraso de 1 segundo (1000000 microssegundos) para Linux/Unix
    #endif
}

void limparTela() {
    // Adaptação para diferentes sistemas operacionais
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

void inicializarTabuleiro(int tabuleiro[][TAMANHO_TABULEIRO]) {
    for (int i = 0; i < TAMANHO_TABULEIRO; i++) {
        for (int j = 0; j < TAMANHO_TABULEIRO; j++) {
            tabuleiro[i][j] = 0;
        }
    }
}

void mostrarTabuleiro(int tabuleiro[][TAMANHO_TABULEIRO]) {
    // Imprimir a malha superior
    printf("   ");
    for (int i = 0; i < TAMANHO_TABULEIRO; i++) {
        printf("%d ", i);
    }
    printf("\n");

    // Imprimir a malha lateral e o tabuleiro
    for (int i = 0; i < TAMANHO_TABULEIRO; i++) {
        printf("%d ", i); // Índice lateral
        for (int j = 0; j < TAMANHO_TABULEIRO; j++) {
            if (j == 0)
                printf("|"); // Borda lateral
            if (tabuleiro[i][j] == -1) {
                printf("X ");
            } else if (tabuleiro[i][j] == 0) {
                printf("~ ");
            } else {
                printf("%d ", tabuleiro[i][j]);
            }
            if (j == TAMANHO_TABULEIRO - 1)
                printf("|"); // Borda lateral
        }
        printf("\n");
    }

    // Imprimir a malha inferior
    printf("  ");
    for (int i = 0; i < TAMANHO_TABULEIRO * 2 + 1; i++) {
        printf("-");
    }
    printf("\n");
}

int inserirNavioManual(int tabuleiro[][TAMANHO_TABULEIRO], int tipo, int tamanho) {
    int linha, coluna, orientacao;
    limparTela();
    mostrarTabuleiro(tabuleiro);
    printf("Montando seu tabuleiro:\n -> Inserindo o navio de tamanho %d \n   1 -> Submarino\n   2 -> Fragata\n"
           "   3 -> Destroyer\n   4 -> Porta-avião\n", tamanho);
    do {
        printf("Escolha a orientação (0 para horizontal, 1 para vertical): ");
        scanf("%d", &orientacao);
    } while (orientacao != 0 && orientacao != 1);
    printf("Escolha a linha (0-%d): ", TAMANHO_TABULEIRO - 1);
    scanf("%d", &linha);
    printf("Escolha a coluna (0-%d): ", TAMANHO_TABULEIRO - 1);
    scanf("%d", &coluna);

    if (orientacao == 0) {
        if (coluna + tamanho > TAMANHO_TABULEIRO) {
            printf("Navio fora do limite do tabuleiro! Tente novamente.\n");
            delay(2);
            return 0;
        }
        for (int i = 0; i < tamanho; i++) {
            if (tabuleiro[linha][coluna + i] != 0) {
                printf("Espaço ocupado! Tente novamente.\n");
                delay(2);
                return 0;
            }
        }
        for (int i = 0; i < tamanho; i++) {
            tabuleiro[linha][coluna + i] = tipo;
        }
    } else {
        if (linha + tamanho > TAMANHO_TABULEIRO) {
            printf("Navio fora do limite do tabuleiro! Tente novamente.\n");
            delay(2);
            return 0;
        }
        for (int i = 0; i < tamanho; i++) {
            if (tabuleiro[linha + i][coluna] != 0) {
                printf("Espaço ocupado! Tente novamente.\n");
                delay(2);
                return 0;
            }
        }
        for (int i = 0; i < tamanho; i++) {
            tabuleiro[linha + i][coluna] = tipo;
        }
    }
    return 1;
}

void montarTabuleiroJogador(int tabuleiro[][TAMANHO_TABULEIRO]) {
    int sucesso;

    for (int i = 0; i < submarinos; i++) {
        do {
            sucesso = inserirNavioManual(tabuleiro, SUBMARINO, 1);
        } while (!sucesso);
    }
    for (int i = 0; i < fragatas; i++) {
        do {
            sucesso = inserirNavioManual(tabuleiro, FRAGATA, 2);
        } while (!sucesso);
    }
    for (int i = 0; i < destroyers; i++) {
        do {
            sucesso = inserirNavioManual(tabuleiro, DESTROYER, 3);
        } while (!sucesso);
    }
    for (int i = 0; i < portaAvioes; i++) {
        do {
            sucesso = inserirNavioManual(tabuleiro, PORTA_AVIAO, 4);
        } while (!sucesso);
    }
}

void montarTabuleiroAdversario(int tabuleiro[][TAMANHO_TABULEIRO]) {
    srand(time(NULL));

    for (int i = 0; i < submarinos; i++) {
        inserirNavioAutomatico(tabuleiro, SUBMARINO, 1);
    }
    for (int i = 0; i < fragatas; i++) {
        inserirNavioAutomatico(tabuleiro, FRAGATA, 2);
    }
    for (int i = 0; i < destroyers; i++) {
        inserirNavioAutomatico(tabuleiro, DESTROYER, 3);
    }
    for (int i = 0; i < portaAvioes; i++) {
        inserirNavioAutomatico(tabuleiro, PORTA_AVIAO, 4);
    }
}

void realizarJogadaJogador(int tabuleiroAdversario[][TAMANHO_TABULEIRO], int tabuleiroJogadas[][TAMANHO_TABULEIRO], int tabuleiroJogador[][TAMANHO_TABULEIRO]) {
    int linha, coluna;
    do {
        printf("Escolha a linha (0-%d): ", TAMANHO_TABULEIRO - 1);
        scanf("%d", &linha);
        printf("Escolha a coluna (0-%d): ", TAMANHO_TABULEIRO - 1);
        scanf("%d", &coluna);

        if (linha < 0 || linha >= TAMANHO_TABULEIRO || coluna < 0 || coluna >= TAMANHO_TABULEIRO) {
            printf("Posição inválida! Tente novamente.\n");
        } else if (tabuleiroJogadas[linha][coluna] != 0) {
            printf("Você já jogou nesta posição! Tente novamente.\n");
        }
    } while (linha < 0 || linha >= TAMANHO_TABULEIRO || coluna < 0 || coluna >= TAMANHO_TABULEIRO || tabuleiroJogadas[linha][coluna] != 0);

    disparosJogador++; // Incrementa o contador de disparos do jogador

    if (tabuleiroAdversario[linha][coluna] != 0) {
        tabuleiroJogadas[linha][coluna] = tabuleiroAdversario[linha][coluna];
        tabuleiroAdversario[linha][coluna] = -1; // Marca o acerto no tabuleiro do adversário
        limparTela();
        printf("Seu tabuleiro:\n");
        mostrarTabuleiro(tabuleiroJogador);
        printf("\nSuas jogadas:\n");
        mostrarTabuleiro(tabuleiroJogadas);
        printf("\nRealize sua jogada:\n");
        printf("Você acertou um navio!\n");
    } else {
        tabuleiroJogadas[linha][coluna] = -1; // Marca o disparo no tabuleiro de jogadas
        limparTela();
        printf("Seu tabuleiro:\n");
        mostrarTabuleiro(tabuleiroJogador);
        printf("\nSuas jogadas:\n");
        mostrarTabuleiro(tabuleiroJogadas);
        printf("\nRealize sua jogada:\n");
        printf("Você errou!\n");
    }
}

void realizarJogadaAdversario(int tabuleiroJogador[][TAMANHO_TABULEIRO]) {
    int linha, coluna;
    linha = rand() % TAMANHO_TABULEIRO;
    coluna = rand() % TAMANHO_TABULEIRO;

    disparosAdversario++; // Incrementa o contador de disparos do adversário

    if (tabuleiroJogador[linha][coluna] != 0) {
        printf("O adversário acertou um navio seu!\n");
        tabuleiroJogador[linha][coluna] = -1; // Marca o acerto no tabuleiro do jogador
    } else {
        printf("O adversário errou!\n");
        tabuleiroJogador[linha][coluna] = -1; // Marca o disparo no tabuleiro de jogadas
    }
}

int verificarNaviosAfundados(int tabuleiro[][TAMANHO_TABULEIRO]) {
    for (int i = 0; i < TAMANHO_TABULEIRO; i++) {
        for (int j = 0; j < TAMANHO_TABULEIRO; j++) {
            if (tabuleiro[i][j] > 0) {
                return 0; // Ainda existem navios não afundados
            }
        }
    }
    return 1; // Todos os navios foram afundados
}

void inserirNavioAutomatico(int tabuleiro[][TAMANHO_TABULEIRO], int tipo, int tamanho) {
    int orientacao, linha, coluna;
    int valido = 0;
    while (!valido) {
        orientacao = rand() % 2; // 0 para horizontal, 1 para vertical
        if (orientacao == 0) {
            linha = rand() % TAMANHO_TABULEIRO;
            coluna = rand() % (TAMANHO_TABULEIRO - tamanho + 1);
            valido = 1;
            for (int i = 0; i < tamanho; i++) {
                if (tabuleiro[linha][coluna + i] != 0) {
                    valido = 0;
                    break;
                }
            }
            if (valido) {
                for (int i = 0; i < tamanho; i++) {
                    tabuleiro[linha][coluna + i] = tipo;
                }
            }
        } else {
            linha = rand() % (TAMANHO_TABULEIRO - tamanho + 1);
            coluna = rand() % TAMANHO_TABULEIRO;
            valido = 1;
            for (int i = 0; i < tamanho; i++) {
                if (tabuleiro[linha + i][coluna] != 0) {
                    valido = 0;
                    break;
                }
            }
            if (valido) {
                for (int i = 0; i < tamanho; i++) {
                    tabuleiro[linha + i][coluna] = tipo;
                }
            }
        }
    }
}

void salvarResultados(int vencedor, int disparosJogador, int disparosAdversario, int tamanhoTabuleiro) {
    limparTela();
    printf("Qual seu nome de jogador?\nInsira seu nome: ");
    char nome_jogador[50];
    scanf("%s", nome_jogador);

    FILE *arquivo = fopen("resultados.txt", "a");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo de resultados.\n");
        return;
    }
    fprintf(arquivo, "Jogador: %s\n", nome_jogador);
    fprintf(arquivo, "Vencedor: %s\n", vencedor == 1 ? "Jogador" : "Adversário");
    fprintf(arquivo, "Disparos do Jogador: %d\n", disparosJogador);
    fprintf(arquivo, "Disparos do Adversário: %d\n", disparosAdversario);
    fprintf(arquivo, "Tamanho do Tabuleiro: %dx%d\n", tamanhoTabuleiro,tamanhoTabuleiro);
    fprintf(arquivo, "-----------------------------\n");
    fclose(arquivo);
}

void verPontuacao() {
    limparTela();
    FILE *arquivo = fopen("resultados.txt", "r");
    if (arquivo == NULL) {
        printf("Nenhuma pontuação registrada.\n");
    } else {
        char linha[256];
        printf("=== PONTUAÇÃO ===\n");
        while (fgets(linha, sizeof(linha), arquivo)) {
            printf("%s", linha);
        }
        fclose(arquivo);
    }
    printf("\nPressione ENTER para voltar ao menu...");
    getchar(); // Espera o ENTER
}
