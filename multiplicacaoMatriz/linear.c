#include <stdio.h>
#include <conio.h>
#define tam 100

float a[tam][tam];
float b[tam][tam];
float res[tam][tam];

void imprime_matriz()
{
}

void calcula_matriz()
{
    for (int i = 0; i < tam; i++)
    {
        for (int j = 0; j < tam; j++)
        {
            res[i][j] = 0;
            for (int k = 0; k < tam; k++)
            {
                res[i][j] += a[i][k] * b[k][j];
            }
        }
    }
}