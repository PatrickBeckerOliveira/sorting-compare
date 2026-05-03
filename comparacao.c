#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX 100000

// ================= LEITURA =================
int lerArquivo(const char *nome, int v[])
{
    FILE *f = fopen(nome, "r");
    if (!f) return -1;

    char linha[32];
    int n = 0;

    while (fgets(linha, sizeof(linha), f) != NULL && strcmp(linha, "\n") != 0)
    {
        v[n++] = atoi(linha);
    }

    fclose(f);
    return n;
}

// ================= BUBBLE =================
long bubbleSort(int v[], int n)
{
    int i, j, temp;
    bool swapped;
    long op = 0;

    for(i=0;i<n-1;i++)
    {
        swapped = false; op++;

        for(j=0;j<n-i-1;j++)
        {
            op++;
            if(v[j] > v[j+1])
            {
                temp = v[j];
                v[j] = v[j+1];
                v[j+1] = temp;
                swapped = true;
                op += 4;
            }
        }

        if (!swapped) break;
    }

    return op;
}

// ================= QUICK =================
int partition(int arr[], int low, int high, long *op)
{
    int pivot = arr[low]; (*op)++;
    int i = low - 1; (*op)++;
    int j = high + 1; (*op)++;

    while (1)
    {
        do { i++; (*op)++; (*op)++; } while (arr[i] < pivot);
        do { j--; (*op)++; (*op)++; } while (arr[j] > pivot);

        (*op)++;
        if (i >= j) return j;

        int temp = arr[i]; (*op)++;
        arr[i] = arr[j]; (*op)++;
        arr[j] = temp; (*op)++;
    }
}

void quickSort(int arr[], int low, int high, long *op)
{
    (*op)++;
    if (low < high)
    {
        int pi = partition(arr, low, high, op); (*op)++;
        quickSort(arr, low, pi, op);
        quickSort(arr, pi + 1, high, op);
    }
}

// ================= COUNTING =================
long countingSort(int arr[], int n)
{
    long op = 0;
    int max = 0;

    for (int i = 0; i < n; i++)
    {
        op++;
        if (arr[i] > max)
        {
            max = arr[i]; op++;
        }
    }

    int *count = calloc(max + 1, sizeof(int)); op++;

    for (int i = 0; i < n; i++)
    {
        count[arr[i]]++; op++;
    }

    for (int i = 1; i <= max; i++)
    {
        count[i] += count[i-1]; op++;
    }

    int *out = malloc(n * sizeof(int)); op++;

    for (int i = n-1; i >= 0; i--)
    {
        out[count[arr[i]] - 1] = arr[i]; op++;
        count[arr[i]]--; op++;
    }

    for (int i = 0; i < n; i++)
    {
        arr[i] = out[i]; op++;
    }

    free(count); op++;
    free(out); op++;

    return op;
}

// ================= MAIN =================
int main()
{
    char nomes[100][50];  // até 100 arquivos
    int qtd = 0;

    printf("Digite os nomes dos arquivos (digite 'fim' para terminar):\n");

    while (1)
    {
        scanf("%s", nomes[qtd]);

        if (strcmp(nomes[qtd], "fim") == 0)
            break;

        qtd++;
    }

    FILE *html = fopen("resultado.html", "w");

    fprintf(html, "<html><head><title>PAA - Trabalho 2</title></head><body><table border=1>");
    fprintf(html, "<tr><th>Arquivo</th><th>BubbleSort</th><th>QuickSort</th><th>CountingSort</th></tr>");

    for (int i = 0; i < qtd; i++)
    {
        int v[100000], v2[100000], v3[100000];

        int n = lerArquivo(nomes[i], v);
        if (n <= 0) continue;

        for (int j = 0; j < n; j++)
        {
            v2[j] = v[j];
            v3[j] = v[j];
        }

        long opBubble = bubbleSort(v, n);

        long opQuick = 0;
        quickSort(v2, 0, n-1, &opQuick);

        long opCount = countingSort(v3, n);

        fprintf(html,
            "<tr><td>%s</td><td>%ld</td><td>%ld</td><td>%ld</td></tr>",
            nomes[i], opBubble, opQuick, opCount);
    }

    fprintf(html, "</table></body></html>");
    fclose(html);

    printf("Arquivo resultado.html gerado!\n");

    return 0;
}