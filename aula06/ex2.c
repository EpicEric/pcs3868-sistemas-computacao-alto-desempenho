#include <stdio.h>
#include <omp.h>

#define SIZE 2000

omp_nest_lock_t sem1;
omp_nest_lock_t sem2;


int A[SIZE];
int B[SIZE];
int C[SIZE];
int X[SIZE];
int Y[SIZE];

int main()
{
  int i;
  for(i = 0; i < 2000; i++) {
    X[i] = i;
    Y[i] = i + 1;
  }
  printf("INICIO\n");
  omp_init_nest_lock(&sem1);
  omp_set_nest_lock(&sem1);
  omp_init_nest_lock(&sem2);
  omp_set_nest_lock(&sem2);
  omp_set_num_threads(3);

#pragma omp parallel sections
  {
   #pragma omp section
   { 
    int i;
    for(i = 0; i < 1999; i++) {
        A[i] = i*3 + 15;
        printf("A[%d]",i);
        fflush(stdout);
        omp_unset_nest_lock(&sem1);
    }
  }
  #pragma omp section
  {
    int i;
    B[0] = 1;
    for(i = 1; i < 2000; i++) {
        omp_set_nest_lock(&sem1);
        B[i] = Y[i] + A[i-1];
        printf("B[%d]",i);
        fflush(stdout);
        omp_unset_nest_lock(&sem2);
    }
  }
  #pragma omp section
  {
    int i;
    C[0] = 1;
    for(i = 1; i < 2000; i++) {
        omp_set_nest_lock(&sem2);
        C[i] = Y[i] + B[i-1] * 2;
        printf("C[%d]", i);
        fflush(stdout);
    }
  }
 }
   omp_destroy_nest_lock(&sem1);
   omp_destroy_nest_lock(&sem2);
}

