#include <stdio.h>
#include <stdlib.h>
#include <string.h>

unsigned int get_random() {
 static unsigned int m_w = 123456;
 static unsigned int m_z = 789123;
 m_z = 36969 * (m_z & 65535) + (m_z >> 16);
 m_w = 18000 * (m_w & 65535) + (m_w >> 16);
 return (m_z << 16) + m_w;
}

struct record{
    int N;
    char w;
};

struct record check(int argc,char *argv[]){
    if (argc!=3){
        fprintf(stderr,"Errore, numero di parametri errato!");
        exit(-1);
    }
    int n=strtod(argv[1],NULL);
    char w=(argv[2][0]);
    if(n<10 || n>20){
        fprintf(stderr,"Il numero n deve essere compreso tra 10 e 20");
        exit(-1);
    }
    if (w<'a' || w>'z'){
        fprintf(stderr,"il carattere non e' valido");
        exit(-1);
    }
    struct record dati;
    dati.N=n;
    dati.w= w;
    return dati;
}
//Funzioni che riguardano la lista concatenata semplice
struct nodo{
    char *string;
    struct nodo *next;
};

int IsEmpty(struct nodo *head){
    if (head == NULL) return 1;
    else return 0;
}

char *genString(){
    int l = get_random()%(15-5+1)+5;
    char *stringa =(char *) malloc(sizeof(char)*l+1);
    for (int i = 0; i<l;i++){
        int aux = get_random()%(122-97+1)+97;
        char z = (char)aux;
        stringa[i]= z;
    }
    stringa[l] = '\0';
    return stringa;
}

void insertstring(struct nodo **head){
    struct nodo *newnodo= (struct nodo *)malloc(sizeof(struct nodo));
    newnodo->next = NULL;
    newnodo->string = genString();
    if (IsEmpty(*head)){
        *head = newnodo;
        return;
    }

    struct nodo* current = *head;
    struct nodo* previous = NULL;
    while (current != NULL && strcmp(current->string,newnodo->string)<0)
    {
        previous = current;
        current = current->next;
    }
    
    if (current == NULL){
        previous->next =newnodo;
        return;
    }

    if (previous == NULL){
        *head = newnodo;
        newnodo->next = current;
        return;
    }

    if(current != NULL){
        previous->next = newnodo;
        newnodo->next = current;
        return;
    }
}

void printList(struct nodo *head) {
    struct nodo *tmp = head;
    while(tmp) {
        fprintf(stdout,"%s\n", tmp->string);
        tmp = tmp->next;
    }
}

void serchList(struct nodo *head,char w) {
    struct nodo *tmp = head;
    int counter = 0;
    while(tmp) {
        int n = strlen(tmp->string);
        for (int i=0;i<n;i++){
            if(tmp->string[i]==w){
                counter++;
            }
        }
        tmp=tmp->next;
    }
    fprintf(stdout,"le occorrenze di %c sono %d",w,counter);
}

int main(int argc, char *argv[]){
    struct record dati;
    dati = check(argc,argv);
    struct nodo* head =NULL;
    for (int i = 0;i<dati.N;i++){
        insertstring(&head);
    }
    printf("%s\n",head->string);
    printList(head);
    serchList(head,dati.w);
    
}