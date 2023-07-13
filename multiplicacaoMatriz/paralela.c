#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <pthread.h>
#include <math.h>
// #include <sys/time.h> //biblioteca do linux
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

void calcula_matriz(int indice_thread)
{
    int passo = floor(tam / num_threads);
    int inicio = indice_thread * passo;
    int resto = tam % num_threads; // Se o resto da divisao for diferente de zero a divisao para cada thread nao vai ser igual
    int fim;
    int i, j, k;
    // Caso o resto seja diferente de 0 a ultima thread fica responsavel pela multiplicacao das ultimas linhas que restaram
    if (resto != 0 && (indice_thread == num_threads - 1))
    {
        fim = tam - 1;
    }
    else
    {
        fim = inicio + passo;
    }

    for (i = inicio; i <= fim; i++)
    {
        for (j = 0; j < tam; j++)
        {
            matrizResultante[i][j] = 0;
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
    if (argc < 2)
    {
        printf("Numero de argumentos incorreto");
        return 1;
    }
    */
    int i;
    clock_t inicio_execucao, fim_execucao;
    double tempo_execucao;
    /*
    struct timeval inicio_execucao, fim_execucao;
    double tempo_execucao;
    */
    /*
    tam = 10;
    num_threads = 2;
    pthread_t threads[num_threads];
    */

    pthread_t *threads;
    num_threads = argv[1];
    tam = argv[2];
    threads = (pthread_t *)malloc(num_threads * sizeof(pthread_t));

    aloca_matriz();
    gera_matriz();
    inicio_execucao = clock();
    /*
    // registra o tempo de início da execucao
    gettimeofday(&inicio_execucao, NULL);
    */
    for (i = 0; i < num_threads; i++)
    {
        pthread_create(&threads[i], NULL, calcula_matriz, i);
    }

    for (i = 0; i < num_threads; i++)
    {
        pthread_join(threads[i], NULL);
    }

    fim_execucao = clock();
    /*
    // registra o tempo do fim da execucao
    gettimeofday(&fim_execucao, NULL);
    */
    tempo_execucao = ((double)(fim_execucao - inicio_execucao)) / CLOCKS_PER_SEC; // Calcula o tempo de execução em segundos
    printf("Tempo de execução: %f segundos\n", tempo_execucao);

    /*
    // tempo de execução em segundos
    tempo_execucao = (fim_execucao.tv_sec - inicio_execucao.tv_sec) + (fim_execucao.tv_usec - inicio_execucao.tv_usec) / 1000000.0;
    prinft("Tempo de execucao: %d segundos", &tempo_execucao);
    */
    return 0;
}
