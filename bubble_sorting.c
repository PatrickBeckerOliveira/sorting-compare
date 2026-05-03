#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

int bubbleSort(int v[], int n)
{
    int i, j, temp;
    bool swapped;
    long op = 0;

    for(i=0;i<n-1;i++)
    {
        swapped = false;            // operation 1
        op++;

        for(j=0;j<n-i-1;j++)
        {
            op++;
            if(v[j] > v[j+1])       // operation 2
            {
                temp = v[j];        // operation 3
                v[j] = v[j+1];      // operation 4
                v[j+1] = temp;      // operation 5
                swapped = true;     // operation 6
                op += 4;
            }
        }

        if (!swapped)
            return op;
    }

    return op;
}

int main() 
{
    printf("Name of file: ");
    
    char arquivo[50];
    scanf("%s", arquivo);
    FILE *f = fopen(arquivo, "r");

    if (f == NULL)
    {
        printf("Error opening file\n");
        return 0;
    }

    char linha[16];
    int lista[100000];
    int N = 0;

    while (fgets(linha, sizeof(linha), f) != NULL && strcmp(linha, "\n") != 0)
    {
        lista[N] = atoi(linha);
        N++;
    }

    fclose(f);

    printf("Number of operations: %ld", bubbleSort(lista, N));
    return 0;
}