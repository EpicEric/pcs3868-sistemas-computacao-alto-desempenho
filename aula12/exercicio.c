#include <mpi.h>
#include <stdio.h>
#include <omp.h>

#define NCORES 2
#define SIZE 100

void processo0(int n_nos, int rank) {
    int i, j, k;
    double A[SIZE][SIZE], B[SIZE][SIZE], X_i[SIZE];
    for (i = 0; i < SIZE; i++) {
        for (j = 0; j < SIZE; j++) {
            A[i][j] = (double) (i - j);
            B[i][j] = (double) (i + j);
        }
    }
    for (i = 0; i < SIZE; i++) {
        #pragma omp parallel shared(A, B, X_i) private(j, k)
        {
            #pragma omp for
            for (j = 0; j < SIZE; j++) {
                X_i[j] = 0;
                for (k = 0; k < SIZE; k++) {
                    X_i[j] += A[i][k] * B[k][j];
                }
            }
        }
        MPI_Send(X_i, SIZE, MPI_DOUBLE, 2, rank * SIZE + i, MPI_COMM_WORLD);
    }
}

void processo1(int n_nos, int rank) {
    int i, j, k;
    double C[SIZE][SIZE], D[SIZE][SIZE], Y_i[SIZE];
    for (i = 0; i < SIZE; i++) {
        for (j = 0; j < SIZE; j++) {
            C[i][j] = (double) (i - 2 * j);
            D[i][j] = (double) (2 * i + j);
        }
    }
    for (i = 0; i < SIZE; i++) {
        #pragma omp parallel shared(C, D, Y_i) private(j, k)
        {
            #pragma omp for
            for (j = 0; j < SIZE; j++) {
                Y_i[j] = 0;
                for (k = 0; k < SIZE; k++) {
                    Y_i[j] += C[i][k] * D[k][j];
                }
            }
        }
        MPI_Send(Y_i, SIZE, MPI_DOUBLE, 2, rank * SIZE + i, MPI_COMM_WORLD);
    }
}

void processo2(int n_nos, int rank) {
    int i, j;
    MPI_Status status;
    double X_i[SIZE], Y_i[SIZE], Z[SIZE][SIZE];
    for (i = 0; i < SIZE; i++) {
        for (j = 0; j < SIZE; j++) {
            Z[i][j] = 0;
        }
    }
    for (i = 0; i < SIZE; i++) {
        MPI_Recv(X_i, SIZE, MPI_DOUBLE, 0, 0 * SIZE + i, MPI_COMM_WORLD, &status);
        MPI_Recv(Y_i, SIZE, MPI_DOUBLE, 1, 1 * SIZE + i, MPI_COMM_WORLD, &status);
        #pragma omp parallel shared(X_i, Y_i, Z) private(j)
        {
            #pragma omp for
            for (j = 0; j < SIZE; j++) {
                Z[i][j] = X_i[j] + Y_i[j];
            }
        }
    }
    printf("[rank %d] Z[0][0] = %f  Z[100][200] = %f  Z[900][900] = %f", Z[0][0], Z[20][10], Z[99][99]);
}

int main(int argc, char **argv) {
    int i, n_nos, rank;
    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &n_nos);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    if (n_nos < 3) {
        if (rank == 0) {
            printf("[rank %d] Expected 3 processes; Received %d\n", rank, n_nos);
            return 1;
        }
    }
    omp_set_num_threads(2);
    switch (rank) {
        case 0:
            printf("[debug] 3-0\n", rank);
            processo0(n_nos, rank);
            break;
        case 1:
            printf("[debug] 3-1\n", rank);
            processo1(n_nos, rank);
            break;
        case 2:
            printf("[debug] 3-2\n", rank);
            processo2(n_nos, rank);
            break;
        default:
            printf("[rank %d] Unexpected process rank; ignoring\n", rank);
    }
    MPI_Finalize();
    return 0;
}
