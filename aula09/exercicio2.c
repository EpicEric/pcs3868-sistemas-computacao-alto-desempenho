#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

#define SEQ_SIZE 10
#define TRUE 0
#define FALSE 1

int main(int argc, char **argv) {
    int i = 0;
    int j;
    int *indice_achou;
    char *buff;
    char sequencia[SEQ_SIZE + 1];
    int file_size;
    char *seq_vet;
    int n_seq;
    int k;
    int achou_parcial;
    int achou_parcial_no;
    FILE *f;
    MPI_Status status;
    int n_nos, rank;

    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &n_nos);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    if (rank == 0) {
        f = fopen("seq-teste.txt", "r");
        fseek(f, 0L, SEEK_END);
        file_size = ftell(f);
        fseek(f, 0L, SEEK_SET);
        n_seq = (file_size + 1) / (SEQ_SIZE + 1);
        printf("file_size = %d\n", file_size);
        printf("n_seq = %d\n", n_seq);
        seq_vet = (char *) malloc(SEQ_SIZE * n_seq * sizeof(char));
        indice_achou = (int *) malloc(n_seq * sizeof(int));
        for (i = 0; i < n_seq; i++) {
            fgets(seq_vet + sizeof(char) * i * SEQ_SIZE, SEQ_SIZE + 1, f);
            fseek(f, 1L, SEEK_CUR);
            /* printf("seq_vet[%d] = ", i); */
            /* for (j = 0; j < SEQ_SIZE; j++) { */
            /*     printf("%c", seq_vet[i * SEQ_SIZE + j]); */
            /* } */
            /* printf("\n"); */
        }
        fclose(f);

        printf("Digite a sequencia que deseja buscar: ");
        fflush(stdout);
        scanf("%s", &sequencia);

        k = n_seq / n_nos;
        for (i = 1; i < n_nos; i++) {
            MPI_Send(&sequencia, SEQ_SIZE + 1, MPI_CHAR, i, 30, MPI_COMM_WORLD);
            MPI_Send(&k, 1, MPI_INT, i, 20, MPI_COMM_WORLD);
            MPI_Send(seq_vet + sizeof(char) * k * i * SEQ_SIZE, k * SEQ_SIZE, MPI_CHAR, i, 10, MPI_COMM_WORLD);
        }
    } else {
        MPI_Recv(&sequencia, SEQ_SIZE + 1, MPI_CHAR, 0, 30, MPI_COMM_WORLD, &status);
        MPI_Recv(&k, 1, MPI_INT, 0, 20, MPI_COMM_WORLD, &status);
        seq_vet = (char *) malloc(SEQ_SIZE * k * sizeof(char));
        indice_achou = (int *) malloc(k * sizeof(int));
        MPI_Recv(seq_vet, k * SEQ_SIZE, MPI_CHAR, 0, 10, MPI_COMM_WORLD, &status);
    }

    /* printf("rank = %d - k = %d\n", rank, k); */
    achou_parcial = 0;
    for (i = 0; i < k; i++) {
        buff = seq_vet + sizeof(char) * i * SEQ_SIZE;
        /* printf("i = %d buff %s\n ", i, buff); */
        for (j = 0; j < SEQ_SIZE; j++) {
            if (sequencia[j] != buff[j]) {
                break;
            }
	    }
        if (j == SEQ_SIZE) {
            indice_achou[achou_parcial] = i + rank * k + 1;
            /* printf("rank = %d indice_achou = %d\n", rank, indice_achou[achou_parcial]); */
            achou_parcial++;
        }
    }

    if (rank == 0) {
        for (i = 1; i < n_nos; i++) {
            MPI_Recv(&achou_parcial_no, 1, MPI_INT, i, 40, MPI_COMM_WORLD, &status);
            MPI_Recv(indice_achou + achou_parcial, achou_parcial_no, MPI_INT, i, 50, MPI_COMM_WORLD, &status);
            achou_parcial += achou_parcial_no;
        }
        if (achou_parcial != 0) {
            printf("Sequencia encontrada %d vezes\n", achou_parcial);
            for (i = 0; i < achou_parcial; i++) {
                printf("  %d) linha %d\n", i + 1, indice_achou[i]);
            }
        } else {
            printf("Sequencia nao encontrada\n");
        }
    } else {
        MPI_Send(&achou_parcial, 1, MPI_INT, 0, 40, MPI_COMM_WORLD);
        MPI_Send(indice_achou, achou_parcial, MPI_INT, 0, 50, MPI_COMM_WORLD);
    }

    free(indice_achou);
    free(seq_vet);
    MPI_Finalize();
    return 0;
}
