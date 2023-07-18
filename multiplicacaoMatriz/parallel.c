#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <math.h>
#include <time.h>

#include "matrix.h"

int num_threads, num_lines_each, rest;

void* multiply_lines(void* arg) {
    int start, end;
    int idx = *(int *)arg;

    start = idx * num_lines_each;
    if (rest && idx == num_threads - 1)
        end = size - 1;
    else
        end = start + num_lines_each;

    for (int i = start; i < end; i++)
        for (int j = 0; j < size; j++) {
            matrixResult[i][j] = 0;
            for (int k = 0; k < size; k++)
                matrixResult[i][j] += matrixA[i][k] * matrixB[k][j];
        }
}

void multiply_matrixes_parallel() {
    pthread_t threads[num_threads];

    num_lines_each = floor(size / num_threads);
    rest = size % num_threads;

    int i;
    for (i = 0; i < num_threads; i++)
        pthread_create(&threads[i], NULL, multiply_lines, &i);
    
    for (i = 0; i < num_threads; i++)
        pthread_join(threads[i], NULL);
}
