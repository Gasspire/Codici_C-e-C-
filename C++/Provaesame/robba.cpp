#include <iostream>
using namespace std;

class data{
private:
    int gg;
    int month;
    int years;
public:
    data(int c_gg = 0,int c_month = 0, int c_years = 0){
        gg = c_gg;
        month = c_month;
        years = c_years;
    }
    int getgiorno(){return gg;}
    void setgiorno(int c_gg){gg = c_gg;};
    int getmese(){return month;}
    void setmese(int c_month){month = c_month;}
    int getanno(){return years;}
    void setanno(int  c_years){years = c_years;}
    void printdata(){cout<<" "<<gg<<"/"<<month<<"/"<<years<<endl;}
    int controlladata(data data2){
        //Restituisce -1 se è minore la data corrente, 1 se è maggiore la data corrente,0 se è uguale;
        if(years > data2.getanno()){
            return 1;
        }
        else if(month > data2.getmese()){
            return 1;
        }
        else if(gg > data2.getgiorno()){
            return 1;
        }
        else if(years == data2.getanno() && month == data2.getmese() && gg == data2.getgiorno()){
            return 0;
        }
        else return -1;
    }
};

data today(27,5,2023);

class Prodotto{
    protected:
        int codice_prodotto;
        double prezzo;
    public:
        Prodotto(){
            codice_prodotto = 0;
            prezzo = 0;
        }
        Prodotto(int c_cod,double c_prezzo){
            codice_prodotto = c_cod;
            prezzo = c_prezzo;
        }
        int getcodiceprodotto(){return codice_prodotto;}
        void setcodiceprodotto(double c_cod){codice_prodotto = c_cod;}
        double getprezzo(){return prezzo;}
        virtual double gettotale(){return prezzo;}
        void setprezzo(double c_prezzo){prezzo = c_prezzo;}
        virtual void inserisci(){
            double prezzotemp;
            int codicetemp;
            cout<<"Inserisci il prezzo"<<endl;
            cin>>prezzotemp;
            setprezzo(prezzotemp);
            cout<<"Inserisci il codice prodotto "<<endl;
            cin>>codicetemp;
            setcodiceprodotto(codicetemp);
        }
};

class ProdottoAlimentare : public Prodotto{
    protected: 
        data datadiscadenza;
    public:
        ProdottoAlimentare(int c_cod,double c_prezzo, data c_datascadenza) : Prodotto(c_cod,c_prezzo){
            datadiscadenza = c_datascadenza;
        }
        data getscadenza(){return datadiscadenza;}
        void setscadenza(int gg,int month,int years){

        }
        bool verificascadenza(data oggi){
            if(datadiscadenza.controlladata(oggi)==0 || datadiscadenza.controlladata(oggi)==1){
                cout<<"Il prodotto e' scaduto!"<<endl;
                return false;
            }
            else{
                return true;
            }
        }
        double gettotale(){
            cout<<"funzione derivata!"<<endl;
            if (verificascadenza(today))
            {
                return prezzo;
            }
            else return 0;            
        }
        void inserisci(){
            double prezzotemp;
            int codicetemp;
            int ggtemp;
            int monthtemp;
            int yearstemp;
            cout<<"Inserisci il prezzo"<<endl;
            cin>>prezzotemp;
            setprezzo(prezzotemp);
            cout<<"Inserisci il codice prodotto "<<endl;
            cin>>codicetemp;
            setcodiceprodotto(codicetemp);
            cout<<"Inserisci il gg di scadenza"<<endl;
            cin>>ggtemp;
            cout<<"Inserisci il month di scadenza"<<endl;
            cin>>monthtemp;
            cout<<"Inserisci il years di scadenza"<<endl;
            cin>>yearstemp;
            datadiscadenza.setgiorno(ggtemp);
            datadiscadenza.setmese(monthtemp);
            datadiscadenza.setanno(yearstemp);
        }
};

class ProdottoPerBambini : public Prodotto{ //riprendi da qui!
    protected:
        int fascia_eta_minima;
        int fascia_eta_massima;
    public:
        ProdottoPerBambini(): Prodotto(){
            fascia_eta_massima = 3;
            fascia_eta_minima = 0;
            }
        ProdottoPerBambini(int c_cod,double c_prezzo,int c_massima,int c_minima) : Prodotto(c_cod,c_prezzo){
                fascia_eta_massima = c_massima;
                fascia_eta_minima = c_minima;
            }
        int getetamax(){return fascia_eta_massima;}
        int getetamin(){return fascia_eta_minima;}
        void inserisci(){
            double prezzotemp;
            int codicetemp;
            int fasciamintemp;
            int fasciamaxtemp;
            cout<<"Inserisci il prezzo"<<endl;
            cin>>prezzotemp;
            setprezzo(prezzotemp);
            cout<<"Inserisci il codice prodotto "<<endl;
            cin>>codicetemp;
            setcodiceprodotto(codicetemp);
            cout<<"Inserisci fascia minmima prodotto"<<endl;
            cin>>fasciamintemp;
            cout<<"Insersci fascia massima prodotto"<<endl;
            cin>>fasciamaxtemp;
            fascia_eta_massima = fasciamaxtemp;
            fascia_eta_minima = fasciamintemp;
        }
};

class Venditore{
    protected:
        int codicevenditore;
        int numeroprodotti;
        Prodotto *prodotti;
        int dimMagazzino;
    public:
        Venditore(){
            codicevenditore = 0;
            numeroprodotti = 0;
            dimMagazzino = 20;
        }
        Venditore(int c_codvenditore,int c_dimensionemagazzino){
            codicevenditore = c_codvenditore;
            numeroprodotti = 0;
            dimMagazzino = c_dimensionemagazzino;
            prodotti = (Prodotto*) new Prodotto[dimMagazzino];
        }

        void aggiungiProdotto(Prodotto nuovoprodotto){
            if(dimMagazzino<numeroprodotti){
                cout<<"Magazzino pieno!"<<endl;
                return;
            }
            else{
                prodotti[numeroprodotti] = nuovoprodotto;
                numeroprodotti++;
                if(numeroprodotti==dimMagazzino) numeroprodotti--;
                return;
            }
        }
        double calcolaPrezzoTotale()const{
            double s=0;
            for(int i=0;i<numeroprodotti;i++) s+= prodotti[i].getprezzo();
            cout<<"Totale e' : "<<s<<endl;
            return s;
        }
        double calcolaValoreMagazzino() const{
            double s=0;
            for(int i=0;i<numeroprodotti;i++){
                cout<<"sommo "<<prodotti[i].gettotale()<<endl;
                s+= prodotti[i].gettotale();
        }
        cout<<"Valore magazzino e' : "<<s<<endl;
        return s;
    }

};

ostream& operator<<  (ostream& output, Prodotto& prodotto){
    output<<"Codice : "<<prodotto.getcodiceprodotto()<<" prezzo : "<<prodotto.getprezzo()<<endl;
    return output;
}

ostream& operator<<  (ostream& output, ProdottoAlimentare& prodotto){
    output<<"Codice : "<<prodotto.getcodiceprodotto()<<" prezzo : "<<prodotto.getprezzo()<<" data di scadenza "<<prodotto.getscadenza().getgiorno()<<"/"<<prodotto.getscadenza().getmese()<<"/"<<prodotto.getscadenza().getanno()<<endl;
    return output;
}

ostream& operator<<  (ostream& output, ProdottoPerBambini& prodotto){
    output<<"Codice : "<<prodotto.getcodiceprodotto()<<" prezzo : "<<prodotto.getprezzo()<<" per la fascia d'eta' : "<<prodotto.getetamax()<<"-"<<prodotto.getetamin()<<endl;
    return output;
}


int main(){
    Venditore Calogero(5000,20);
    data scadenza(10,10,2024);
    data scadenza2(10,10,1900);
    ProdottoAlimentare lattuga(2402,5.00,scadenza);
    ProdottoPerBambini macchina(5002,15,10,6);
    ProdottoAlimentare passata(2402,20.00,scadenza2);
    Calogero.aggiungiProdotto(lattuga);
    Calogero.aggiungiProdotto(macchina);
    Calogero.aggiungiProdotto(passata);
    Calogero.calcolaValoreMagazzino();
}