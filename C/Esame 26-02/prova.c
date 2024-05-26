#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int readinput(int argc,char *argv[]){
    if(argc!=2){
        fprintf(stderr,"errore, parametri non validi");
        exit(-1);
    }
    int  n = strtod(argv[1],NULL);
    if (n<0){
        fprintf(stderr,"Errore, N non valido");
        exit(-1);
    }
    return n;
}

struct nodo{
    char word[100];
    int count;
    struct nodo *next;
};

//Creazione lista

int IsEmpty(struct nodo *head){
    if (head == NULL) return 1;
    else return 0;
}
void insertnodo(struct nodo **head,char word[100],int n){
    struct nodo *newnodo= (struct nodo *)malloc(sizeof(struct nodo));
    newnodo->next = NULL;
    strcpy(newnodo->word,word);
    printf("shii : %s\n",newnodo->word);
    newnodo->count = n;
    if (IsEmpty(*head)){
        *head = newnodo;
        return;
    }
    struct nodo * current = *head;
    while (current->next != NULL)
    {
        current = current->next;
    }
    current->next =newnodo;
}

void printlist(struct nodo *head){
    struct nodo *temp = head;
    printf("print lista\n");
    while(temp!=NULL){
        printf("%s con ricorrenze: %d\n",temp->word,temp->count);
        temp = temp->next;
    }
}

int main(int argc, char *argv[]){
    int n = readinput(argc,argv);
    char *ptrparola = NULL;
    char *ptrfrase =NULL;
    int counter = 1;
    char stringa[100];
    struct nodo * head = NULL;
    //Leggiamo il file
    FILE *ptr = NULL;
    ptr = fopen("input.txt","r");
    while (!feof(ptr))
    {
        fgets(stringa,100,ptr);
        printf("%s\n",stringa);
        ptrparola = strtok(stringa," ");
        do
        {
            ptrfrase = strtok(NULL," \n");
            if (ptrfrase==NULL) continue;
            if (strcmp(ptrparola,ptrfrase)  == 0)
            {
                counter++;
            }
        } while (ptrfrase!=NULL);
        printf("La ricorrenza della prima  parola e' :%d\n",counter);
        insertnodo(&head,ptrparola,counter);
        counter = 1;
    }
    printlist(head);
    fclose(ptr);
}