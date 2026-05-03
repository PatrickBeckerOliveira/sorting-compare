#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void gerarRandom(const char *nome, int n)
{
    FILE *f = fopen(nome, "w");

    for (int i = 0; i < n; i++)
    {
        fprintf(f, "%d\n", rand() % (n * 10));
    }

    fprintf(f, "\n"); // linha em branco final
    fclose(f);
}

void gerarSorted(const char *nome, int n)
{
    FILE *f = fopen(nome, "w");

    for (int i = 1; i <= n; i++)
    {
        fprintf(f, "%d\n", i);
    }

    fprintf(f, "\n");
    fclose(f);
}

void gerarReverse(const char *nome, int n)
{
    FILE *f = fopen(nome, "w");

    for (int i = n; i >= 1; i--)
    {
        fprintf(f, "%d\n", i);
    }

    fprintf(f, "\n");
    fclose(f);
}

int main()
{
    srand(time(NULL));

    int tamanhos[] = {100, 1000, 10000, 100000};
    int qtd = 4;

    char nome[50];

    for (int i = 0; i < qtd; i++)
    {
        int n = tamanhos[i];

        // RANDOM
        sprintf(nome, "%d_random.txt", n);
        gerarRandom(nome, n);

        // SORTED
        sprintf(nome, "%d_sorted.txt", n);
        gerarSorted(nome, n);

        // REVERSE
        sprintf(nome, "%d_reverse.txt", n);
        gerarReverse(nome, n);
    }

    printf("Arquivos de teste gerados com sucesso!\n");

    return 0;
}