#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#define seed 1

int num_threads, tam;
float **matrizA;
float **matrizB;
float **matrizResultante;

void aloca_matriz()
{
    int i;
    matrizA = (float **)malloc(sizeof(float *) * tam);
    matrizB = (float **)malloc(sizeof(float *) * tam);
    matrizResultante = (float **)malloc(sizeof(float *) * tam);
    for (i = 0; i < tam; i++)
    {
        matrizA[i] = (float *)malloc(sizeof(float) * tam);
        matrizB[i] = (float *)malloc(sizeof(float) * tam);
        matrizResultante[i] = (float *)malloc(sizeof(float) * tam);
    }
}
void gera_matriz()
{
    int i, j;
    srand(seed);

    for (i = 0; i < tam; i++)
    {
        for (j = 0; j < tam; j++)
        {
            // gera numeros aleatorios de 0.0 a 9.0
            matrizA[i][j] = ((float)rand() / RAND_MAX) * 9.0;
            matrizB[i][j] = ((float)rand() / RAND_MAX) * 9.0;
        }
    }
}

void imprime_matriz(float **matriz)
{
    int i, j;

    for (i = 0; i < tam; i++)
    {
        for (j = 0; j < tam; j++)
        {
            printf("%.2f ", matriz[i][j]);
        }
        printf("\n");
    }
}

void calcula_matriz()
{
    int i, j, k;
    for (i = 0; i < tam; i++)
    {
        for (j = 0; j < tam; j++)
        {
            matrizResultante[i][j] = 0.0;
            for (k = 0; k < tam; k++)
            {
                matrizResultante[i][j] += matrizA[i][k] * matrizB[k][j];
            }
        }
    }
}

int main(int argc, char *argv[])
{
    /*
    if (argc < 1)
    {
        printf("Numero de argumentos incorreto");
        return 1;
    }
    */
    // tam = argv[1];
    tam = 100;
    clock_t inicio_execucao, fim_execucao;
    double tempo_execucao;

    /*
    struct timeval inicio_execucao, fim_execucao;
    double tempo_execucao;
    */
    aloca_matriz();
    gera_matriz();

    inicio_execucao = clock();
    calcula_matriz();
    //  registra o tempo de início da execucao
    /*
    gettimeofday(&inicio_execucao, NULL);
    calcula_matriz();
    */

    fim_execucao = clock();
    /*
    //  registra o tempo do fim da execucao
    gettimeofday(&fim_execucao, NULL);
    */

    tempo_execucao = ((double)(fim_execucao - inicio_execucao)) / CLOCKS_PER_SEC; // Calcula o tempo de execução em segundos
    printf("Tempo de execucao: %f segundos\n", tempo_execucao);
    /*
    // tempo de execução em segundos
    tempo_execucao = (fim_execucao.tv_sec - inicio_execucao.tv_sec) + (fim_execucao.tv_usec - inicio_execucao.tv_usec) / 1000000.0;
    prinft("Tempo de execucao: %d segundos", &tempo_execucao);
    */
}