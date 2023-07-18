#include <sys/time.h>
#include <string.h>

#include "parallel.c"
#include "linear.c"
#include "matrix.c"

double time_to_sec(struct timeval t1, struct timeval t2) {
    return (t2.tv_sec - t1.tv_sec) + (t2.tv_usec - t1.tv_usec) / 1000000.0;
}

int main(int argc, char *argv[]) {
    if (argc < 3 || argc > 4) {
        printf("Uso: %s <tamanho> <num_threads> [-p]\n", argv[0]);
        return EXIT_FAILURE;
    }

    size = atoi(argv[1]);
    int max_threads = atoi(argv[2]);
    int progressive = argc > 3 && strcmp(argv[3], "-p") == 0;

    struct timeval exec_start, exec_end;

    printf("Tamanho das matrizes: %d\n", size);
    printf("Numero de threads: %d\n", max_threads);
    printf("Executando em modo progressivo: %d\n", progressive);

    allocate_matrixes();

    int seed = time(NULL);
    populate_matrixes(seed);

    double exec_time_parallel, exec_time_linear, speedup;

    gettimeofday(&exec_start, NULL);
    multiply_matrixes_linear();
    gettimeofday(&exec_end, NULL);

    exec_time_linear = time_to_sec(exec_start, exec_end);
    printf("\nLinear: %f segundos\n\n", exec_time_linear);

    if (progressive)
        num_threads = 2;
    else
        num_threads = max_threads;
    
    while (num_threads <= max_threads) {
        gettimeofday(&exec_start, NULL);
        multiply_matrixes_parallel();
        gettimeofday(&exec_end, NULL);

        exec_time_parallel = time_to_sec(exec_start, exec_end);
        printf("Paralelo (%d threads): %f segundos\n", num_threads, exec_time_parallel);

        speedup = exec_time_linear / exec_time_parallel;
        printf("Speedup: %f\n", speedup);

        ++num_threads;
    }

    if (size <= 5) {
        puts("Matriz A:\n");
        print_matrix(matrixA);
        puts("\nMatriz B:\n");
        print_matrix(matrixB);
        puts("\nResultado:\n");
        print_matrix(matrixResult);
    }

    return EXIT_SUCCESS;
}
