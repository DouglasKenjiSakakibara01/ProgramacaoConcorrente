#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <pthread.h>
#include <math.h>
#define tam 100

float a[tam][tam];
float b[tam][tam];
float res[tam][tam];
int num_threads;
void imprime_matriz()
{
}

void calcula_matriz(int indice_thread)
{
    int area = ceil(tam / num_threads);
    int inicio = indice_thread * area;
    int fim = (indice_thread + 1) * area;

    for (int i = inicio; i <= fim; i++)
    {
        for (int j = 0; j <= tam; j++)
        {
            res[i][j] = 0;
            for (int k = 0; k < tam; k++)
            {
                res[i][j] += a[i][k] * b[k][j];
            }
        }
    }
}
int main(int argc, char *argv[])
{ /*
  pthread_t *threads;
  num_threads = argv[1];
  num_threads = 2;
  threads = (pthread_t *)malloc(num_threads * sizeof(pthread_t));
  */
    num_threads = 2;
    pthread_t threads[num_threads];
    for (int i = 0; i < num_threads; i++)
    {
        pthread_create(&threads[i], NULL, calcula_matriz, i);
    }

    for (int i = 0; i < num_threads; i++)
    {
        pthread_join(threads[i], NULL);
    }
}