#include <stdio.h>
#include <time.h>
#include <stdlib.h>

int a[1000][1000];
void buscar(int elemento)
{int i, j;
 for(i=0; i<1000; i++){
  for(j=0; j<1000;j++)
  {
   if(elemento == a[i][j]) {
    printf("[%d][%d]\n", i, j); 
   }
   fflush(stdout);
  }
 }
}
main()
{int i, j, elemento;
 for(i=0; i<1000;i++)
 {
  for(j=0; j<1000; j++)
  {
   a[i][j] = rand() %256;
  }
 }

 printf("INICIO TESTE\n");
 fflush(stdout);
 scanf("%d", &elemento);
 buscar(elemento);
 printf("\nFIM\n");
 fflush(stdout);
}
