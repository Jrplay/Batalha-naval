/*
 * batalha_naval_novato.c
 *
 * Módulo Novato - Batalha Naval (versão simplificada)
 * Objetivo: representar um tabuleiro usando vetores (array 1D)
 *           e posicionar navios horizontais usando loops.
 *
 * Autor: [Seu Nome]
 * Data: [coloque a data]
 *
 * Explicação rápida:
 * - O tabuleiro é uma linha de N casas (vetor de chars).
 * - Navios são posicionados fornecendo uma posição inicial e comprimento.
 * - O programa demonstra posicionamento de 2 navios e imprime o tabuleiro.
 *
 * Compile:
 *   gcc batalha_naval_novato.c -o batalha_naval_novato
 * Execute:
 *   ./batalha_naval_novato
 */

#include <stdio.h>

#define TAM_TABULEIRO 10   // tamanho do tabuleiro (vetor 1D)
#define MAX_NAVIOS 5       // limite para demonstração

// Estrutura simples para definir um navio (usamos tipos inteiros e string)
typedef struct {
    int inicio;    // índice inicial (0..TAM_TABULEIRO-1)
    int tamanho;   // número de casas ocupadas
    char nome[20]; // nome curto do navio (opcional, não obrigatório)
} Navio;

/* Função para inicializar o tabuleiro com água '~' */
void inicializar_tabuleiro(char tab[]) {
    for (int i = 0; i < TAM_TABULEIRO; i++) {
        tab[i] = '~';
    }
}

/* Função para posicionar um navio no tabuleiro (horizontal em linha única)
   Retorna 1 se sucesso, 0 se erro (ex: fora do limite ou sobreposição) */
int posicionar_navio(char tab[], Navio navio) {
    // verifica limites
    if (navio.inicio < 0 || navio.inicio >= TAM_TABULEIRO) {
        return 0;
    }
    if (navio.inicio + navio.tamanho - 1 >= TAM_TABULEIRO) {
        return 0;
    }

    // verifica sobreposição
    for (int i = navio.inicio; i < navio.inicio + navio.tamanho; i++) {
        if (tab[i] == 'S') { // já ocupado
            return 0;
        }
    }

    // posiciona
    for (int i = navio.inicio; i < navio.inicio + navio.tamanho; i++) {
        tab[i] = 'S';
    }
    return 1;
}

/* Função para imprimir o tabuleiro com índices */
void imprimir_tabuleiro(const char tab[]) {
    printf("Índices: ");
    for (int i = 0; i < TAM_TABULEIRO; i++) {
        printf("%2d ", i);
    }
    printf("\nCasas  : ");
    for (int i = 0; i < TAM_TABULEIRO; i++) {
        printf(" %c ", tab[i]);
    }
    printf("\n");
}

int main() {
    char tabuleiro[TAM_TABULEIRO];
    Navio listaNavios[MAX_NAVIOS];

    // --- Inicializa navios de exemplo (você pode alterar) ---
    // Exemplo 1: navio pequeno de tamanho 3 começando na posição 1
    listaNavios[0].inicio = 1;
    listaNavios[0].tamanho = 3;
    snprintf(listaNavios[0].nome, sizeof(listaNavios[0].nome), "Corveta");

    // Exemplo 2: navio médio de tamanho 4 começando na posição 5
    listaNavios[1].inicio = 5;
    listaNavios[1].tamanho = 4;
    snprintf(listaNavios[1].nome, sizeof(listaNavios[1].nome), "Fragata");

    int quantidadeNavios = 2; // número de navios definidos acima

    // --- Inicializa o tabuleiro ---
    inicializar_tabuleiro(tabuleiro);

    // --- Posiciona os navios (usando loop for) ---
    for (int n = 0; n < quantidadeNavios; n++) {
        int sucesso = posicionar_navio(tabuleiro, listaNavios[n]);
        if (sucesso) {
            printf("Navio '%s' posicionado em inicio=%d tamanho=%d\n",
                   listaNavios[n].nome, listaNavios[n].inicio, listaNavios[n].tamanho);
        } else {
            printf("Erro ao posicionar navio '%s' (inicio=%d tamanho=%d)\n",
                   listaNavios[n].nome, listaNavios[n].inicio, listaNavios[n].tamanho);
        }
    }

    printf("\nTabuleiro final:\n");
    imprimir_tabuleiro(tabuleiro);

    // --- Exemplo simples de verificação de área (contagem de partes de navio) ---
    int partesNavio = 0;
    for (int i = 0; i < TAM_TABULEIRO; i++) {
        if (tabuleiro[i] == 'S') partesNavio++;
    }
    printf("\nTotal de casas ocupadas por navios: %d\n", partesNavio);

    return 0;
}