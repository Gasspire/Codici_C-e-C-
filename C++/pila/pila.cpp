#include <iostream>
using namespace std;

class Nodo{
    private:
        int dato;
        Nodo *seguente;
    public:
        Nodo(int elemento){
            dato = elemento;
            seguente = NULL;
            }
        int getDato(){return dato;}
        Nodo *getseguente(){return seguente;}
        void setDato(int elemento){dato = elemento;}
        void sedSeguente(Nodo *newseguente){seguente = newseguente;}
};

class Pila{
    private:
        Nodo *head;
    public:
        Pila(){head = NULL;}
        bool Isempty(){
            if (head==NULL) return true;
            else return false;
        }
        void addnodo(int elemento){
            Nodo *nuovonodo;
            nuovonodo = new Nodo(elemento);
            if (Isempty()){
                head = nuovonodo;
                return;
            }
            nuovonodo->sedSeguente(head);
            head = nuovonodo;
            return;
        }
        void printpila(){
            if (Isempty())
            {
                cout<<"La pila e' vuota!"<<endl;
                return;
            }
            Nodo *current = head;
            while (current!= NULL)
            {
                cout<<""<<current->getDato()<<endl;
                current = current->getseguente();
            }
            return;
        }
        void pop(){
            Nodo *current = head;
            if (Isempty())
            {
                return;
            }
            head = head->getseguente();
            cout<<"popping "<<current->getDato()<<endl;
            delete current;
        }
        void Svuota(){
            while (Isempty()==false)
            {
                pop();
            }
        }
        void copiainvertito(Pila piladicopia){
            if (Isempty())
            {
                cout<<"La pila e' vuota!"<<endl;
                return;
            }
            Nodo *current = head;
            while (current!= NULL)
            {
                piladicopia.addnodo(current->getDato());
                current = current->getseguente();
            }
            cout<<"\n sto stampando la pila copiata\n"<<endl;
            piladicopia.printpila();
            return;
        }
        bool confrontapila(Pila pila){
            Nodo *current = head;
            Nodo *current2 = pila.head;
            while (current!=NULL && current2 != NULL)
            {
                if (current->getDato()==current2->getDato())
                {
                    current = current->getseguente();
                    current2 = current2->getseguente();
                }
                else{
                    return false;
                }
            }
            return true;
            
        }
        
};

int main(){
    Pila lamiapila;
    lamiapila.addnodo(1);
    lamiapila.addnodo(2);
    lamiapila.addnodo(1);
    lamiapila.printpila();
    Pila piladicopia;
    for (int i = 0; i < 9; i++)
    {
        piladicopia.addnodo(i);
    }
    cout<<"Pile uguali : "<<lamiapila.confrontapila(piladicopia);
}