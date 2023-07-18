#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#include "matrix.h"

void allocate_matrixes() {
    matrixA = (float**)malloc(size * sizeof(float*));
    matrixB = (float**)malloc(size * sizeof(float*));
    matrixResult = (float**)malloc(size * sizeof(float*));
    for (int i = 0; i < size; i++) {
        matrixA[i] = (float*)malloc(size * sizeof(float));
        matrixB[i] = (float*)malloc(size * sizeof(float));
        matrixResult[i] = (float*)malloc(size * sizeof(float));
    }
}

float rnd_float() {
    return ((float)rand() / RAND_MAX) * MAX_EL;
}

void populate_matrixes(int seed) {
    srand(seed);

    for (int i = 0; i < size; i++)
        for (int j = 0; j < size; j++) {
            matrixA[i][j] = rnd_float();
            matrixB[i][j] = rnd_float();
        }
}

void print_matrix(MATRIX m) {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++)
            printf("%.2f\t", m[i][j]);
        printf("\n");
    }
}
