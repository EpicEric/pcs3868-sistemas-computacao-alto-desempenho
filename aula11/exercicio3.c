#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

#define SIZE 500

int main(int argc, char **argv) {
    int A[SIZE][SIZE], B[SIZE][SIZE], X[SIZE][SIZE], Y[SIZE][SIZE],
        C[SIZE][SIZE], T[SIZE][SIZE], Z[SIZE][SIZE];
    int i, j, k, n_nos, rank;
    MPI_Request req1, req2;
    MPI_Status status;
    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &n_nos);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    switch (rank) {
        case 0: // Tarefa 1
            for (i = 0; i < SIZE; i++) {
                for (j = 0; j < SIZE; j++) {
                    A[i][j] = i + j;
                    B[i][j] = 2 * i - j;
                }
            }
            for (i = 0; i < SIZE; i++) {
                for (k = 0; k < SIZE; k++) {
                    for (j = 0; j < SIZE; j++) {
                        X[i][j] = X[i][j] + A[i][k] * B[k][j];
                    }
                }
                // Envia linhas de X para tarefa 3
                MPI_Isend(X[i], SIZE, MPI_INT, 2, 10, MPI_COMM_WORLD, &req2);
            }
            for (i = 0; i < SIZE; i++) {
                // Recebe linhas de C de tarefa 2
                MPI_Irecv(C[i], SIZE, MPI_INT, 1, 30, MPI_COMM_WORLD, &req1);
                // Aguarda linhas de C de tarefa 2
                MPI_Wait(&req1, &status);
                for (j = 0; j < SIZE; j++) {
                    Y[i][j] = X[i][j] + C[i][j];
                }
                // Envia linhas de Y para tarefa 3
                MPI_Isend(Y[i], SIZE, MPI_INT, 2, 20, MPI_COMM_WORLD, &req2);
            }
            break;
        case 1: // Tarefa 2
            for (i = 0; i < SIZE; i++) {
                for (j = 0; j < SIZE; j++) {
                    C[i][j] = 2 * i + j;
                }
                // Envia linhas de C para tarefa 1
                MPI_Isend(C[i], SIZE, MPI_INT, 0, 30, MPI_COMM_WORLD, &req1);
            }
            break;
        case 2: // Tarefa 3
            for (i = 0; i < SIZE; i++) {
                // Recebe linhas de X de tarefa 1
                MPI_Irecv(X[i], SIZE, MPI_INT, 0, 10, MPI_COMM_WORLD, &req1);
                // Recebe linhas de Y de tarefa 1
                MPI_Irecv(Y[i], SIZE, MPI_INT, 0, 20, MPI_COMM_WORLD, &req2);
                for (j = 0; j < SIZE; j++) {
                    T[i][j] = i + j;
                }
                // Aguarda linhas de X de tarefa 1
                MPI_Wait(&req1, &status);
                // Aguarda linhas de Y de tarefa 1
                MPI_Wait(&req2, &status);
                for (j = 0; j < SIZE; j++) {
                    Z[i][j] = T[i][j] + X[i][j] + Y[i][j];
                }
            }
            printf("Z[0][0]=%d  Z[200][100]=%d  Z[499][499]=%d\n",
                    Z[0][0], Z[200][100], Z[499][499]);
            break;
        default:
            break;
    }
    MPI_Finalize();
    return 0;
}
