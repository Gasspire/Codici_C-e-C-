
#include <iostream>
#include <cstring>
#include <ctime>
#include <fstream>
#include <cstdlib>
#include <sstream>
#include <iostream> 
using namespace std;


//to string
#define to_string( x ) static_cast< std::ostringstream & >( \
        ( std::ostringstream() << std::dec << x ) ).str()
        

//string to int
int stoi(string x){
	
    int i;
    std::istringstream(x) >> i;
    return i;
}




class Prodotto{
protected: // attributi protected in modo da potervi accedere nelle sottoclassi
    static int prossimoCodice; // si incrementa ogni volta che creo un nuovo Prodotto (o sottoclasse)
    int codice;
    string nome;
    double prezzo;

public:
    //Prodotto(): prezzo(0), nome(""), codice(prossimoCodice++) {/*cout << prossimoCodice << endl;*/}
    Prodotto(double _p, string _n): prezzo(_p), nome(_n), codice(prossimoCodice++){}
    Prodotto(): Prodotto(0, "<noname>"){}
    int getCodice() const { return codice;}
    //double getPrezzo() const {return prezzo;}
    double getPrezzoTotale(){ return prezzo;};
    virtual double getPrezzo(){ return prezzo;};
     string  getNome() const {return nome;}

    void inserisci(){
        cout << "Inserisci nome e prezzo del prodotto separati da ';': ";
        char buffer[512];
        cin >> buffer;

        char *token = strtok(buffer, ";");
        this->nome = token;
        //cout << "Nome:\t" << token << endl;
        token = strtok(NULL, ";");
        
        //atof trasforma una stringa in double
        this->prezzo = atof(token);
    }

    /*Implemento un metodo write() per stampare gli attributi, questo
    metodo sara' virtuale e pubblico (in alternativa, se lo voglio privato allora operator<<
    deve essere friend). A questo punto operator<< richiama write(). Dato che write() e'
    polimorfico verra' eseguita la versione della sottoclasse*/

    // metodo virtuale: pu� essere sovrasritto nelle sottoclassi
    virtual ostream& write(ostream& os)const{
        os << "["<<this->codice<<"]\t" << this->nome << "\t\tEUR " << this->prezzo;
        return os;    }

};

//un membro static deve essere inizializzato
int Prodotto::prossimoCodice = 0;

// operator<< che chiama write()
ostream& operator<<(ostream& os, Prodotto const &p){
        return p.write(os);
}



int getToday() {
    int retVal = 20230517;
    // OPPURE prendo la data corrente a runtime
    time_t now = time(0);

    // Converto 'now' nella struct tm definita in <ctime>
    tm *gmtm = gmtime(&now);
    int i_giorno = gmtm->tm_mday;
    // aggiungo uno '0' come prefisso se giorno e/o mese hanno valori minori di 10
    string giorno = (i_giorno<10)? "0"+to_string(i_giorno): to_string(i_giorno);
    //string giorno = (i_giorno<10)? "0"+to_string(i_giorno): to_string(i_giorno);
    int i_mese = gmtm->tm_mon +1;
    string mese = (i_mese<10)? "0"+to_string(i_mese): to_string(i_mese);
    int i_anno = gmtm->tm_year +1900;

    // compongo l'intero
    retVal = stoi(to_string(i_anno) + mese + giorno);
    //retVal = stoi(to_string(i_anno) + mese + giorno);

    return retVal;
}


class ProdottoAlimentare: public Prodotto{
    /* 12/03/2024 -->
        int:    20240312 (sistema posizionale)
        string: "20240312"    */

    string scadenza;
    // input: "20240312"  ->  output: 20240312
    int scadenzaInt() const { return stoi(scadenza);  }
    // restituisce il valore di scadenza nel formato "gg/mm/aaaa"
    string scadenzaString() const{
        return scadenza.substr(6,2) + "/" +
               scadenza.substr(4,2) + "/" +
               scadenza.substr(0,4);
    }
    // input: 12/03/2024  ->  output: set attributo scadenza "20240312"
    void setScadenza(string _exp){
        string gg, mm, aaaa;
        char buffer[512];
        strcpy(buffer, _exp.c_str());
        char *token = strtok(buffer, "/");
        gg = token;
        token = strtok(NULL, "/");
        mm = token;
        token = strtok(NULL, "/");
        aaaa = token;

        this->scadenza = aaaa + mm + gg;
        //cout << this->scadenza << endl;

    }
public:
    ProdottoAlimentare(){}
    // Richiamo il costruttore base nella lista di inizializzazione
    ProdottoAlimentare(double _p, string _n, string _exp): Prodotto(_p,_n){
        this->setScadenza(_exp);
    }
   

    bool verifica()const {
        int today = getToday();
        // se scadenza >= today il prodotto e' ancora buono
        return (this->scadenzaInt()>=today);
    }

    void inserisci(){
        cout << "Inserisci nome prezzo e data di scadenza del prodotto separati da ';': ";
        char buffer[512];
        cin >> buffer;

        char *token = strtok(buffer, ";");
        this->nome = token;
        token = strtok(NULL, ";");
        this->prezzo = atof(token);
        token = strtok(NULL, ";");
        this->setScadenza(token);
    }
    
    double getPrezzo(){
     if(verifica())
      return prezzo;
      else
      return 0;
    };


/*    friend   ostream& operator<<(ostream& os, ProdottoAlimentare const & p){
        os << "["<<p.codice<<"_ALIM]\t" << p.nome << "\t\tEUR "
            << p.prezzo << "\tEXP_DATE " << p.scadenzaString()
            << " (" << (p.verifica()? "buono)":"scaduto)");
        return os;   }  */
    ostream& write(ostream& os)const{
       os << "["<<this->codice<<"_PA]\t" << this->nome << "\t\tEUR "
            << this->prezzo << "\tEXP_DATE " << this->scadenzaString()
            << " (" << (this->verifica()? "buono)":"scaduto)");
         return os;    }


};
class ProdottoPerBambini: public Prodotto{
//  0-3, 3-6, 6-9, 9-12.
static string fasceEta[];
string fascia;
public:
    ProdottoPerBambini(){}
    ProdottoPerBambini(int f_eta): fascia(fasceEta[f_eta]){}
    ProdottoPerBambini(string f_eta): fascia(f_eta){}
    ProdottoPerBambini(double _p, string _n, int f_eta): Prodotto(_p,_n), fascia(fasceEta[f_eta]){}
    ProdottoPerBambini(double _p, string _n, string f_eta): Prodotto(_p,_n), fascia(f_eta){}
    string getFascia(){return fascia;}
    int getFasciaInt(){  // mi permette di confrontare le fasce
        for(int i=0;i<4;i++)
            if(fascia == fasceEta[i])
                return i;
        }
   ostream& write(ostream& os)const{
       os << "["<<this->codice<<"_PB]\t" << this->nome << "\t\tEUR "
            << this->prezzo << "\tFascia: " << this->fascia;
         return os;    }
         
         double getPrezzo(){return prezzo;};


};
string ProdottoPerBambini::fasceEta[4]= {"0-3", "3-6", "6-9", "9-12"};




// Implementazione di Venditore
//int STEP_DIM = 5;
class Venditore{
    int codVenditore;
    string nome;
    int numProdotti=0;
    int dimMagazzino=20;
    static int prossimoCodice;
    Prodotto *magazzino[20];
public:
    Venditore(string _n): nome(_n), codVenditore(prossimoCodice++){}
    Venditore():Venditore("<noname>"){}

    double calcolaPrezzoTotale()const{
        double s=0;
        for(int i=0;i<numProdotti;i++)
            s+= magazzino[i]->getPrezzoTotale();
        return s;
    }
    double calcolaValoreMagazzino() const{
        double s=0;
        for(int i=0;i<numProdotti;i++){
            s+= magazzino[i]->getPrezzo();
        }
        return s;
    }

    void aggiungiProdotto(Prodotto *p){
        if(dimMagazzino < numProdotti+1){

        }

        magazzino[numProdotti] = p;
        numProdotti++;
    }

    friend
    ostream& operator<<(ostream& os, Venditore const &v){
        os << "[VEN"<< v.codVenditore << "]\t"<< v.nome
                    << "\tMagazzino["<< v.numProdotti<< "/"<<v.dimMagazzino<<"]:"
                    << " TOT. EUR " << v.calcolaPrezzoTotale() << endl;
        for(int i=0;i<v.numProdotti;i++)
            os << "\t"<< *(v.magazzino[i]) << endl;
        return os;
    }

    bool operator>(const Venditore & v2)const{
        return this->calcolaPrezzoTotale() > v2.calcolaPrezzoTotale();
    }
};
int Venditore::prossimoCodice = 0;


void caricaVenditore(string nome, Venditore* v){
    string fname = nome+".txt";
    const int length = fname.length();
  
    // declaring character array (+1 for null terminator)
    char* char_array = new char[length + 1];
  
    // copying the contents of the
    // string to char array
    strcpy(char_array, fname.c_str());
    
    ifstream FileIn (char_array);

    int cnt =0;
    cout << endl<<"LETTURA DEL FILE " << fname << endl;
    for(string line; getline(FileIn, line);){
      //  cout << line << endl;
        // leggo il primo token
        // 1) se e' un P mi aspetto nome e prezzo
        // 2) se e' PA mi aspetto nome prezzo e data
        // 3) se e' PPB mi aspetto nome prezzo e fascia
        // devo definire dei metodi leggi() appositi
        char *buffer;
        buffer = strdup(line.c_str());
        char *token = strtok(buffer, "#");
        string tipo = token;

        string _n, _exp, _feta;
        double _p;
        token = strtok(NULL, ";");
        _n = token;
        token = strtok(NULL, ";");
        _p =  atof(token);

        //    Prodotto magazzino[10];
    // array di prodotti
  //  Prodotto* magazzino[10];

        if(tipo == "PA"){
            token = strtok(NULL, ";");
            _exp =  token; // data in formato gg/mm/aaaa

//            magazzino[cnt] = *(new ProdottoAlimentare(_p,_n,_exp));
  //          magazzino[cnt] = new ProdottoAlimentare(_p,_n,_exp);
            v->aggiungiProdotto(new ProdottoAlimentare(_p,_n,_exp));
        }
        else if(tipo == "PPB"){
            token = strtok(NULL, ";");
            _feta =  token; // fascia d'eta'
            //magazzino[cnt] = *(new ProdottoPerBambini(_p,_n,_feta));
            //magazzino[cnt] = new ProdottoPerBambini(_p,_n,_feta);
            v->aggiungiProdotto(new ProdottoPerBambini(_p,_n,_feta));
        }
        else{
//            magazzino[cnt] = *(new Prodotto(_p,_n));
     //       magazzino[cnt] = new Prodotto(_p,_n);
             v->aggiungiProdotto(new Prodotto(_p,_n));
        }
        //cout << *magazzino[cnt] << endl;
       // cout << "instance of PA:\t" << instanceof<ProdottoAlimentare>(magazzino[cnt]) << endl;
       // cout << "instance of PPB:\t" << instanceof<ProdottoPerBambini>(magazzino[cnt]) << endl;

        cnt++;
    }
    FileIn.close();

}

// insertion sort
template <typename T>
void insertionSort(T arr[], int n, bool crescente=true){
	int i,j;
	T key;
	for (i = 1; i < n; i++)	{
		key = arr[i];
		j = i - 1;
		if(crescente)
            while (j >= 0 && arr[j] > key){
                arr[j + 1] = arr[j];
                j = j - 1;
            }
        else // ordinamento decrescente
            while (j >= 0 && key > arr[j]){
                arr[j + 1] = arr[j];
                j = j - 1;
            }
		arr[j + 1] = key;
	}
}



int main(){


    Venditore shop = *(new Venditore("shop"));
    caricaVenditore("shop", &shop);
    cout << "stampo venditore"<< endl;
    cout << shop << endl<< endl;
    cout << "shop prezzo totale:\tEUR " << shop.calcolaPrezzoTotale() << endl;
    cout << "shop valore magazzino:\tEUR " << shop.calcolaValoreMagazzino() << endl;



    Venditore cristaldi = *(new Venditore("cristaldi"));
    caricaVenditore("cristaldi", &cristaldi);
    cout << "stampo venditore"<< endl;
    cout << cristaldi << endl<< endl;
    cout << "cristaldi prezzo totale:\tEUR " << cristaldi.calcolaPrezzoTotale() << endl;
    cout << "cristaldi valore magazzino:\tEUR " << cristaldi.calcolaValoreMagazzino() << endl;


    Venditore rinascente = *(new Venditore("rinascente"));
    caricaVenditore("rinascente", &rinascente);
    cout << "stampo venditore"<< endl;
    cout << rinascente << endl<< endl;
    cout << "rinascente prezzo totale:\tEUR " << rinascente.calcolaPrezzoTotale() << endl;
    cout << "rinascente valore magazzino:\tEUR " << rinascente.calcolaValoreMagazzino() << endl;


    Venditore mercato[] = {shop, cristaldi, rinascente};
    // menu per l'utente
    int scelta;
    do{
        cout << "Scegliere una operazione:" << endl
            << "0) stampa venditori in ordine crescente di prezzo totale" << endl
            << "1) stampa i venditori in ordine decrescente di prezzo totale" << endl
            << "Qualsiasi altro valore per uscire" << endl;
        cin >> scelta;
        cout << "Hai inserito: " << scelta << endl;

        switch(scelta){
        case 0:
            insertionSort(mercato,3);
            for(int i=0;i<3;i++)
                cout << mercato[i] << endl;
            break;
        case 1:
            insertionSort(mercato,3,false);
            for(int i=0;i<3;i++)
                cout << mercato[i] << endl;
            break;
        default:
		scelta =2;
		cout << "Ciao ciao!" << endl;
		break;
    }


    }while(scelta !=2);
    return 0;

}
