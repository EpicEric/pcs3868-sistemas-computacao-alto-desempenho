#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 100000
#define MAX_VALUE 20

int main(int argc, char **argv) {
    int i, n, n_nos, rank, search_value;
    int vetor[SIZE];
    int *ocorrencias;
    MPI_Status status;
    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &n_nos);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    srand(time(NULL) + 60 * rank); // Deixar valores aleatorios diferentes entre cada thread
    for (i = 0; i < SIZE; i++) {
        vetor[i] = rand() % MAX_VALUE;
    }
    if (rank == 0) {
        search_value = rand() % MAX_VALUE;
        ocorrencias = malloc(sizeof(int) * n_nos);
        printf("[rank 0] Valor a ser encontrado: %d\n", search_value);
    }
    MPI_Bcast(&search_value, 1, MPI_INT, 0, MPI_COMM_WORLD);
    for (i = 0; i < SIZE; i++) {
        if (vetor[i] == search_value) break;
    }
    MPI_Gather(&i, 1, MPI_INT, ocorrencias, 1, MPI_INT, 0, MPI_COMM_WORLD);
    if (rank == 0) {
        for (i = 0; i < n_nos; i++) {
            if (ocorrencias[i] == SIZE) {
                printf("[rank %d] Valor nao encontrado!\n", i);
            } else {
                printf("[rank %d] vetor[%d] = %d\n", i, ocorrencias[i], search_value);
            }
        }
        free(ocorrencias);
    }
    MPI_Finalize();
    return 0;
}
