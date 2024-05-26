#include <iostream>
#include <fstream>
using namespace std;
#include <cstring>



class Prodotto{
    protected:
        string nome;
        int codice;
        static int prossimocodice;
        double prezzo;
    public:
        Prodotto(string c_nome = " ",double c_prezzo = 0){
            codice = prossimocodice;
            prossimocodice++;
            nome = c_nome;
            prezzo = c_prezzo;
        }

        virtual double getprezzo(){ return prezzo;};

        int getcodice(){return codice;}
        string getnome(){return nome;}
        virtual ostream& write(ostream& output)const{
            output<<"["<<this->codice<<"] "<<this->nome<<" "<<this->prezzo<<endl;
            return output;
        }
};

int Prodotto::prossimocodice = 0;

ostream& operator<<(ostream& output,Prodotto const &p){
    return p.write(output);
}

class ProdottoPerBambini: public Prodotto{
    protected:
        string Fasciaeta;
        static string selettore[];
    public:
        ProdottoPerBambini(string c_nome,double c_prezzo, int c_fascia = 0) : Prodotto (c_nome,c_prezzo){
            Fasciaeta = selettore[c_fascia];
        }
        string getfascia(){return Fasciaeta;}
        int getfasciaint(){
            for (int i = 0; i < 4; i++)
            {
                if(Fasciaeta == selettore[i]) return i;
            }
            
        }
        ostream& write(ostream& output)const{
            output<<"["<<this->codice<<"] "<<this->nome<<" "<<this->prezzo<<" "<<this->Fasciaeta<<endl;
            return output;
        }
};

string ProdottoPerBambini::selettore[4] = {"0-3", "3-6", "6-9", "9-12"};

class ProdottoAlimentare: public Prodotto{
    protected:
        unsigned int scadenza;
    public:
        ProdottoAlimentare(string c_nome,double c_prezzo,int c_scadenza): Prodotto(c_nome,c_prezzo){
            scadenza = c_scadenza;
        }
        
        bool verifica(){
            if(scadenza>20230613)return true;
            else return false;
        }
        double getprezzo(){
            if(verifica()) return prezzo;
            else return 0;
        }
        unsigned int getscadenza(){return scadenza;}
        
        
        ostream& write(ostream& output)const{
            output<<"["<<this->codice<<"] "<<this->nome<<" "<<this->prezzo<<" "<<this->scadenza<<endl;
            return output;
        }
};

class Venditore{
    protected:
        int codVenditore;
        string nome;
        int numProdotti=0;
        int dimMagazzino=20;
        static int prossimoCodice;
        Prodotto *magazzino[20];
    public:
        Venditore(string c_nome){
            nome = c_nome;
            codVenditore = prossimoCodice;
            prossimoCodice++;
        }
        void aggiungiProdotto(Prodotto *p){
            if(dimMagazzino < numProdotti+1){
                return;
            }
            magazzino[numProdotti] = p;
            numProdotti++;
        }
        double getTotaleMagazzino()const{
            double s=0;
            for(int i=0;i<numProdotti;i++){
                s+= magazzino[i]->getprezzo();
            }
            return s;
            
        }
    friend
    ostream& operator<<(ostream& os, Venditore const &v){
        os << "[VEN"<< v.codVenditore << "]\t"<< v.nome
                    << "\tMagazzino["<< v.numProdotti<< "/"<<v.dimMagazzino<<"]:"
                    << " TOT. EUR " << v.getTotaleMagazzino() << endl;
        for(int i=0;i<v.numProdotti;i++)
            os << "\t"<< *(v.magazzino[i]) << endl;
        return os;
    }
};

int Venditore::prossimoCodice=0;

int main(){
    ProdottoAlimentare cs("lattuga",5.50,20240613);
    ProdottoPerBambini ss("macchina",5.50,1);
    Venditore armani("armani");
    armani.aggiungiProdotto(&cs);
    armani.aggiungiProdotto(&ss);
    cout<<armani;
    cout<<armani.getTotaleMagazzino();

}