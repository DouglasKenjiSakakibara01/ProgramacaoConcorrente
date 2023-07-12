#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <pthread.h>
#include <math.h>
int num_threads, tam;
float **matrizA;
float **matrizB;
float **matrizResultante;

void aloca_matriz()
{
    matrizA = (float **)malloc(sizeof(float *) * tam);
    matrizB = (float **)malloc(sizeof(float *) * tam);
    matrizResultante = (float **)malloc(sizeof(float *) * tam);
    for (int i = 0; i < tam; i++)
    {
        matrizA[i] = (float *)malloc(sizeof(float) * tam);
        matrizB[i] = (float *)malloc(sizeof(float) * tam);
        matrizResultante[i] = (float *)malloc(sizeof(float) * tam);
    }
}
void gera_matriz()
{
    srand(time(NULL));

    for (int i = 0; i < tam; i++)
    {
        for (int j = 0; j < tam; j++)
        {
            // gera numeros aleatorios de 0.0 a 9.0
            matrizA[i][j] = ((float)rand() / RAND_MAX) * 9.0;
        }
    }
}
void imprime_matriz(float **matriz)
{

    for (int i = 0; i < tam; i++)
    {
        for (int j = 0; j < tam; j++)
        {
            printf("%.2f ", matriz[i][j]);
        }
        printf("\n");
    }
}

void calcula_matriz()
{

    for (int i = 0; i <= tam; i++)
    {
        for (int j = 0; j < tam; j++)
        {
            matrizResultante[j] = 0;
            for (int k = 0; k < tam; k++)
            {
                matrizResultante[i][j] += matrizA[i][k] * matrizB[k][j];
            }
        }
    }
}

int main(int argc, char *argv[])
{
}