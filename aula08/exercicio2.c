#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

#define SEQ_SIZE 12
#define TRUE 0
#define FALSE 1
#define NTHREADS 4

int main() {
  int i_achou;
  int i = 0;
  int j;
  int igual;
  char *buff;
  char sequencia[SEQ_SIZE];
  int file_size;
  char **seq_vet;
  int n_seq;
  int k;
  FILE *f = fopen("seq-teste.txt", "r");
  if (f == NULL) {
    printf("Erro na abertura do arquivo\n");
    exit(1);
  }
  fseek(f, 0L, SEEK_END);
  file_size = ftell(f);
  fseek(f, 0L, SEEK_SET);
  n_seq = (file_size + 1) / (SEQ_SIZE - 1);
  seq_vet = (char **) malloc(n_seq * sizeof(char*));
  for (k = 0; k < n_seq; k++) {
    seq_vet[k] = malloc(SEQ_SIZE * sizeof(char));
  }
  while (!feof(f)) {
    fgets(seq_vet[i], SEQ_SIZE, f);
    /*printf("seq_vet[%d] =  %s\n ", i, seq_vet[i]);*/
    i = i + 1;
  }
        
  printf("file_size=%d\n", file_size);

  printf("Digite a sequencia que deseja buscar: ");
  scanf("%s", &sequencia);
  igual = FALSE;

  #pragma omp parallel num_threads(NTHREADS) shared(igual, i_achou)
  {
    int i_min, i_max, igual_local;
    int thread_num = omp_get_thread_num();
    i_min = ((int) (n_seq * 1.0 / NTHREADS) * thread_num);
    i_max = ((int) (n_seq * 1.0 / NTHREADS) * (thread_num + 1));
    printf("t[%d], [%d:%d]\n", thread_num, i_min, i_max);
    for (i = i_min; i < i_max; i++) {
      #pragma omp atomic read
      igual_local = igual;
      if (igual_local == TRUE) {
        break;
      }
      buff = seq_vet[i];
      /*printf("i=%d buff %s\n ", i, buff);*/
      for (j = 0; j < SEQ_SIZE - 2; j++) {
        if (sequencia[j] != buff[j]) {
          break;
        }
      }
      if (j == SEQ_SIZE - 2) {
        #pragma omp critical
        {
          igual = TRUE;
          i_achou = i;
        }
        break;
      }
    }
  }

  if (igual == TRUE) {
    printf("Sequencia encontrada na linha %d\n", i_achou);
  } else {
    printf("Sequencia nao encontrada\n");
  }

  fclose(f);
  return 0;
}

