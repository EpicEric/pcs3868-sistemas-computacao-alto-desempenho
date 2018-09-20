#include <stdio.h>

int A[100][100], B[100][100], C[100][100], D[100][100], RES[100][100], X[100][100], Y[100][100];

void inicializarMatrizes()
{int i, j;
 for(i=0;i<100;i++)
  for(j=0;j<100;j++)
  {A[i][j]=i+j;
   B[i][j]=i+2*j;
   C[i][j]=2*i+3*j;
   D[i][j]=2*i+j;
   X[i][j]=0;
   Y[i][j]=0;
  }
}

void tarefaAB()
{int i,j,k;
printf("AB\n");
 for(i=0;i<=99;i++){
  for(j=0;j<=99;j++)
   for(k=0;k<=99;k++)
    X[i][j]=X[i][j]+A[i][k]*B[k][j];
 }
printf("Fim AB\n");
}
void tarefaCD()
{int i,j,k;
printf("CD\n");
 for(i=0;i<=99;i++){
  for(j=0;j<=99;j++)
   for(k=0;k<=99;k++)
    Y[i][j]=Y[i][j]+C[i][k]*D[k][j];
 }
printf("Fim CD\n");
}
void tarefaRES()
{int i,j;
 printf("RES\n");
 for(i=0;i<=99;i++){
  for(j=0;j<=99;j++)
   RES[i][j]=X[i][j]+Y[i][j];
 }
}
main()
{int i;
for (i=0;i<1000;i++){
 inicializarMatrizes();
  printf("INICIO TESTE\n");
 fflush(stdout);
	tarefaAB();
	tarefaCD();
	printf("\nSOMA\n");
	tarefaRES();
 printf("\nFIM\n");
} 
printf("RES[0][0]=%9d  RES[49][49]=%9d  RES[99][99]=%9d\n", RES[0][0], RES[49][49], RES[99][99]);
 fflush(stdout);
}
