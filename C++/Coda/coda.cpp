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

class Coda{
    private:
        Nodo *head;
    public:
        Coda(){head = NULL;}
        bool Isempty(){
            if (head==NULL) return true;
            else return false;
        }
        void inqueue(int elemento){
            Nodo *nuovonodo;
            nuovonodo = new Nodo(elemento);
            if (Isempty()){
                head = nuovonodo;
                return;
            }
            Nodo *current = head;
            while (current->getseguente()!= NULL)
            {
                current = current->getseguente();
            }
            current->sedSeguente(nuovonodo);
        }
        void printCoda(){
            if (Isempty())
            {
                cout<<"La Coda e' vuota!"<<endl;
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
        void dequeue(){
            Nodo *current = head;
            if (Isempty())
            {
                return;
            }
            
            head = head->getseguente();
            cout<<"dequeue "<<current->getDato()<<endl;
            delete current;
        }
        void Svuota(){
            while (Isempty()==false)
            {
                dequeue();
            }
        }

};


int main(){
    Coda coda;
    for(int i = 0; i<10; i++){
        coda.inqueue(i);
        cout<<"adding "<<i<<endl;
    }
    coda.printCoda();
    coda.dequeue();
    coda.Svuota();
}