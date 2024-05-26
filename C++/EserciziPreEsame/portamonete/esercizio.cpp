#include <iostream>
using namespace std;

class Portamonete{
    protected:
        int monete50cent;
        int monete1euro;
        int monete2euro;
    public:
        Portamonete(){
            monete50cent = 0;
            monete2euro = 0;
            monete1euro = 0;
        }
        Portamonete(int c_50cent,int c_1euro,int c_2euro){
            monete50cent = c_50cent;
            monete2euro = c_2euro;
            monete1euro = c_1euro;
        }
        void Inserisci(double moneta){
            if(moneta == 2.0 || moneta == 1.00 || moneta == 0.50){
                if(moneta == 2.0) monete2euro++;
                if(moneta == 1.00) monete1euro++;
                if(moneta == 0.50) monete50cent++;
            }
            else{
                cout<<"valore non valido!"<<endl;
                return;
            }
        }        
        void Inserisci(double moneta,int quantita){
            if(moneta == 2.0 || moneta == 1.00 || moneta == 0.50){
                if(moneta == 2.0) monete2euro += quantita;
                if(moneta == 1.00) monete1euro+= quantita;
                if(moneta == 0.50) monete50cent+= quantita;
            }
            else{
                cout<<"valore non valido!"<<endl;
                return;
            }
        }
        double Denaro(){
            double totale = 0;
            totale = totale+(monete50cent * 0.5);
            totale = totale+(monete1euro * 1);
            totale = totale+(monete2euro * 2);
            return totale;
        }
};



int main(){
    Portamonete luigi;
    luigi.Inserisci(2,20);
    luigi.Inserisci(0.50,31);
    luigi.Inserisci(1,10);
    cout<<luigi.Denaro();
}