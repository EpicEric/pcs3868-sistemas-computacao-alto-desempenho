#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main(argc, argv)

int			argc;
char			*argv[];

{
	int		n,n_nos, rank;
	MPI_Status	status;
  int fim,i,j,k;
  int max,parcial;
  int a[1000][1000];
/*
 *  * Initialize MPI.
 *   */
	MPI_Init(&argc, &argv);
/*
 *  * Error check the number of processes.
 *   * Determine my rank in the world group.
 *    * The sender will be rank 0 and the receiver, rank 1.
 *     */
	MPI_Comm_size(MPI_COMM_WORLD, &n_nos);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  n=1000;
  printf("INICIO\n");
  fflush(stdout);
  k=n/n_nos;
  if (rank==0) {
    printf("rank0");
    for(i=0;i<n;i++)
      for(j=0;j<n;j++) {
        a[i][j]=rand();
      }
  }
  MPI_Scatter(a,k*n,MPI_INT,a,k*n,MPI_INT,0,MPI_COMM_WORLD);
  fflush(stdout);
  parcial=a[0][0];
  fim=k;
  for (i=0;i<fim;i++)
    for (j=0;j<n;j++)
      if (a[i][j] > parcial) {
        parcial = a[i][j];
      } 
  printf("rank=%d parcial=%d\n",rank,parcial);
  fflush(stdout);        
  MPI_Reduce(&parcial,&max,1,MPI_INT,MPI_MAX,0,MPI_COMM_WORLD);
  if (rank==0) {
     printf("RESULTADO=%d\n",max);
     fflush(stdout);
  } 
	MPI_Finalize();
	return(0);
}

