#include <stdio.h>
#include <omp.h>
#include <sys/time.h>
#include "mede_time.h"

#define SIZE 1000
#define NTHREADS 2

int A[SIZE][SIZE], B[SIZE][SIZE], C[SIZE][SIZE], D[SIZE][SIZE],
    AB[SIZE][SIZE], CD[SIZE][SIZE], R[SIZE][SIZE];

void init_matrizes() {
  int i, j;
  for (i = 0; i < SIZE; i++) {
    for (j = 0; j < SIZE; j++) {
      A[i][j] = i;
      B[i][j] = j;
      C[i][j] = i + j;
      D[i][j] = i - j;
    }
  }
}

void multiplicacao_matriz(int a[SIZE][SIZE], int b[SIZE][SIZE], int res[SIZE][SIZE]) {
  int i, j, k;
  #pragma omp for
  for (i = 0; i < SIZE; i++) {
    for (j = 0; j < SIZE; j++) {
      res[i][j] = 0;
      for (k = 0; k < SIZE; k++) {
        res[i][j] += a[i][k] * b[k][j];
      }
    }
  }
}

void soma_matriz(int a[SIZE][SIZE], int b[SIZE][SIZE], int res[SIZE][SIZE]) {
  int i, j;
  #pragma omp for
  for (i = 0; i < SIZE; i++) {
    for (j = 0; j < SIZE; j++) {
      res[i][j] = a[i][j] + b[i][j];
    }
  }
}

void run() {
  omp_set_num_threads(NTHREADS);
  #pragma omp parallel sections
  {
    #pragma omp section
    {
      multiplicacao_matriz(A, B, AB);
    }
    #pragma omp section
    {
      multiplicacao_matriz(C, D, CD);
    }
  }
  #pragma omp parallel
  {
    soma_matriz(AB, CD, R);
  }
}

int main(int argc, char **argv) {
  TIMER_CLEAR;
  init_matrizes();
  TIMER_START;
  run();
  TIMER_STOP;
  printf("TEMPO [SIZE = %d, NTHREADS = %d]: %.7f\n", SIZE, NTHREADS, TIMER_ELAPSED);
  printf("R[0][0] = %7d\n", R[0][0]);
  printf("R[%d][%d] = %7d\n", SIZE / 10, SIZE / 5, R[SIZE / 10][SIZE / 5]);
  printf("R[%d][0] = %7d\n", SIZE - 1, R[SIZE - 1][0]);
  return 0;
}
