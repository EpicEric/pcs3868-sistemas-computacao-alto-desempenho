#include <stdio.h>
#include <sys/time.h>
#include "mede_time.h"

#define SIZE 1000

double A[SIZE][SIZE];

/*inicia matriz*/
void init_matrix()
{
  int i, j;
  for (i = 0; i < SIZE; i++)
  {
    for (j = 0; j < SIZE; j++)
    {
      A[i][j] = (3 * i - j) / 2.0;
    }
  }
}

/*multiplicacao*/
double sum_matrix()
{
  int i, j;
  double sum = 0;
  for (i = 0; i < SIZE; i++)
  {
    for (j = 0; j < SIZE; j++)
      sum = sum + A[i][j];
  }
  return sum;
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
