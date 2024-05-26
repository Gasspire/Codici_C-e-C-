#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct record{
    int n;
    int m;
    int p;

};

struct record readInput(int argc,char *argv[]){
    if(argc!=4){
        fprintf(stderr,"Errore, numero di parametri insufficenti");
        exit(-1);
    }
    int n,m,p;
    n = strtod(argv[1],NULL);
    m = strtod(argv[2],NULL); 
    p = strtod(argv[3],NULL); 
    if(n<0 ||  m<0 || p<0){
        fprintf(stderr,"Errore, i parametri devono essere interi positivi!");
        exit(-1);
    }
    fprintf(stdout,"Numeri letti con successo %d %d %d\n\n",n,m,p);
    struct record dati;
    dati.n = n;
    dati.m = m;
    dati.p = p;
    return dati;
}

int ***initArray(struct record dati){
    int ***Array = (int ***) malloc(sizeof(int **)*dati.n);
    for (int i = 0; i<dati.n; i++){
        Array[i] = (int **) malloc(sizeof(int *)*dati.m);
        for (int j = 0; j < dati.m; j++)
        {
            Array[i][j] = (int *) malloc(sizeof(int)*dati.p);
        }
        
    }
    FILE *ptrfile = NULL;
    ptrfile = fopen("input.txt","r");
    if (ptrfile==NULL) exit(-1);
    int aux[dati.n*dati.m*dati.p];
    int i = 0;
    char riga[500];
    char *valore;
    while(!feof(ptrfile)){
        fgets(riga,500,ptrfile);
        valore = strtok(riga," \n");
        while (valore!=NULL){
            aux[i] = strtod(valore,NULL);
            valore = strtok(NULL," \n");
            i++;
        }
    }
    fclose(ptrfile);
    int p = 0;
    for (int i = 0; i < dati.n; i++)
    {
        for (int j = 0; j < dati.m; j++)
        {
            for (int z = 0; z < dati.p; z++)
            {
                Array[i][j][z] = aux[p];
                p++;
            }
        }
    }
    return Array;
}

int *initB(struct record dati,int ***Matrice){
    int *B = (int  *) malloc(sizeof(int)*dati.n);
    int max = 0;

    for (int i = 0; i < dati.n; i++)
    {
        for (int j = 0; j < dati.m; j++)
        {
            for (int z = 0; z < dati.p; z++)
            {
                if (max<Matrice[i][j][z]) max = Matrice[i][j][z];
            }
        }
        B[i] = max;
        max = 0;
    }
    return B;
}
//Funzioni per stack
struct nodo{
    int n;
    struct nodo *next;
};

int isempty(struct nodo *head){
    if(head==NULL)return 1;
    return 0;
}

void push(struct nodo **head,int n){
    struct nodo*newnodo =(struct nodo *) malloc(sizeof(struct nodo));
    newnodo->n = n;
    newnodo->next = NULL;
    if(isempty(*head)){
        *head = newnodo;
        return;
    }
    struct nodo *current = *head;
    newnodo->next =  current;
    *head = newnodo;
}

void printlist(struct nodo *head){
    struct nodo *temp = head;
    while(temp!=NULL){
        printf("%d\n",temp->n);
        temp = temp->next;
    }
    return;
}

int pop(struct nodo **head){
    FILE *ptrfile =NULL;
    ptrfile = fopen("out.txt","a");
    if(ptrfile==NULL) exit(-1);
    
    if(isempty(*head)) return 1;

    struct nodo *current = *head;
    *head = current->next;

    fprintf(ptrfile,"%d\n",current->n);
    free(current);
    return 0;
}

int main(int argc,char *argv[]){
    struct record dati = readInput(argc,argv);
    int ***Matrice;
    Matrice = initArray(dati);
    int *B;
    B = initB(dati,Matrice);
    struct nodo *head = NULL;
    for (int i = 0; i<dati.n; i++){
        push(&head,B[i]);
    }
    int n = 0;
    while (n!=1)
    {
        n = pop(&head);
        printf("%d",n);
    }
    
}