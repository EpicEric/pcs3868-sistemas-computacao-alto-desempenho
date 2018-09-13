#include <stdio.h>
#define n_processos 3
#include <sys/shm.h>
#include <stdlib.h>
#define size 1000
typedef struct {
	double a[size][size], b[size][size], c[size][size];
} shared_data;
shared_data *shared;
pid_t pid_p;

void main()
{
	int i, j, k;
	pid_t pid[n_processos];
	int status;
	struct shmid_ds *buf;
	int id;
	int inicio, fim, n_iter;
	id = shmget(IPC_PRIVATE, sizeof(shared_data), 0777 | IPC_CREAT);
	shared = shmat(id, 0, 0);
	//inicializa as matrizes   -  3 processos
	n_iter = size/(n_processos+1);
	inicio = 0;
	fim = n_iter;
	k=-1;

	//inicializa as matrizes
	for (i = 0; i < size; i++)
		for (j = 0 ; j < size; j++) {
			shared->a[i][j] = 1.5;
			shared->b[i][j] = 2.6;
		}
	// fim da inicializacao
	// soma de a com b
	do {
		k++;
		pid_p = fork();
		if (pid_p != 0)
			pid[k] = pid_p;
	} while ((pid_p != 0) && (k < (n_processos - 1)));
	if (pid_p == 0) {     //filhos
		shared = shmat(id, 0, 0);
		inicio = (k + 1) * n_iter;
		fim = inicio + n_iter;
	}
	for (i = inicio; i < fim; i++)
		for (j = 0; j < size; j++)
			shared->c[i][j] = shared->a[i][j] + shared->b[i][j];
	if (pid_p == 0) {
		shmdt(shared);
		exit(0);
	}
	for (k = 0; k < n_processos; k++)
		waitpid(pid[k], &status, 0);
	printf("c[0][0]=%f   c[15][20]=%f  c[size-1][size-1]=%f \n", shared->c[0][0], shared->c[15][20], shared->c[size-1][size-1]);
}
