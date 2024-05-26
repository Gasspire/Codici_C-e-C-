/****************** Una stampante è caratterizzata dal livello di inchiostro (int) delle singole 
cartucce C M Y K; le cartucce non possono essere ricaricate ma sostituite (con valore come parametro);
la stampante permette di stampare singoli fogli o più copie di uno stesso foglio
(passando i livelli di inchiostro richiesti per la stampa di quel foglio);
si può sempre verificare il livello di inchiostro di una cartuccia.
Ragionare su quali attributi e metodi sono presenti e sul codice dei metodi 
(si ragioni su come gestire le stampe soprattutto nel caso non ci sia inchiostro sufficiente).
Creare la classe e un main.

*******************************************************************************/
#include <iostream>
using namespace std;

class Stampante{
    private:
        int C;
        int M;
        int Y;
        int K;
    public:
        Stampante(int x=100,int y=100,int z=100,int k=100){
            C=x;
            M=y;
            Y=z;
            K=k;
        }
        void sostituisciCartuccia(char colore, int inchiostro){
            switch (colore)
            {
            case 'C':
                C = inchiostro;
                break;
            case 'M':
                M = inchiostro;
                break;
            case 'Y':
                Y = inchiostro;
                break;
            case 'K':
                K = inchiostro;
                break;
            default:
                cout<<"Errore, colore selezionato non valido!";
                break;
            }
        }
        void stampa(int quanti_C,int quanti_M,int quanti_Y,int quanti_K, int copie){
            quanti_C = quanti_C*copie;
            quanti_M = quanti_M*copie;
            quanti_Y = quanti_Y*copie;
            quanti_K = quanti_K*copie;
            if(quanti_C>C) {
                cout<<"Errore, colore C non sufficiente per la stampa!";
                return;
            }
            if(quanti_M>M){ 
                cout<<"Errore, colore M non sufficiente per la stampa!";
                return;
            }
            if(quanti_Y>Y){
                cout<<"Errore, colore Y non sufficiente per la stampa!";
                return;
            }
            if(quanti_K>K){
                cout<<"Errore, colore K non sufficiente per la stampa!";
                return;
            }
            C=C-quanti_C;
            M=M-quanti_M;
            Y=Y-quanti_Y;
            K=K-quanti_K;
        }
        void printcartucce(){
            cout<<"Quantita' di C : "<<C<<" di M : "<<M<<" di Y "<<Y<<" di K "<<K<<endl;
        }
};





int main(){
    Stampante stampante;
    stampante.printcartucce();
    stampante.stampa(4,5,2,1,10);
    stampante.printcartucce();
}