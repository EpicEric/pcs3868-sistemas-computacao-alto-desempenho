#include <stdio.h>
#include <sys/time.h>
#include "mede_time.h"

#define SIZE 1000
#define NTHREADS 4

int A[SIZE][SIZE];

void init_matrix() { 
  int i,j;
  #pragma omp parallel num_threads(NTHREADS) shared(A) private(i, j)
  {
    #pragma omp for
    for (i = 0; i < SIZE; i++) {  
      for (j = 0; j < SIZE; j++) {
        A[i][j] = (2 * i - j) % 1000;
      }
    }
  }
}

int contar_ocorrencias(int valor) {
  int i, j;
  int ocorrencias = 0;
  #pragma omp parallel num_threads(NTHREADS) shared(A) private(i, j) reduction(+:ocorrencias)
  {
    #pragma omp for
    for (i = 0; i < SIZE; i++) {
      for (j = 0; j < SIZE; j++) {
        if (A[i][j] == valor) {
          ocorrencias++;
        }
      }
    }
  }
  return ocorrencias;
}

void main(int argc, char **argv) {
  int valor, ocorrencias;
  TIMER_CLEAR;
  printf("Valor a ser encontrado: ");
  scanf("%d", &valor);
  TIMER_START;
  init_matrix();
  ocorrencias = contar_ocorrencias(valor);
  TIMER_STOP;
  printf("TEMPO [SIZE = %d, NTHREADS = %d]: %.7f\n", SIZE, NTHREADS, TIMER_ELAPSED);
  printf("OCORRENCIAS: %d\n", ocorrencias);
}
