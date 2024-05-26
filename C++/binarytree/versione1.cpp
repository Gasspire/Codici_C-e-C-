#include <iostream>
using namespace std;

struct nodo {
  int dato;
  nodo *sx;
  nodo *dx;
};

class btree{
    public:   
        nodo *radice;
    public: 
        btree(){radice = NULL;}
        void Insert(nodo *&rad,int key){
            if(rad){//In maniera ricorsiva, questo sarà il nostro stop
                if(key<rad->dato){//vediamo se la key è minore rispetto alla radice
                    if(rad->sx!=NULL){Insert(rad->sx,key);}//se a sinistra non è vuoto, ripetiamo il processo in maniera ricorsiva
                    else{ //Se arriviamo qui, vuol dire che alla sinistra della nostra radice non c'è nulla!
                        nodo *nuovonodo = new nodo;
                        nuovonodo->dato = key;
                        nuovonodo->sx = NULL;
                        nuovonodo->dx = NULL;
                        rad->sx = nuovonodo;
                    }
                }
                else if(rad->dx!=NULL){Insert(rad->dx,key);}//se a sinistra non è vuoto, ripetiamo il processo in maniera ricorsiva
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
        void Elimina(int key,nodo *&rad){
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
        void PreOrder(nodo *rad){
            nodo *temp= rad;
            if(temp){
                cout<<" "<<temp->dato;
                PreOrder(temp->sx);
                PreOrder(temp->dx);
            }
        }
        void InOrder(nodo *rad){
            nodo *temp= rad;
            if(temp){
                InOrder(temp->sx);
                cout<<" "<<temp->dato;
                InOrder(temp->dx);
            }
        }       
        void PostOrder(nodo *rad){
            nodo *temp= rad;
            if(temp){
                PostOrder(temp->sx);
                PostOrder(temp->dx);
                cout<<" "<<temp->dato;
            }
        }
};


int main(){
    btree albero;                                  // generiamo l'albero
	albero.Insert(albero.radice,1);                                 // popoliamo l'albero
	albero.Insert(albero.radice,4);
	albero.Insert(albero.radice,3);
	albero.Insert(albero.radice,6);
	albero.Insert(albero.radice,2);
	albero.Insert(albero.radice,8);
	cout << "InOrdine: ";
	albero.InOrder(albero.radice); cout << endl;        // visualizziamo l'albero InOrdine
	cout << "PreOrdine: ";
	albero.PreOrder(albero.radice); cout << endl;       // visualizziamo l'albero PreOrdine
	cout << "PostOrdine: ";
	albero.PostOrder(albero.radice); cout << endl;      // visualizziamo l'albero PostOrdine
	albero.Elimina(6,albero.radice);                                 // eliminiamo un nodo
	cout << "InOrdine: ";
	albero.InOrder(albero.radice); cout << endl;
	cout << "PreOrdine: ";
	albero.PreOrder(albero.radice); cout << endl;
	cout << "PostOrdine: ";
	albero.PostOrder(albero.radice); cout << endl;
}