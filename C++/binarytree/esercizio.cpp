#include <iostream>
using namespace std;

struct nodo{
    char dato;
    nodo *dx;
    nodo *sx;
};
 

class BTree{
    protected:
        nodo *radice;
        void Insert(nodo *&rad,int key);
        void Elimina(nodo *&rad,int key);
        void PreOrder(nodo *rad);
        void InOrder(nodo *rad);
        void PostOrder(nodo *rad);
        void stampaLivello(nodo* p, int level);// stampa i nodi ad un dato livello
        int altezza(nodo* p)const;
        void stampaalbero(nodo *p);



    public:
        BTree(){radice = NULL;}
        void Insert(int key){Insert(radice,key);}
        void Elimina(int key){Elimina(radice,key);}
        void PreOrder(){PreOrder(radice);}
        void InOrder(){InOrder(radice);}
        void PostOrder(){PostOrder(radice);}
        void stampaLivello(int level){stampaLivello(radice,level);} // stampa i nodi ad un dato livello
        int altezza()const{return altezza(radice);}
        void stampaalbero(){stampaalbero(radice);};
    
};

void BTree::Insert(nodo *&rad,int key){
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

void BTree::Elimina(nodo *&rad,int key){
    nodo *temp;
    if(rad){
        if(key<rad->dato) Elimina(rad->sx,key);
        else if(key>rad->dato) Elimina(rad->dx,key);
        else{
            if(rad->dx== NULL && rad->sx == NULL){
                temp = rad;
                rad = NULL;
                delete temp;
                return;
            }
            else if(rad->dx==NULL){
                temp = rad;
                rad = rad->sx;
                delete temp;
                return;
            }
            else if(rad->sx==NULL){
                temp = rad;
                rad = rad->dx;
                delete temp;
                return;
            }
            else if(rad->dx != NULL && rad->sx!= NULL){
                temp = rad->dx;
                while (temp->sx!=NULL) temp = temp->sx;
                rad->dato = temp->dato;
                Elimina(rad->dx,temp->dato);
                return;
            }
        }
    }
}

void BTree::PreOrder(nodo *rad){
    nodo *temp = rad;
    if(temp){
        cout<<" "<<temp->dato;
        PreOrder(temp->sx);
        PreOrder(temp->dx);
    }
}
void BTree::InOrder(nodo *rad){
    nodo *temp = rad;
    if(temp){
        InOrder(temp->sx);
        cout<<" "<<temp->dato;
        InOrder(temp->dx);
    }
}
void BTree::PostOrder(nodo *rad){
    nodo *temp = rad;
    if(temp){
        PostOrder(temp->sx);
        PostOrder(temp->dx);
        cout<<" "<<temp->dato;
    }
}

void BTree::stampaLivello(nodo* p, int level){ // stampa i nodi ad un dato livello
    // p punta ad una posizione vuota
    if(p == 0){ //se quella radice è nulla e se ci troviamo al livello da stampare, allora stampa _ in modo da indicare che è vuoto
        if (level==0) cout << "_\t";
        return;
    }

    if(level == 0) //se siamo al livello da stampare, stampiamo il dato
       cout << p->dato << "\t";
    else if(level>0){ //se non siamo al livello, allora in modo ricorsivo rifacciamo la stessa cosa in modo ricorsivo.
        stampaLivello(p->sx,level-1);
        stampaLivello(p->dx,level-1);
    }

}

int BTree::altezza(nodo* p)const{
    if (p==0) return 0; //se la radice è nulla, allora ritorna 0;

    int lh = altezza(p->sx);  // altrimenti in maniera ricorsiva contiamo i livelli sia a dx che a sx, e vediamo quale è maggiore
    int rh = altezza(p->dx);

    if(lh>rh)   return (lh+1); 
    else        return (rh+1);
}

void BTree::stampaalbero(nodo *p){
    for (int i = 0; i < altezza(radice); i++)
    {
        stampaLivello(i);
        cout<<endl;
    }
    return;
}


int main(){
    BTree albero;                                  // generiamo l'albero
	albero.Insert('1');                                 // popoliamo l'albero
	albero.Insert('4');
	albero.Insert('a');
	albero.Insert('b');
	albero.Insert('2');
	albero.Insert('8');
	cout << "PreOrdine: ";
	albero.PreOrder(); cout << endl;
    cout << "InOrdine: ";
	albero.InOrder(); cout << endl;
    cout << "PostOrdine: ";
	albero.PostOrder(); cout << endl;
    albero.stampaalbero();
}