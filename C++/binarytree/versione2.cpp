#include <iostream>
using namespace std;

struct nodo {
  int dato;
  nodo *sx;
  nodo *dx;
};

class btree {
public:
	btree() {radice = NULL;};
	void Insert(int key) {Insert(key, radice);};
	void Elimina(int key) {Elimina(key, radice);};
	void InOrder(){InOrder(radice);};
	void PreOrder(){PreOrder(radice);};
	void PostOrder(){PostOrder(radice);};
private:
    nodo *radice;
    void Insert(int, nodo* &);
    void Elimina(int, nodo* &);
	void InOrder(nodo*);
	void PreOrder(nodo*);
	void PostOrder(nodo*);
};

void btree::Insert(int key,nodo *&rad){
            if(rad){//In maniera ricorsiva, questo sarà il nostro stop
                if(key<rad->dato){//vediamo se la key è minore rispetto alla radice
                    if(rad->sx!=NULL){Insert(key,rad->sx);}//se a sinistra non è vuoto, ripetiamo il processo in maniera ricorsiva
                    else{ //Se arriviamo qui, vuol dire che alla sinistra della nostra radice non c'è nulla!
                        nodo *nuovonodo = new nodo;
                        nuovonodo->dato = key;
                        nuovonodo->sx = NULL;
                        nuovonodo->dx = NULL;
                        rad->sx = nuovonodo;
                    }
                }
                else if(rad->dx!=NULL){Insert(key,rad->dx);}//se a sinistra non è vuoto, ripetiamo il processo in maniera ricorsiva
                    else{ //Se arriviamo qui, vuol dire che alla sinistra della nostra radice non c'è nulla!
                        nodo *nuovonodo = new nodo;
                        nuovonodo->dato = key;
                        nuovonodo->sx = NULL;
                        nuovonodo->dx = NULL;
                        rad->dx = nuovonodo;
                    }
                }
            else{  //Se arriviamo qui è perché l'albero è vuoto, e quindi creiamo la prima radice!
                nodo *nuovonodo = new nodo;
                nuovonodo->dato = key;
                nuovonodo->dx = NULL;
                nuovonodo->sx = NULL;
                rad = nuovonodo;
            }
        }
void btree::Elimina(int key,nodo *&rad){
            nodo* temp;
            if(rad){
                if(key<rad->dato) Elimina(key,rad->sx); //controlliamo se la key è minore e in caso andiamo a sinistra
                else if(key>rad->dato) Elimina(key,rad->dx);  //controlliamo se la key è maggiore in caso andiamo a destra
                    else{//Se non rispetta né il < né il > allora lo abbiamo trovato!
                        if(rad->sx== NULL && rad->dx == NULL){ //Stiamo eliminando una foglia
                            temp = rad;
                            rad = NULL;
                            delete temp;
                        }
                        else if(rad->sx == NULL){ //stiamo eliminando una ramo con un solo figlio a dx
                            temp = rad;
                            rad = rad->dx;
                            delete temp;
                        }
                        else if(rad->dx == NULL){ //stiamo eliminando una ramo con un solo figlio a sx
                            temp = rad;
                            rad = rad->sx;
                            delete temp;
                        }
                        else{ //stiamo eliminando un ramo con due figli 
                            temp = rad->dx; //settiamo il nostro temp per prende il valore più grande rispetto a quello da eliminare
                            while(temp->sx != NULL) temp = temp->sx;//finito questo while troviamo il nodo con cui fare lo swap con la radice
                            rad->dato = temp->dato; //più che uno swap, copiamo il valore di temp sulla radice
                            Elimina(temp->dato,rad->dx);//Eliminiamo il doppione rimasto 
                        }
                    }
            }
        }
void btree::PreOrder(nodo *rad){
    nodo *temp= rad;
    if(temp){
        cout<<" "<<temp->dato;
        PreOrder(temp->sx);
        PreOrder(temp->dx);
    }
}
void btree::InOrder(nodo *rad){
    nodo *temp= rad;
    if(temp){
        InOrder(temp->sx);
        cout<<" "<<temp->dato;
        InOrder(temp->dx);
    }
}       
void btree::PostOrder(nodo *rad){
    nodo *temp= rad;
    if(temp){
        PostOrder(temp->sx);
        PostOrder(temp->dx);
        cout<<" "<<temp->dato;
    }
}

int main(){
    btree albero;                                  // generiamo l'albero
	albero.Insert(1);                                 // popoliamo l'albero
	albero.Insert(4);
	albero.Insert(3);
	albero.Insert(6);
	albero.Insert(2);
	albero.Insert(8);
	cout << "InOrdine: ";
	albero.InOrder(); cout << endl;        // visualizziamo l'albero InOrdine
	cout << "PreOrdine: ";
	albero.PreOrder(); cout << endl;       // visualizziamo l'albero PreOrdine
	cout << "PostOrdine: ";
	albero.PostOrder(); cout << endl;      // visualizziamo l'albero PostOrdine
	albero.Elimina(6);                                 // eliminiamo un nodo
	cout << "InOrdine: ";
	albero.InOrder(); cout << endl;
	cout << "PreOrdine: ";
	albero.PreOrder(); cout << endl;
	cout << "PostOrdine: ";
	albero.PostOrder(); cout << endl;
}