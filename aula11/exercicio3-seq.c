/*
tarefa1:gera A e B X=A x B     Y=X+C   
tarefa2:gera C
tarefa3:gera T Z= T+X+Y
*/

#include <stdio.h>
#include <stdlib.h>
void main()
{   int A[500][500], B[500][500],X[500][500],Y[500][500],C[500][500],T[500][500],Z[500][500];
    int i,j,k;
    for (i=0;i<500;i++)
      for (j=0;j<500;j++) {
        A[i][j]=i+j;
        B[i][j]=2*i-j;
      }
    for (i=0;i<500;i++) 
      for(k=1;k<500;k++)
          for (j=0;j<500;j++)
            X[i][j]=X[i][j]+A[i][k]*B[k][j];
    for (i=0;i<500;i++) 
      for (j=0;j<500;j++){
            C[i][j]=2*i+j;
            T[i][j]=i+j;
      } 
    for (i=0;i<500;i++) 
      for (j=0;j<500;j++)
            Y[i][j]=X[i][j]+C[i][j];
    for (i=0;i<500;i++) 
      for (j=0;j<500;j++)
            Z[i][j]=T[i][j]+X[i][j]+Y[i][j];
    printf("Z[0][0]=%d  Z[200][100]=%d  Z[499][499]=%d \n",Z[0][0],Z[200][100],Z[499][499]);
}

