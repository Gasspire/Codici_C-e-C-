#include <iostream>
using namespace std;


struct Nodo {
    int dato;
    Nodo* next;
};


class Lista{
    public:
        Nodo *head;
    public:
        Lista(){head = NULL;}
        void AggiungiNodo(int c_dato){
            Nodo *newNodo = new Nodo;
            newNodo->dato = c_dato;
            newNodo->next = NULL;
            if(head==NULL){
                head = newNodo;
                return;
            }
            Nodo *current = head;
            while (current->next!=NULL)
            {
                current = current->next;
            }
            current->next = newNodo;
            return;
        }
        void PrintLista(){
            Nodo *current = head;
            while (current!=NULL)
            {
                cout<<" "<<current->dato<<endl;
                current = current->next;
            }
        }
    

};


Nodo* getTail(Nodo* head) {
    if (head == nullptr || head->next == nullptr)
        return head;

    Nodo* curr = head;
    while (curr->next != nullptr)
        curr = curr->next;

    return curr;
}

Nodo* partition(Nodo* low, Nodo* high) {
    int pivot = low->dato;
    Nodo* i = low->next;
    Nodo* j = low;
    while (i != high->next) {
        if (i->dato < pivot) {
            j = j->next;
            int temp = i->dato;
            i->dato = j->dato;
            j->dato = temp;
        }
        i = i->next;
    }
    int temp = low->dato;
    low->dato = j->dato;
    j->dato = temp;

    return j;
}

void quicksortUtil(Nodo* low, Nodo* high) {
    if (low != nullptr && high != nullptr && low != high) {
        Nodo* pivot = partition(low, high);

        quicksortUtil(low, pivot);
        quicksortUtil(pivot->next, high);
    }
}

void quicksort(Nodo*& head) {
    Nodo* tail = getTail(head);
    quicksortUtil(head, tail);
}



int main(){
    Lista mialista;
    mialista.AggiungiNodo(5);
    mialista.AggiungiNodo(3);
    mialista.AggiungiNodo(7);
    mialista.AggiungiNodo(9);
    mialista.AggiungiNodo(4);
    mialista.AggiungiNodo(10);
    mialista.AggiungiNodo(2);
    mialista.PrintLista();
    quicksort(mialista.head);
    cout<<"POST QUICKSORT!"<<endl;
    mialista.PrintLista();
}