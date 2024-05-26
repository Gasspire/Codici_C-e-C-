// 20.9
/* Dato un albero binario di elementi di tipo int , scrivere funzioni che calcolino:
a) la somma dei suoi elementi;
b) la somma dei suoi elementi che sono multipli di 3.
* 
SUGGERIMENTO: metodo int Sommatoria(nodo*); ispira anche la stessa
* Sommatoria selezionando solo i multipli di 3 ... (BANALE)
*/


#include <iostream>
using namespace std;

struct nodo {
  int info;
  nodo *sx;
  nodo *dx;
};

int somma;

class btree {
public:
	btree() {radice = NULL;};
	~btree() {distruggi(radice);};
	void I(int chiave) {I(chiave, radice);};
	void E(int chiave) {E(chiave, radice);};
	void In(){In(radice);};
	void Pr(){Pr(radice);};
	void Po(){Po(radice);};
	int Sommatoria() {Sommatoria(radice);};
private:
    nodo *radice;
    void distruggi(nodo* &);
    void I(int, nodo* &);
    void E(int, nodo* &);
	void In(nodo*);
	void Pr(nodo*);
	void Po(nodo*);
	int Sommatoria(nodo*);
};


int btree::Sommatoria(nodo* p) {
	if(p) {
		Sommatoria(p->sx);
		Sommatoria(p->dx);
		somma += p->info;
	}
	
	return somma;
}

void btree::distruggi(nodo* &p) {
  if(p) {
    distruggi(p->sx);
    distruggi(p->dx);
    delete p;
  }
}

void btree::I(int chiave, nodo* &p) {
	if (p) {
		if(chiave < p->info) {
			if(p->sx != NULL) I(chiave, p->sx);
			else {
				p->sx = new nodo;
				p->sx->info = chiave;
				p->sx->sx = NULL; // il figlio sx del nuovo nodo è NULL
				p->sx->dx = NULL; // il figlio dx del nuovo nodo è NULL
			}  
		}
		else if(p->dx != NULL) I(chiave, p->dx);
			else {
				p->dx = new nodo;
				p->dx->info = chiave;
				p->dx->sx = NULL; // il figlio sx del nuovo nodo è NULL
				p->dx->dx = NULL; // il figlio dx del nuovo nodo è NULL
			}
	}
	else {
		p = new nodo;
		p->info = chiave;
		p->sx = NULL;
		p->dx = NULL;
	}	
}

void btree::E(int chiave, nodo* &p) {
	nodo* temp;
	if (p) {
		if(chiave < p->info) E(chiave, p->sx);
		else if(chiave > p->info) E(chiave, p->dx);
		     else {
		     if (p->sx==NULL && p->dx==NULL) {
				 temp = p;
				 p = NULL;
				 delete temp;
			 }
			 else if (p->sx == NULL) {
				temp = p;
				p = p->dx;
				delete temp;
				}
				else if (p->dx == NULL) {
					temp = p;
					p = p->sx;
					delete temp;
					}
				else {
					temp = p->dx;
					while (temp->sx != NULL) temp = temp->sx;
					p->info = temp->info;
            		E(temp->info, p->dx);
				}
		}	
	}
}

void btree:: In(nodo* p) {
	if (p) {
		In(p -> sx);
		cout << p->info << ' ';
		In(p -> dx);
		}
}

void btree:: Pr(nodo* p) {
	if (p) {
		cout << p->info << ' ';
		Pr(p -> sx);
		Pr(p -> dx);
		}
}

void btree:: Po(nodo* p) {
	if (p) {
		Po(p -> sx);
		Po(p -> dx);
		cout << p->info << ' ';
		}
}

int main() {
	btree albero;                                  // generiamo l'albero
	albero.I(1);                                 // popoliamo l'albero
	albero.I(4);
	albero.I(3);
	albero.I(6);
	albero.I(2);
	albero.I(8);
	somma=0; 
	cout << "Sommatoria: " << albero.Sommatoria() << endl;
	cout << "InOrdine: ";
	albero.In(); cout << endl;        // visualizziamo l'albero InOrdine
	cout << "PreOrdine: ";
	albero.Pr(); cout << endl;       // visualizziamo l'albero PreOrdine
	cout << "PostOrdine: ";
	albero.Po(); cout << endl;      // visualizziamo l'albero PostOrdine
	albero.E(6);                                 // eliminiamo un nodo
	cout << "InOrdine: ";
	albero.In(); cout << endl;
	cout << "PreOrdine: ";
	albero.Pr(); cout << endl;
	cout << "PostOrdine: ";
	albero.Po(); cout << endl;
	somma=0; cout << "Sommatoria: " << albero.Sommatoria() << endl;
}
