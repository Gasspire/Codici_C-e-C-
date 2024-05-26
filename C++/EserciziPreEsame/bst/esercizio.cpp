#include <iostream>
using namespace std;

struct nodo{
    int dato;
    nodo *dx;
    nodo *sx;
};


class BST{
    private:
        nodo* radice;
        void addnodo(nodo *&rad,int key);
        int altezza(nodo *rad)const;
        void stampalivello(nodo *rad,int level)const;
        void eliminanodo(nodo *&rad,int key);
    public:
        BST(){radice = NULL;}
        void addnodo(int key){addnodo(radice,key);}
        int altezza(){return altezza(radice);}
        void stampalivello(int level){stampalivello(radice,level);}
        void stampaalbero();
        void eliminanodo(int key){eliminanodo(radice,key);}
};

void BST::addnodo(nodo *&rad,int key){
    if(rad){
        if(key<rad->dato){
            if(rad->sx!=NULL) addnodo(rad->sx,key);
            else{
                nodo *newnodo = new nodo;
                newnodo->dato = key;
                newnodo->dx = NULL;
                newnodo->sx = NULL;
                rad->sx = newnodo;
            }
        }
        else{
            if(rad->dx != NULL) addnodo(rad->dx,key);
            else{
                nodo *newnodo = new nodo;
                newnodo->dato = key;
                newnodo->dx = NULL;
                newnodo->sx = NULL;
                rad->dx = newnodo;
            }
        }
    }
    else{
        nodo *newnodo = new nodo;
        newnodo->dato = key;
        newnodo->dx = NULL;
        newnodo->sx = NULL;
        rad = newnodo;
    }
}

int BST::altezza(nodo *rad)const{
    if(rad==0){
        return 0;
    }
    
    int sh =altezza(rad->sx);
    int rh =altezza(rad->dx);

    if(sh>rh) return sh+1;
    else return rh+1;
}

void BST::stampalivello(nodo *rad,int level)const{
    if(rad==0){
        if(level == 0){
            cout<<"_\t";
        }
        return;
    }

    if(level==0){
        cout<<rad->dato<<"\t";
    }
    else if(level>0){
        stampalivello(rad->sx,level-1);
        stampalivello(rad->dx,level-1);
    }
}

void BST::stampaalbero(){
    for (int i = 0; i < altezza(); i++)
    {
        stampalivello(i);
        cout<<endl;
    }
}


void BST::eliminanodo(nodo *&rad,int key){
    nodo *temp;
    if(rad){
        if(key<rad->dato)eliminanodo(rad->sx,key);
        else if(key>rad->dato) eliminanodo(rad->dx,key);
        else{
            if(rad->sx==NULL && rad->dx == NULL){
                temp = rad;
                rad = NULL;
                delete temp;
            }
            else if(rad->dx==NULL){
                temp = rad;
                rad = rad->sx;
                delete temp;
            }
            else if(rad->sx==NULL){
                temp = rad;
                rad =  rad->dx;
                delete temp;
            }
            else{
                temp = rad->dx;
                while (temp->sx !=NULL) temp = temp->sx;
                rad->dato = temp->dato;
                eliminanodo(rad->dx,temp->dato);
                return;
            }
        }
    }
    else{
        cout<<"Numero non presente"<<endl;
    }
}




int main(){
    BST albero;
    albero.addnodo(2);
    albero.addnodo(5);
    albero.addnodo(1);
    albero.addnodo(4);
    albero.addnodo(8);
    albero.addnodo(9);
    albero.addnodo(6);
    albero.addnodo(77);
    albero.addnodo(3);
    albero.addnodo(49);
    albero.addnodo(1);
    albero.stampaalbero();
    albero.eliminanodo(2);
    cout<<"Post eliminazione!"<<endl<<endl;
    albero.stampaalbero();

    
}