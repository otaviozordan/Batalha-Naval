#ifndef TABULEIRO_H
#define TABULEIRO_H

#define TAMANHO_TABULEIRO 4 // ou qualquer outro tamanho padrão que você desejar

void inicializarTabuleiro(int tabuleiro[][TAMANHO_TABULEIRO]);
void mostrarTabuleiro(int tabuleiro[][TAMANHO_TABULEIRO]);
int inserirNavioManual(int tabuleiro[][TAMANHO_TABULEIRO], int tipo, int tamanho);
void inserirNavioAutomatico(int tabuleiro[][TAMANHO_TABULEIRO], int tipo, int tamanho);

#endif /* TABULEIRO_H */
