#include "jogo.h"

int main() {
    int escolha;
    do {
        mostrarMenu();
        printf("Escolha uma opção: ");
        scanf("%d", &escolha);
        getchar(); // Limpa o buffer de entrada
        limparTela();

        switch (escolha) {
            case 1:
                iniciarJogo();
                break;
            case 2:
                regrasJogo();
                break;
            case 3:
                verPontuacao();
                break;
            case 4:
                printf("Saindo do jogo...\n");
                break;
            default:
                printf("Opção inválida! Tente novamente.\n");
        }
    } while (escolha != 4);

    return 0;
}
