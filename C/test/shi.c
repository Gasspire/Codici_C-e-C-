#include  <stdio.h>
#include <stdlib.h>
#include <string.h>



int main(){
    char frase[]="Sopra la panca la capra campa, sotto la panca la capra crepa panca";
    char aux[]= " \n";
    int  counter = 0;
    char *ptr =NULL;
    ptr=strtok(frase,aux);
    printf("%s ",ptr);
    do
    {
        ptr=strtok(NULL,aux);
        if(ptr==NULL) continue;
        if(strcmp(ptr,"panca")==0) counter++;
        printf("%s ",ptr);
    } while (ptr!=NULL);
    printf("\nIl counter e' arrivato a %d",counter);
    
}