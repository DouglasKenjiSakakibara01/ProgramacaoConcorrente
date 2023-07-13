#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <pthread.h>
#include <math.h>
#include <sys/time.h> //biblioteca do linux

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
    if (argc < 1)
    {
        printf("Numero de argumentos incorreto");
        return 1;
    }
    tam = argv[1];
    struct timeval inicio_execucao, fim_execucao;
    double tempo_execucao;
    aloca_matriz();
    // registra o tempo de início da execucao
    gettimeofday(&inicio_execucao, NULL);
    calcula_matriz();

    // registra o tempo do fim da execucao
    gettimeofday(&fim_execucao, NULL);
    // tempo de execução em segundos
    tempo_execucao = (fim_execucao.tv_sec - inicio_execucao.tv_sec) + (fim_execucao.tv_usec - inicio_execucao.tv_usec) / 1000000.0;
    prinft("Tempo de execucao: %d segundos", &tempo_execucao);
}