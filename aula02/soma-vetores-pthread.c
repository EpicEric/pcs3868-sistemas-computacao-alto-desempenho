#include <stdio.h>
#define size 1000
#define n_threads 3
#include <pthread.h>
#include <stdlib.h>

double a[size][size], b[size][size], c[size][size];
int n_iter;
pthread_t tid[n_threads];

void *soma_matrizes(void *arg) {
	int i, j, inicio, fim, k;
	k = *((int *) arg);
	inicio = (k + 1) * n_iter;
	fim = inicio + n_iter;
	for (i=inicio;i<fim;i++)
		for (j=0;j<size;j++)
			c[i][j] = a[i][j] + b[i][j];
}

void main() {
	int i, j, k, id_thread[n_threads];
	int p = -1;
	n_iter = size / (n_threads + 1);
	//inicializa as matrizes
	for (i = 0; i < size; i++)
		for (j = 0; j < size; j++){
			a[i][j] = 1.5;
			b[i][j] = 2.6;
	}
	// fim da inicializacao
	for (k = 0; k < n_threads; k++) {
		id_thread[k] = k;
		if (pthread_create(&tid[k], NULL, soma_matrizes, (void *)&id_thread[k])) {
			printf("Cannot create thread %d\n", i);
			exit(1);
		}
	}
	soma_matrizes((void *)&p);
	/* join threads */
	for (i = 0; i < n_threads; i++) {
		pthread_join(tid[i], NULL);
	}
	printf("c[0][0]=%f   c[15][20]=%f  c[size-1][size-1]=%f \n", c[0][0], c[15][20], c[size-1][size-1]);
}
