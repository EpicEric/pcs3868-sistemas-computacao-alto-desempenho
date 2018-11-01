/*
 * Nú mámo de um vetor usando MPI_Send.
 * Numero de elementos do vetor: multiplo do nú de processos.
 *  */

#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

#define max(x,y) ((x) > (y) ? (x) : (y))

main(argc, argv)

int			argc;
char			*argv[];

{
	int		n,n_nos, rank;
	MPI_Status	status;
        int inicio,fim,vetor[100000],max_parcial,i,k;
        int max_total,maximo;
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
        n=100000;
        k=n/n_nos;
        inicio=rank*k;
        fim=inicio+k;
        if (rank==0) {
          for(i=inicio;i<n;i++)
            vetor[i]=rand();
          for (i=1;i<n_nos;i++)
           {
             MPI_Send(&vetor[k*i],k,MPI_INT,i,10,MPI_COMM_WORLD);
             printf("rank=%d APOS SEND\n",rank);
             fflush(stdout);
           }
        }
        else {
          MPI_Recv(vetor,k,MPI_INT,0,10,MPI_COMM_WORLD,&status);
        printf("rank=%d APOS RECV\n",rank);
        fflush(stdout);
        }
        max_parcial=vetor[0];
        for(i=1;(i<k);i++) {
          max_parcial = max(max_parcial, vetor[i]);
        }
        printf("rank=%d mámo_parcial=%d\n",rank,max_parcial);
        fflush(stdout);
        if (rank==0) {
           max_total=max_parcial;
           for(i=1;i<n_nos;i++){
             MPI_Recv(&maximo,1,MPI_INT,MPI_ANY_SOURCE,11,MPI_COMM_WORLD,&status);
             max_total = max(maximo, max_total);}
           printf("RESULTADO=%d\n",max_total);
           fflush(stdout); 
           }
        else {
        printf("rank=%d maximo_parcial=%d\n",rank,max_parcial);
        fflush(stdout);
           MPI_Send(&max_parcial,1,MPI_INT,0,11,MPI_COMM_WORLD);
             }
	MPI_Finalize();
	return(0);
}

