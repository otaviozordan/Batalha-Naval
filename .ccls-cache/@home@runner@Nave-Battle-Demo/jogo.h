#ifndef JOGO_H
#define JOGO_H

#include <stdio.h>
#include <stdlib.h>
// Deixar o jogo mais dinâmico
#include <time.h>
#include <string.h>

// Verificar em qual sistema operacional está rodando e incluir as bibliotecas faltantes
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

// Declaração das variáveis globais como externas
extern int TAMANHO_TABULEIRO;
extern int submarinos;
extern int fragatas;
extern int destroyers;
extern int portaAvioes;
extern int disparosJogador;
extern int disparosAdversario;
extern int vencedor;


// Informar o código que existe funções próprias que não serão utilizadas nesse momento
void delay(int t);
void limparTela();
void inicializarTabuleiro(int tabuleiro[][TAMANHO_TABULEIRO]);
void mostrarTabuleiro(int tabuleiro[][TAMANHO_TABULEIRO]);
int inserirNavioManual(int tabuleiro[][TAMANHO_TABULEIRO], int tipo, int tamanho);
void montarTabuleiroJogador(int tabuleiro[][TAMANHO_TABULEIRO]);
void montarTabuleiroAdversario(int tabuleiro[][TAMANHO_TABULEIRO]);
void realizarJogadaJogador(int tabuleiroAdversario[][TAMANHO_TABULEIRO], int tabuleiroJogadas[][TAMANHO_TABULEIRO], int tabuleiroJogador[][TAMANHO_TABULEIRO]);
void realizarJogadaAdversario(int tabuleiroJogador[][TAMANHO_TABULEIRO]);
int verificarNaviosAfundados(int tabuleiro[][TAMANHO_TABULEIRO]);
void inserirNavioAutomatico(int tabuleiro[][TAMANHO_TABULEIRO], int tipo, int tamanho);
void mostrarMenu();
void regrasJogo();
void iniciarJogo();
void salvarResultados(int vencedor, int disparosJogador, int disparosAdversario, int tamanhoTabuleiro);
void verPontuacao();
void selecionarDificuldade();
void definirDificuldade(int dificuldade);

#endif
