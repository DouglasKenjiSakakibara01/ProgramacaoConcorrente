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

void calcula_matriz(int indice_thread)
{
    int passo = floor(tam / num_threads);
    int inicio = indice_thread * passo;
    int resto = tam % num_threads; // Se o resto da divisao for diferente de zero a divisao para cada thread nao vai ser igual
    int fim;
    // Caso o resto seja diferente de 0 a ultima thread fica responsavel pela multiplicacao das ultimas linhas que restaram
    if (resto != 0 && (indice_thread == num_threads - 1))
    {
        fim = tam - 1;
    }
    else
    {
        fim = inicio + passo;
    }

    for (int i = inicio; i <= fim; i++)
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
    if (argc < 2)
    {
        printf("Numero de argumentos incorreto");
        return 1;
    }
    /*
    num_threads = 2;
    tam = 100;
    pthread_t threads[num_threads];
    */

    pthread_t *threads;
    num_threads = argv[1];
    tam = argv[2];
    threads = (pthread_t *)malloc(num_threads * sizeof(pthread_t));

    for (int i = 0; i < num_threads; i++)
    {
        pthread_create(&threads[i], NULL, calcula_matriz, i);
    }

    for (int i = 0; i < num_threads; i++)
    {
        pthread_join(threads[i], NULL);
    }

    return 0;
}
