#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#include "matrix.h"

void multiply_matrixes_linear()
{
    for (int i = 0; i < size; i++)
        for (int j = 0; j < size; j++) {
            matrixResult[i][j] = 0.0;
            for (int k = 0; k < size; k++)
                matrixResult[i][j] += matrixA[i][k] * matrixB[k][j];
        }
}