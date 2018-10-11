#include <stdio.h>
#include <omp.h>

#define SIZE 2000

omp_lock_t semA_empty;
omp_lock_t semA_full;
omp_lock_t semB_empty;
omp_lock_t semB_full;


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
  omp_init_lock(&semA_empty);
  omp_init_lock(&semA_full);
  omp_set_lock(&semA_full);
  omp_init_lock(&semB_empty);
  omp_init_lock(&semB_full);
  omp_set_lock(&semB_full);
  omp_set_num_threads(3);

#pragma omp parallel sections
  {
   #pragma omp section
   { 
    int i;
    for(i = 0; i < 1999; i++) {
        omp_set_lock(&semA_empty);
        A[i] = i*3 + 15;
        printf("A[%d]",i);
        omp_unset_lock(&semA_full);
    }
  }
  #pragma omp section
  {
    int i;
    B[0] = 1;
    for(i = 1; i < 2000; i++) {
        omp_set_lock(&semA_full);
        omp_set_lock(&semB_empty);
        B[i] = Y[i] + A[i-1];
        printf("B[%d]",i);
        omp_unset_lock(&semB_full);
        omp_unset_lock(&semA_empty);
    }
  }
  #pragma omp section
  {
    int i;
    C[0] = 1;
    for(i = 1; i < 2000; i++) {
        omp_set_lock(&semB_full);
        C[i] = Y[i] + B[i-1] * 2;
        printf("C[%d]", i);
        omp_unset_lock(&semB_empty);
    }
  }
 }
   omp_destroy_lock(&semA_empty);
   omp_destroy_lock(&semA_full);
   omp_destroy_lock(&semB_empty);
   omp_destroy_lock(&semB_full);
}

