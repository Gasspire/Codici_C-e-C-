#include <stdio.h>
#include <stdlib.h>
#include <string.h>





int main(){
    char ***Array;
    int n = 5;
    int m = 4;
    int p = 10;
    Array = (char ***) malloc(sizeof(char **)*n);
    for (int i=0;i<n;i++){
        Array[i] = (char **) malloc(sizeof(char *)*m);
        for (int j = 0; j < m; j++)
        {
            Array[i][j] = (char *)  malloc(sizeof(char)*p+1);
        }
    }

    int aux;

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            for (int z = 0; z < p; z++)
            {
                aux = rand()%(122-97+1)+97;
                Array[i][j][z] = (char) aux;
                if (z==p-1) Array[i][j][z+1] = '\0';
            }
        }
    }
    
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            printf("%s ",Array[i][j]);
            if(j==m-1) printf("\n");
        }
    }

    printf("\nCerco di printare la lista da colonna!\n");
    for (int i = 0; i < p; i++)
    {
        for (int j = 0; j < m; j++)
        {
            for (int z = 0; z < n; z++)
            {
                printf("%c",Array[z][j][i]);
                if(z==n-1) printf(" ");
            }
            if(j==m-1)printf("\n");
        }
        
    }
    
}