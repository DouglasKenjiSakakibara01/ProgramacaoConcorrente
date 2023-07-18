#define MATRIX float**
#define MAX_EL 9.9

int size;

MATRIX matrixA;
MATRIX matrixB;
MATRIX matrixResult;

void allocate_matrixes();

void populate_matrixes(int seed);

void print_matrix(MATRIX m);
