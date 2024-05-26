#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct record{
    char *input;
    char *output;
};
typedef struct record Record;

Record readInput(int argc,char *argv[]){
    if (argc!=3){
        fprintf(stderr,"Errore, numero di parametri non valido");
        exit(-1);
    }
    char *input = argv[1];
    char *output = argv[2];

    if(strstr(input,".txt")==NULL || strstr(output,".txt")==NULL){
        fprintf(stderr,"Errore, parametri non validi\n");
        exit(-1);
    }
    Record dati;
    dati.input=input;
    dati.output = output;
    return dati;
}

struct nodo{
    char nome[255];
    char cognome[255];
    int numero_conto;
    int anno_apertura;
    float saldo;
    struct nodo* next;
};

int isempty(struct nodo *head){
    if(head==NULL)return 1;
    else  return 0;
}

void addnode(struct nodo **head,char nome[255],char cognome[255],int numero_conto,int anno_aperturta, float saldo){
    struct nodo *newnodo = (struct nodo *) malloc(sizeof(struct nodo));
    strcpy(newnodo->nome,nome);
    strcpy(newnodo->cognome,cognome);
    newnodo->numero_conto = numero_conto;
    newnodo->anno_apertura = anno_aperturta;
    newnodo->saldo = saldo;
    newnodo->next =NULL;
    if(isempty(*head)){
        *head = newnodo;
        return;
    }
    struct nodo *current = *head;
    struct nodo *previous =NULL;
    while (current!=NULL && (current->anno_apertura) < (newnodo->anno_apertura))
    {
        previous = current;
        current = current->next;
    }
    if(previous == NULL){
        *head = newnodo;
        newnodo->next = current;
        return;
    }
    if (current == NULL)
    {
        previous->next = newnodo;

        return;
    }
    if (previous!=NULL){
        previous->next = newnodo;
        newnodo->next = current;
        return;
    }
}

void printList(struct nodo *head,char *output){
    FILE  *ptrfile = fopen(output,"w+");
    struct nodo *temp = head;
    if(isempty(head)) return;
    while (temp!=NULL)
    {
        fprintf(ptrfile,"%s %s %d %d %.2f\n",temp->nome,temp->cognome,temp->numero_conto,temp->anno_apertura,temp->saldo);
        temp =  temp->next;
    }
    fclose(ptrfile);
    return;
}

struct nodo *readFile(char *input){
    FILE *ptrfile = NULL;
    ptrfile =fopen(input,"r");
    if (ptrfile==NULL){
        fprintf(stderr,"Errore nell'apertura del file");
        exit(-1);
    }
    
    struct nodo *head = NULL;
    char riga[500];
    char nome[255];
    char cognome[255];
    char *aux;
    int numero_conto;
    int anno_apertura;
    float saldo;

    while(!feof(ptrfile)){
        fgets(riga,500,ptrfile);
        aux = strtok(riga," \n");
        while(aux!=NULL){
            strcpy(nome,aux);
            aux =strtok(NULL," \n");
            strcpy(cognome,aux);
            aux = strtok(NULL," \n");
            numero_conto = atoi(aux);
            aux = strtok(NULL," \n");
            anno_apertura = atoi(aux);
            aux = strtok(NULL," \n");
            saldo = atof(aux);
            addnode(&head,nome,cognome,numero_conto,anno_apertura,saldo);
            aux  = strtok(NULL," \n");
        }
    }
    fclose(ptrfile);
    return head;
}

float getmax(struct nodo *head){
    struct nodo *temp = head;
    float max = temp->saldo;
    while (temp!=NULL)
    {
        if (max <= temp->saldo) max = temp->saldo;
        temp = temp->next;
    }
    printf("il massimo saldo in lista e' : %.2f\n",max);
    return max;
}

void removeaccount(struct nodo **head, float max){
    struct nodo *temp = *head;
    float valorex = 0;
    float valorexmax = -300;
    int codclientemax;
    while (temp!=NULL)
    {
        if(((2023-temp->anno_apertura)/5.0)<1){
            valorex = ((2023-temp->anno_apertura)/5.0)*(temp->saldo/max);
        }
        else{
            valorex =(temp->saldo/max);
        }
        if(valorex>valorexmax){
            valorexmax  = valorex;
            codclientemax = temp->numero_conto;
        }
        temp = temp->next;
    }
    printf("Removing %d  con x = %.2f\n",codclientemax,valorexmax);
    struct nodo *current = *head;
    struct nodo *previous = NULL;
    while (current!=NULL && current->numero_conto!=codclientemax)
    {
        previous = current;
        current = current->next;
    }
    
    if(current==NULL){
        fprintf(stderr,"Errore!\n");
        exit(-1);
    }
    
    if(previous==NULL){
        *head = current->next;
        return;
    }
    if(previous!=NULL){
        previous->next = current->next;
        return;
    }
}



int main(int argc, char *argv[]){
    Record dati;
    dati = readInput(argc,argv);
    struct nodo *head =  NULL;
    head = readFile(dati.input);
    for (int i = 0;i<5;i++){
        removeaccount(&head,getmax(head));
    }
    printList(head,dati.output);
}