#include <iostream>
using namespace std;



class Prodotto{
    protected:
        int codice_prodotto;
        double prezzo;
    public:
        Prodotto(){
            codice_prodotto = 0;
            prezzo  = 0;
        }
        Prodotto(int c_cod, double c_prezzo){
            codice_prodotto = c_cod;
            prezzo  = c_prezzo;
        }
        int getcodiceprodotto(){return codice_prodotto;}
        int getprezzo(){return prezzo;}
        virtual double gettotale(){return prezzo;}
        void setcodiceprodotto(int c_cod){codice_prodotto = c_cod;}
        void setprezzo(double c_prezzo){prezzo = c_prezzo;}
};

class ProdottoPerBambini : public Prodotto{
    protected:  
    //  0-3, 3-6, 6-9, 9-12.
        static string fasceEta[];
        string fascia;
    public: 
        ProdottoPerBambini(){}
        ProdottoPerBambini(int f_eta): fascia(fasceEta[f_eta]){}
        ProdottoPerBambini(string f_eta): fascia(f_eta){}
        ProdottoPerBambini(int f_eta, int c_cod, double c_prezzo): Prodotto(c_cod,c_prezzo), fascia(fasceEta[f_eta]){}
        ProdottoPerBambini(string f_eta, int c_cod, double c_prezzo): Prodotto(c_cod,c_prezzo), fascia(f_eta){}
        string getfascia(){return fascia;}
        int getfasciaint(){
            for (int i = 0;i<4; i++){
                if(fascia == fasceEta[i]){return i;}
            }
        }
};

int today = 20230529;
string ProdottoPerBambini::fasceEta[4]= {"0-3", "3-6", "6-9", "9-12"};

class ProdottoAlimentare : public Prodotto{
    private:
        int datadiscadenza;
    public:
        ProdottoAlimentare(int c_scadenza,int c_cod, double c_prezzo) : Prodotto(c_cod,c_prezzo){
            datadiscadenza = c_scadenza;
        }
        ProdottoAlimentare() : Prodotto(){
            datadiscadenza = 0;
        }
        void setscadenza(int c_scadenza){datadiscadenza = c_scadenza;}
        int getscadenza(){return datadiscadenza;}
        bool verificascadenza(){
            if(datadiscadenza<today) return false;
            else return true;
        }
        double gettoale(){
            if(verificascadenza()){
                return prezzo;
            }
            else  return false;
        }
};

ostream& operator<< ( ostream& output,ProdottoPerBambini mio){
    output<<"Prodotto "<<mio.getcodiceprodotto()<<" prezzo "<<mio.getprezzo()<<" per la fascia d'eta' : "<<mio.getfascia()<<endl;
    return output;
}
ostream& operator<< (ostream& output, ProdottoAlimentare mioprodotto){
    output<<"Codice prodotto : "<<mioprodotto.getcodiceprodotto()<<" prezzo : "<<mioprodotto.getprezzo()<<" scade il : "<<mioprodotto.getscadenza()<<endl; 
    return output;
}
ostream& operator<< (ostream& output, Prodotto mioprodotto){
    output<<"Codice prodotto : "<<mioprodotto.getcodiceprodotto()<<" prezzo : "<<mioprodotto.getprezzo()<<endl; 
    return output;
}


int main(){
    ProdottoAlimentare Lattuga(20200529,1010,10.00);
}