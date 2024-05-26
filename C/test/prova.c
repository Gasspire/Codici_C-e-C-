#include <stdio.h>
#include <stdlib.h>
#include <string.h>




int main(){
    FILE *ptrfile = NULL;
    ptrfile = fopen("input.txt","r");
    if(ptrfile==NULL) exit(-1);
    char riga[50];
    fgets(riga,50,ptrfile);
    printf("%s",riga);
    int n = strlen(riga);
    printf("%d",n);
}