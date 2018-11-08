/*
tarefa1: X = A x B
tarefa2: Y = E x F
tarefa3: Z = C x D
tarefa4: W = X + Y + Z
*/

#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

#define SIZE 500

int n;
int X[SIZE][SIZE], Y[SIZE][SIZE], Z[SIZE][SIZE];

void tarefa1() {
    int i, j, buffer_size, rank;
    int *buffer;
    for (i = 0; i < SIZE; i++) {
        for (j = 0; j < SIZE; j++) {
            X[i][j] = i * 2 - j;
        }
    }
    for (i = 0; i < SIZE - 1; i++) {
        for (j = 1; j < SIZE - 1; j++) {
            X[i][j] = X[i+1][j-1] * 3 - X[i+1][j+1];
        }
    }
    buffer_size = MPI_BSEND_OVERHEAD + SIZE * sizeof(int);
    for (i = 0; i < SIZE; i++) {
        buffer = malloc(buffer_size);
        MPI_Buffer_attach(buffer, buffer_size);
        MPI_Bsend(X[i], SIZE, MPI_INT, 3, 1000 + i, MPI_COMM_WORLD);
        MPI_Buffer_detach(buffer, &buffer_size);
    }
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    printf("tarefa1 rank %d FIM\n", rank);
}

void tarefa2() {
    int i, j, buffer_size, rank;
    int *buffer;
    for (i = 0; i < SIZE; i++) {
        for (j = 0; j < SIZE; j++) {
            Y[i][j] = i * 3 - j;
        }
    }
    buffer_size = MPI_BSEND_OVERHEAD + SIZE * sizeof(int);
    for (i = 0; i < SIZE - 1; i++) {
        for (j = 1; j < SIZE - 1; j++) {
            Y[i][j] = Y[i+1][j-1] * 4 - Y[i+1][j+1];
        }
    }
    buffer_size = MPI_BSEND_OVERHEAD + SIZE * sizeof(int);
    for (i = 0; i < SIZE; i++) {
        buffer = malloc(buffer_size);
        MPI_Buffer_attach(buffer, buffer_size);
        MPI_Bsend(Y[i], SIZE, MPI_INT, 3, 2000 + i, MPI_COMM_WORLD);
        MPI_Buffer_detach(buffer, &buffer_size);
    }
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    printf("tarefa2 rank %d FIM\n", rank);
}

void tarefa3() {
    int i, j, buffer_size, rank;
    int *buffer;
    for (i = 0; i < SIZE; i++) {
        for (j = 0; j < SIZE; j++) {
            Z[i][j] = i * 2 + j;
        }
    }
    for (i = 0; i < 499; i++) {
        for (j = 1; j < 499; j++) {
            Z[i][j] = Z[i+1][j-1] * 2 - Z[i+1][j+1];
        }
    }
    buffer_size = MPI_BSEND_OVERHEAD + SIZE * sizeof(int);
    for (i = 0; i < SIZE; i++) {
        buffer = malloc(buffer_size);
        MPI_Buffer_attach(buffer, buffer_size);
        MPI_Bsend(Z[i], SIZE, MPI_INT, 3, 3000 + i, MPI_COMM_WORLD);
        MPI_Buffer_detach(buffer, &buffer_size);
    }
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    printf("tarefa3 rank %d FIM\n", rank);
}

void tarefa4() {
    int i, j, rank;
    int W[SIZE][SIZE];
    MPI_Status status;
    for (i = 0; i < SIZE; i++) {
        for (j = 0; j < SIZE; j++) {
            W[i][j] = 0;
        }
    }
    for (i = 0; i < SIZE; i++) {
        MPI_Recv(X[i], SIZE, MPI_INT, 0, 1000 + i, MPI_COMM_WORLD, &status);
        MPI_Recv(Y[i], SIZE, MPI_INT, 1, 2000 + i, MPI_COMM_WORLD, &status);
        MPI_Recv(Z[i], SIZE, MPI_INT, 2, 3000 + i, MPI_COMM_WORLD, &status);
        for (j = 0; j < SIZE; j++) {
            W[i][j] = X[i][j] + Y[i][j] + Z[i][j];
        }
    }
    printf("tarefa4 W[0][0]=%d W[300][400]=%d W[499][499]=%d\n", W[0][0], W[300][400], W[499][499]);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    printf("tarefa4 rank %d FIM\n", rank);
    printf("tarefa4 FIM\n");
}

int main(int argc, char **argv) {
    int n_nos, rank;
    n = SIZE;
    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &n_nos);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    if (n_nos != 4 && rank == 0) {
        if (rank == 0) {
            printf("[ERROR] Running %d threads; expected 4\n", n_nos);
        }
        MPI_Finalize();
        return -1;
    }
    switch (rank) {
        case 0:
            tarefa1();
            break;
        case 1:
            tarefa2();
            break;
        case 2:
            tarefa3();
            break;
        case 3:
            tarefa4();
            break;
        default:
            printf("[ERROR] Unexpected rank %d\n", rank);
            return -1;
    }
    MPI_Finalize();
	return 0;
}
