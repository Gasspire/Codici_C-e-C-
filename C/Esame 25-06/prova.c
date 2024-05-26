#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void readInput(char *input, char *output, int argc) {
  if (argc != 3) {
    fprintf(stderr, "numero di parametri non valido");
    return;
  }
  if (strlen(input) > 255 || strlen(output) > 255) {
    fprintf(stderr, "troppe lettere");
    return;
  }
}

double ***createMatrix(char *input) {
  FILE *ptrfile = NULL;
  ptrfile = fopen(input,"r");
  if (ptrfile == NULL) {
    fprintf(stderr, "Non sono riuscito ad aprire il file perchè sono daun");
    exit(-1);
  }
  int n = 0, m = 0;
  //Controllo valori per creare matrice
  while (!feof(ptrfile)) {
    char riga[100];
    fgets(riga, 100, ptrfile);
    char *numero = strtok(riga, " \n");
    m = 0;
    while (numero != NULL) {
      m++;
      numero = strtok(NULL, " \n");
    }
    n++;
  }
  fclose(ptrfile);
  double ***matrice = (double ***) malloc(sizeof(double **)*n);
  for (int i = 0; i < n; i++)
  {
    matrice[i] = (double **) malloc(sizeof(double *)*m);
    for (int j = 0; j < m; j++)
    {
        matrice[i][j] = (double *) malloc(sizeof(double));
    }
  }
  return matrice;
}

void riempimatrice(double ***matrice,int n, int m,char *input){
  FILE *ptrfile = NULL;
  ptrfile = fopen(input,"r");
  if(ptrfile==NULL) exit(-1);
  char riga[100];
  char *valore;
  float numero;
  float Arrayvalori[n*m];
  int i = 0;
  while (!feof(ptrfile))
  {
    fgets(riga,100,ptrfile);
    valore = strtok(riga," \n");
    while(valore!=NULL){
      numero = strtof(valore,NULL);
      Arrayvalori[i] = numero;
      i++;
      valore = strtok(NULL," \n");
    }
  }
  int z = 0;
  for (int i = 0; i < n; i++)
  {
    for (int j = 0; j < m; j++)
    {
      *matrice[i][j] = Arrayvalori[z];
      z++;
    }
    
  }
  for (int i = 0; i < n; i++)
  {
    for (int j = 0; j < m; j++)
    {
      printf("Matrice [%d][%d] = %.2f ",i,j,*matrice[i][j]);
      if (j==m-1)printf("\n");
    }
    
  }
  
  
}

int main(int argc, char *argv[]) {
  char *input = argv[1];
  char *output = argv[2];
  readInput(input, output, argc);
  double ***Matrice = createMatrix(input);
  riempimatrice(Matrice,3,5,input);
}