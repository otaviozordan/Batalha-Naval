#ifndef JOGO_H
#define JOGO_H

#include <stdio.h>
#include <stdlib.h>
// Deixar o jogo mais dinâmico
#include <string.h>
#include <time.h>

// Verificar em qual sistema operacional está rodando e incluir as bibliotecas
// faltantes
#ifdef _WIN32
#include <windows.h>
#else
#include <unistd.h>
#endif

// Definindo o tamanho de cada navio no tabuleiro
#define SUBMARINO 1
#define FRAGATA 2
#define DESTROYER 3
#define PORTA_AVIAO 4
#define CODIGO_DESENVOLVEDOR 1234


// Declaração das variáveis globais como externas
extern int TAMANHO_TABULEIRO;
extern int submarinos;
extern int fragatas;
extern int destroyers;
extern int portaAvioes;
extern int disparosJogador;
extern int disparosAdversario;
extern int vencedor;

// Informar o código que existe funções próprias que não serão utilizadas nesse
// momento
void mostrarMenu();
void selecionarDificuldade();
void definirDificuldade(int dificuldade);
void regrasJogo();
void iniciarJogo();
void delay(int t);
void limparTela();
void inicializarTabuleiro(int tabuleiro[][8]);
void mostrarTabuleiro(int tabuleiro[][8]);
int inserirNavioManual(int tabuleiro[][8], int tipo, int tamanho);
void montarTabuleiroJogador(int tabuleiro[][8]);
void montarTabuleiroAdversario(int tabuleiro[][8]);
void realizarJogadaJogador(int tabuleiroAdversario[][8],
                           int tabuleiroJogadas[][8],
                           int tabuleiroJogador[][8]);
 int verificarNaviosAfundados(int tabuleiro[][8]);
 void inserirNavioAutomatico(int tabuleiro[][8], int tipo, int tamanho);
 void salvarResultados(int vencedor, int disparosJogador,
                       int disparosAdversario, int tamanhoTabuleiro);
 void verPontuacao();

 void realizarJogadaAdversario(int tabuleiroJogador[][TAMANHO_TABULEIRO],
                               int tabuleiroDisparos[][TAMANHO_TABULEIRO],
                               int *proxpasso, int *rept, int *ultimaLinha,
                               int *ultimaColuna, int *pos);

 void proxPassoFuncao(int acertou, int *proxpasso, int *pos);

#endif
