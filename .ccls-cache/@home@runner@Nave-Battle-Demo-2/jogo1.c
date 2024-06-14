/////////////////////////////////////////////////////////////////////////////////////////

// O código foi dividido em três partes por conta de seu tamanho. Assim, fica
// mais organizado e é só pedir para a main.c puxar o jogo.h ou o jogo.c
#include "jogo.h"

// Variáveis globais para contagem de disparos
int disparosJogador = 0;
int disparosAdversario = 0;
int vencedor = 0; // 1 para jogador, 2 para adversário

// Variáveis globais para configuração do jogo, não importante
// Inicia e muda dependendo do modo de jogo
int TAMANHO_TABULEIRO = 4; // Tamanho padrão
int submarinos = 0;
int fragatas = 0;
int destroyers = 0;
int portaAvioes = 0;

////////////////////////////PARTE 1 MENUS DENTRO DO JOGO////////////////////////////////

//1.1 MENU DO JOGO
void mostrarMenu() {
  limparTela();
  printf("=== BATALHA NAVAL ===\n");
  printf("1. Iniciar Jogo\n");
  printf("2. Regras do Jogo\n");
  printf("3. Ver Pontuação\n");
  printf("4. Sair\n"); // sequencia de prints que cria o menu do jogo
}
//1.1 SELETOR DE DIFICULDADES
void selecionarDificuldade() {
  int dificuldade;
  do {
    limparTela();
    printf("=== SELECIONAR DIFICULDADE ===\n");
    printf("1. Fácil (Tabuleiro 3x3)\n");
    printf("2. Médio (Tabuleiro 4x4)\n");
    printf("3. Difícil (Tabuleiro 8x8)\n");
    printf("Escolha a dificuldade: "); // sequencia de prints que cria o menu de
                                       // seleção de dificuldades
    scanf("%d", &dificuldade); // recebe a dificuldade selecionada
  } while (dificuldade < 1 ||
           dificuldade > 3); // estrutura de repetição que garante que o usuário
                             // digite uma opção valida

  definirDificuldade(dificuldade);//função que define a dificuldade
}

//1.2 REGRAS DO JOGO
void regrasJogo() {
  limparTela();
  printf("=== REGRAS DO JOGO ===\n");
  printf("1. O objetivo do jogo é afundar todos os navios do adversário.\n");
  printf("2. Cada jogador posiciona seus navios no tabuleiro.\n");
  printf("3. Os jogadores se revezam para adivinhar a posição dos navios "
         "adversários.\n");
  printf("4. O jogo termina quando todos os navios de um jogador forem "
         "afundados.\n");
  printf("\nPressione ENTER para voltar ao menu...");//printa a regras
  getchar(); // Espera o ENTER
}

//////////////////////////PARTE 2 GERAÇÃO E EXIBIÇÃO DE TABULEIRO////////////////////

// 2.1 ADEQUA A DIFICULDADE AO TABULEIRO
void definirDificuldade(int dificuldade) {
  switch (dificuldade) {
  case 1:
    // Facil
    TAMANHO_TABULEIRO = 3;
    submarinos = 1;
    fragatas = 1;
    destroyers = 1;
    portaAvioes = 0;
    break;
  case 2:
    // Medio
    TAMANHO_TABULEIRO = 4;
    submarinos = 1;
    fragatas = 2;
    destroyers = 1;
    portaAvioes = 0;
    break;
  case 3:
    // Dificil
    TAMANHO_TABULEIRO = 8;
    submarinos = 3;
    fragatas = 2;
    destroyers = 2;
    portaAvioes = 1;
    break;
  }
}

// PARTE 2.2 SEQUENCIA LÓGICA DO JOGO E EXIBIÇÃO DE TABULEIROS
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

  disparosJogador = 0;    // Reset disparos do jogador
  disparosAdversario = 0; // Reset disparos do adversário
  vencedor = 0;           // Reset vencedor

  // Inicializa tudo 0
  inicializarTabuleiro(tabuleiroJogador);
  inicializarTabuleiro(tabuleiroJogadasJogador);
  inicializarTabuleiro(tabuleiroAdversario);

  // Tabuleiro de registro de disparos do adversário
  // Pressets que ditaram a randomicidade dos disparos
  int proxpasso = 0;
  int rept = 0;
  int ultimaLinha = -1;
  int ultimaColuna = -1;
  int pos = 0;
  int tabuleiroDisparosAdversario[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO];
  inicializarTabuleiro(tabuleiroDisparosAdversario);

  // Inicia a montagem do tabuleiro do jogador
  montarTabuleiroJogador(tabuleiroJogador);
  getchar(); // Espera o ENTER
  limparTela();

  // Inicia a montagem do tabuleiro do jogador
  printf("Montando o tabuleiro do adversário...\n");
  montarTabuleiroAdversario(tabuleiroAdversario);
  printf("\nPressione ENTER para continuar...");
  getchar(); // Espera o ENTER
  limparTela();

  // PARTE 2.2.1 ATUALIZAÇÃO DA TELA DURANTE O JOGO

  while (jogoContinua) {
    printf("Seu tabuleiro:\n");
    mostrarTabuleiro(tabuleiroJogador);
    printf("\nSuas jogadas:\n");
    mostrarTabuleiro(tabuleiroJogadasJogador);
    printf("\nRealize sua jogada:\n");
    realizarJogadaJogador(tabuleiroAdversario, tabuleiroJogadasJogador,
                          tabuleiroJogador);

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
    realizarJogadaAdversario(tabuleiroJogador, tabuleiroDisparosAdversario,
                             &proxpasso, &rept, &ultimaLinha, &ultimaColuna,
                             &pos);
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

  salvarResultados(vencedor, disparosJogador, disparosAdversario,
                   TAMANHO_TABULEIRO);
}

// PARTE 2.3 INICIALIZA OS TABULEIROS EM 0
void inicializarTabuleiro(int tabuleiro[][TAMANHO_TABULEIRO]) {
  for (int i = 0; i < TAMANHO_TABULEIRO; i++) {
    for (int j = 0; j < TAMANHO_TABULEIRO; j++) {
      tabuleiro[i][j] = 0;
    }
  }
}

// PARTE 2.4 INSERE NAVIOS
int inserirNavioManual(int tabuleiro[][TAMANHO_TABULEIRO], int tipo,
                       int tamanho) {
  int linha, coluna, orientacao;
  limparTela();
  mostrarTabuleiro(tabuleiro);
  printf("Montando seu tabuleiro:\n -> Inserindo o navio de tamanho %d \n   1 "
         "-> Submarino\n   2 -> Fragata\n"
         "   3 -> Destroyer\n   4 -> Porta-avião\n\n",
         tamanho);
  do {
    printf("->Escolha a orientação: \n   ->0 para horizontal\n   ->1 para "
           "vertical\n>>");
    scanf("%d", &orientacao);
  } while (orientacao != 0 && orientacao != 1);
  printf("\nEscolha a linha (0-%d)>> ", TAMANHO_TABULEIRO - 1);
  scanf("%d", &linha);
  printf("Escolha a coluna (0-%d)>> ", TAMANHO_TABULEIRO - 1);
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
// PARTE 2.5 EXIBINDO O TABULEIRO DO JOGADOR

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

// PARTE 2.6 GERANDO O TABULEIRO ADVERSÁRIO

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

// PARTE 2.7 INSERÇÃO DE NAVIOS ADVERSÁRIOS

void inserirNavioAutomatico(int tabuleiro[][TAMANHO_TABULEIRO], int tipo,
                            int tamanho) {
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

//////////////PARTE 3 REALIZANDO E JOGADA E VERIFICANDO COLISÃOES//////////////////

// PARTE 2.8 REALIZANDO JOGADAS

void realizarJogadaJogador(int tabuleiroAdversario[][TAMANHO_TABULEIRO],
                           int tabuleiroJogadas[][TAMANHO_TABULEIRO],
                           int tabuleiroJogador[][TAMANHO_TABULEIRO]) {
  int linha, coluna;
  do {
    printf("Escolha a linha (0-%d)>> ", TAMANHO_TABULEIRO - 1);
    scanf("%d", &linha);
    printf("Escolha a coluna (0-%d)>> ", TAMANHO_TABULEIRO - 1);
    scanf("%d", &coluna);

    if (linha == CODIGO_DESENVOLVEDOR) {
      limparTela();
      printf("\n*** Tabuleiro do Adversário ***\n");
      mostrarTabuleiro(tabuleiroAdversario);
      printf("\nMostrando tabuleiros por 3 segundos...\n");
      delay(3);
      limparTela();
      printf("Seu tabuleiro:\n");
      mostrarTabuleiro(tabuleiroJogador);
      printf("\nSuas jogadas:\n");
      mostrarTabuleiro(tabuleiroJogadas);
      printf("\nRealize sua jogada:\n");
      continue; // Reinicia o loop sem fazer a jogada do jogador
    }
    if (linha < 0 || linha >= TAMANHO_TABULEIRO || coluna < 0 ||
        coluna >= TAMANHO_TABULEIRO) {
      limparTela();
      printf("Posição inválida! Tente novamente.\n");
      printf("Seu tabuleiro:\n");
      mostrarTabuleiro(tabuleiroJogador);
      printf("\nSuas jogadas:\n");
      mostrarTabuleiro(tabuleiroJogadas);
      printf("\nRealize sua jogada:\n");
      continue; // Reinicia o loop sem fazer a jogada do jogador
    } else if (tabuleiroJogadas[linha][coluna] != 0) {
      limparTela();
      printf("Você já jogou nesta posição! Tente novamente.\n");
      printf("Seu tabuleiro:\n");
      mostrarTabuleiro(tabuleiroJogador);
      printf("\nSuas jogadas:\n");
      mostrarTabuleiro(tabuleiroJogadas);
      printf("\nRealize sua jogada:\n");
      continue; // Reinicia o loop sem fazer a jogada do jogador
    }
  } while (linha < 0 || linha >= TAMANHO_TABULEIRO || coluna < 0 ||
           coluna >= TAMANHO_TABULEIRO || tabuleiroJogadas[linha][coluna] != 0);

  disparosJogador++; // Incrementa o contador de disparos do jogador

/////// PARTE 3 VERIFICA SE ACERTOU
bv 

  if (tabuleiroAdversario[linha][coluna] != 0) {
    tabuleiroJogadas[linha][coluna] = tabuleiroAdversario[linha][coluna];
    tabuleiroAdversario[linha][coluna] =
        -1; // Marca o acerto no tabuleiro do adversário
    limparTela();
    printf("Seu tabuleiro:\n");
    mostrarTabuleiro(tabuleiroJogador);
    printf("\nSuas jogadas:\n");
    mostrarTabuleiro(tabuleiroJogadas);
    printf("\nRealize sua jogada:\n");
    printf("Você acertou um navio!\n");
  } else {
    tabuleiroJogadas[linha][coluna] =
        -1; // Marca o disparo no tabuleiro de jogadas
    limparTela();
    printf("Seu tabuleiro:\n");
    mostrarTabuleiro(tabuleiroJogador);
    printf("\nSuas jogadas:\n");
    mostrarTabuleiro(tabuleiroJogadas);
    printf("\nRealize sua jogada:\n");
    printf("Você errou!\n");
  }
}

// PARTE 3.1 VERIFICA SE TODOS OS NAVIOS JÁ AFUNDARAM

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

///////////////////////////PARTE 4 ALGORÍTIMO JOGANDO//////////////////
void realizarJogadaAdversario(int tabuleiroJogador[][TAMANHO_TABULEIRO],
                              int tabuleiroDisparos[][TAMANHO_TABULEIRO],
                              int *proxpasso, int *rept, int *ultimaLinha,
                              int *ultimaColuna, int *pos) {

  int linha, coluna;
  int acertou = 0;

  switch (*proxpasso) {
  case 0:
    srand(time(NULL));
    linha = rand() % TAMANHO_TABULEIRO;
    coluna = rand() % TAMANHO_TABULEIRO;
    break;
  case 1:
    linha = *ultimaLinha;
    coluna = *ultimaColuna;
    *pos = rand() % 3;
    if (*pos == 0 && coluna + 1 < TAMANHO_TABULEIRO)
      coluna++;
    else if (*pos == 1 && coluna - 1 >= 0)
      coluna--;
    else if (*pos == 2 && linha + 1 < TAMANHO_TABULEIRO)
      linha++;
    else if (*pos == 3 && linha - 1 >= 0)
      linha--;
    else {
      srand(time(NULL));

      linha = rand() % TAMANHO_TABULEIRO;
      coluna = rand() % TAMANHO_TABULEIRO;
    }

    break;
  case 2:
    coluna = *ultimaColuna + 1;
    linha = *ultimaLinha;
    (*rept)++;
    break;
  case 3:
    coluna = *ultimaColuna - 1;
    linha = *ultimaLinha;
    (*rept)++;
    break;
  case 4:
    linha = *ultimaLinha - 1;
    coluna = *ultimaColuna;
    (*rept)++;
    break;
  case 5:
    linha = *ultimaLinha + 1;
    coluna = *ultimaColuna;
    (*rept)++;
    break;
  case 6:
    linha = *ultimaLinha + (*rept + 2);
    coluna = *ultimaColuna;
    *rept = 0;
    break;
  case 7:
    linha = *ultimaLinha - (*rept + 2);
    coluna = *ultimaColuna;
    *rept = 0;
    break;
  case 8:
    linha = *ultimaLinha;
    coluna = *ultimaColuna + (*rept + 2);
    *rept = 0;
    break;
  case 9:
    linha = *ultimaLinha;
    coluna = *ultimaColuna - (*rept + 2);
    *rept = 0;
    break;
  }
  if (linha < 0 || linha < TAMANHO_TABULEIRO - 1 || coluna < 0 ||
      coluna < TAMANHO_TABULEIRO - 1) {
    srand(time(NULL));
    linha = rand() % TAMANHO_TABULEIRO;
    coluna = rand() % TAMANHO_TABULEIRO;
    *proxpasso = 0;
  }
  while (tabuleiroDisparos[linha][coluna] == 1) {
    srand(time(NULL));
    linha = rand() % TAMANHO_TABULEIRO;
    coluna = rand() % TAMANHO_TABULEIRO;
    *proxpasso = 0;
  }

  if (tabuleiroJogador[linha][coluna] != 0) {
    printf("O adversario acertou um navio seu!\n");
    tabuleiroJogador[linha][coluna] = -1;
    acertou = 1;
  } else {
    printf("O adversario errou!\n");
    tabuleiroJogador[linha][coluna] = -1;
  }

  tabuleiroDisparos[linha][coluna] = 1;
  *ultimaLinha = linha;
  *ultimaColuna = coluna;

  proxPassoFuncao(acertou, proxpasso, pos);
}

// PARTE 4.2 ALGORÍTIMO DEFININDO A JOGADA

void proxPassoFuncao(int acertou, int *proxpasso, int *pos) {
  if (acertou) {
    switch (*proxpasso) {
    case 0:
      *proxpasso = 1;
      break;
    case 1:
      switch (*pos) {
      case 1:

        *proxpasso = 2;
        break;
      case 2:

        *proxpasso = 3;
        break;
      case 3:

        *proxpasso = 5;
        break;
      case 4:

        *proxpasso = 4;
      }
    case 2:
      *proxpasso = 3;
      break;
    case 3:
      *proxpasso = 4;
      break;
    case 4:
      *proxpasso = 5;
      break;
    case 5:
      *proxpasso = 6;
      break;
    case 6:
      *proxpasso = 7;
      break;
    case 7:
      *proxpasso = 8;
      break;
    case 8:
      *proxpasso = 9;
      break;
    case 9:
      *proxpasso = 0;
      break;
    }
  } else {
    switch (*proxpasso) {
    case 0:
      *proxpasso = 0;
      break;
    case 1:
      *proxpasso = 7;
      break;
    case 2:
      *proxpasso = 7;
      break;
    case 3:
      *proxpasso = 6;
      break;
    case 4:
      *proxpasso = 8;
      break;
    case 5:
      *proxpasso = 9;
      break;
    case 6:
      *proxpasso = 0;
      break;
    case 7:
      *proxpasso = 0;
      break;
    case 8:
      *proxpasso = 0;
      break;
    case 9:
      *proxpasso = 0;
      break;
    }
  }
}


////////////////////PARTE 5 ARMAZENANDO RESULTADOS E RANKING///////////////////////

// PARTE 5.1 SALVA OS RESULTADOS

void salvarResultados(int vencedor, int disparosJogador, int disparosAdversario,
                      int tamanhoTabuleiro) {
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
  fprintf(arquivo, "Tamanho do Tabuleiro: %dx%d\n", tamanhoTabuleiro,
          tamanhoTabuleiro);
  fprintf(arquivo, "-----------------------------\n");
  fclose(arquivo);
}

// PARTE 5.2 MOSTRA OS RESULRTADOS

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


////////////////////PARTE 6 INTERFACES ///////////////////////

void delay(int t) {
// Adaptação para diferentes sistemas operacionais
#ifdef _WIN32
  Sleep(t * 1000); // Atraso de 1 segundo (1000 milissegundos) para Windows
#else
  usleep(
      t *
      1000000); // Atraso de 1 segundo (1000000 microssegundos) para Linux/Unix
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


