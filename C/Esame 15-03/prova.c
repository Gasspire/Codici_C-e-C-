#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct nodo{
    char nome[50];
    char cognome[50];
    char telefono[50];
    struct nodo* next;
};

int IsEmpty(struct nodo*head){
    if(head==NULL) return 1;
    else return 0;
}

void addnode(struct nodo **head,char nome[],char cognome[],char telefono[]){
    struct nodo* newnodo = (struct nodo *) malloc(sizeof(struct nodo));
    strcpy(newnodo->nome,nome);
    strcpy(newnodo->cognome,cognome);
    strcpy(newnodo->telefono,telefono);
    newnodo->next = NULL;
    if(IsEmpty(*head)){
        *head = newnodo;
        return;
    }
    struct nodo *current =  *head;
    struct nodo *previous = NULL;
    while(current!=NULL && strcmp(current->nome,newnodo->nome)<0){
        previous = current;
        current = current->next;
    }

    if (current==NULL)
    {
        previous->next = newnodo;
        return;
    }
    
    if(previous==NULL){
        newnodo->next = current;
        *head = newnodo;
        return;
    }
    if(current!=NULL){
        previous->next = newnodo;
        newnodo->next =current;
        return;
    }
}

void printlist(struct nodo *head){
    if(IsEmpty(head)){
        printf("ERROR");
        exit(-1);
    }
    struct nodo *temp = head;
    while (temp!=NULL)
    {
        printf("%s %s %s\n",temp->nome,temp->cognome,temp->telefono);
        temp = temp->next;
    }
    return;
}

void readinput(){
    FILE *ptrfile = NULL;
    ptrfile = fopen("rubrica.txt","r");
    if(ptrfile == NULL) exit(-1);
    char riga[500];
    char *valore;
    char nome[500];
    char cognome[500];
    char telefono[500];
    
    struct nodo *head = NULL;

    while (!feof(ptrfile))
    {
        fgets(riga,500,ptrfile);
        valore = strtok(riga," \n");
        while (valore!=NULL)
        {
            strcpy(nome,valore);
            valore = strtok(NULL," \n");
            strcpy(cognome,valore);
            valore = strtok(NULL," \n");
            strcpy(telefono,valore);
            addnode(&head,nome,cognome,telefono);
            valore = strtok(NULL," \n");
        }
    }
    printlist(head);
}




int main(){
    readinput();
}