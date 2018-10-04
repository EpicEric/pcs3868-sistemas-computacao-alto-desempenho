#include <stdio.h>
#include <sys/time.h>
#include "mede_time.h"

#define SIZE 1000
#define NTHREADS 4

double A[SIZE][SIZE];

void init_matrix() {
  int i, j;
  #pragma omp parallel num_threads(NTHREADS) shared(A) private(i, j)
  {
  #pragma omp for
    for (i = 0; i < SIZE; i++) {
      for (j = 0; j < SIZE; j++) {
        A[i][j] = (3 * i - j) / 2.0;
      }
    }
  }
}

double sum_matrix() {
  int i, j;
  double sum = 0;
  #pragma omp parallel num_threads(NTHREADS) shared(A) private(i, j) reduction(+:sum)
  {
    #pragma omp for
    for (i = 0; i < SIZE; i++) {
      for (j = 0; j < SIZE; j++) {
        sum += A[i][j];
      } 
    }
  }
  return sum;
}

void main(argc, argv) int argc;
char **argv;
{
  double sum;
  TIMER_CLEAR;
  TIMER_START;
  init_matrix();
  sum = sum_matrix();
  TIMER_STOP;
  printf("TEMPO [SIZE = %d, NTHREADS = %d]: %.7f\n", SIZE, NTHREADS, TIMER_ELAPSED);
  printf("SOMA: %lf\n", sum);
}
