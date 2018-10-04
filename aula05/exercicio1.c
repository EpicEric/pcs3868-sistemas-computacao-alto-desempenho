#include <stdio.h>
#include <sys/time.h>
#include "mede_time.h"

#define SIZE 1000

double A[SIZE][SIZE];

/*inicia matriz*/
void init_matrix()
{
  int i, j;
#pragma omp parallel num_threads(2) shared(A) private(i, j)
  {
#pragma omp for
    for (i = 0; i < SIZE; i++)
    {
      for (j = 0; j < SIZE; j++)
      {
        A[i][j] = (3 * i - j) / 2.0;
      }
    }
  }
}

/*multiplicacao*/
double sum_matrix()
{
  int i, j;
  double sum = 0;
#pragma omp parallel num_threads(2) shared(A) private(i, j) reduction(+ \
                                                                      : sum)
  {
#pragma omp for
    for (i = 0; i < SIZE; i++)
    {
      for (j = 0; j < SIZE; j++)
        sum = sum + A[i][j];
    }
  }
  return sum;
}

/*imprime matriz */
void print_mat(A) double A[SIZE][SIZE];
{
  int i, j;

  for (i = 0; i < 10; i++)
  {
    for (j = 0; j < 10; j++)
      printf(" %10.2f", A[i][j]);
    puts("");
  }
  puts("");
}

void main(argc, argv) int argc;
char **argv;
{
  double sum;
  init_matrix();
  TIMER_CLEAR;
  TIMER_START;
  sum = sum_matrix();
  TIMER_STOP;
  printf("TEMPO [%d]: %12.7f\n", SIZE, TIMER_ELAPSED);
  printf("SOMA: %lf\n", sum);
}
