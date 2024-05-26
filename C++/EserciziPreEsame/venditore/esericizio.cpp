#include <iostream>
#include <fstream>
using namespace std;



class Prodotto{
    protected:
        string name;
        static int nextcodice;
        int codice;
        double prezzo;
    public:
        Prodotto(){
            name = "noname";
            codice = nextcodice;
            nextcodice++;
            prezzo = 5.00;
        }
        Prodotto(string c_name, double c_prezzo){
            name = c_name;
            prezzo = c_prezzo;
            codice = nextcodice;
            nextcodice++;
        }
        double getprezzo(){return prezzo;}
        virtual double gettotale(){return prezzo;}
        void setprezzo(double c_prezzo){prezzo = c_prezzo;}
        int getcodice(){return codice;}
        void setcodice(int c_cod){codice = c_cod;}
        virtual ostream& write(ostream &os){
            os<<"["<<codice<<"] "<<name<<" : "<<prezzo<<" euro"<<endl;
            return os;
        }
};

int Prodotto :: nextcodice = 0;

class ProdottoAlimentare:public Prodotto{
    protected:
        int datascadenza;

    public:
        ProdottoAlimentare() : Prodotto(){
            datascadenza = 0;
        }
        ProdottoAlimentare(string c_name, double c_prezzo,int c_data) : Prodotto(c_name,c_prezzo){
            datascadenza = c_data;
        }
        bool Verifica(){
            if(datascadenza>20230622){
                return true;
            }
            else{
                return false;
            }
        }
        double gettotale(){
            if(Verifica()) return prezzo;
            else return 0;
        }
        int getscadenza(){return datascadenza;}
        void setscadenza(int c_scadenza){
            datascadenza = c_scadenza;
        }
        ostream& write(ostream& os){
            os<<"["<<codice<<"] "<<name<<" : "<<prezzo<<" euro "<<"Il prodotto scade il "<<datascadenza;
            if(Verifica()) os<<endl;
            else{
                os<<" il prodotto e' scaduto"<<endl;
            }
            return os;
        }
};


class ProdottoPerBambini : public Prodotto{
    protected:
        static string fasceselettore[4];
        string fascia;
    public:
        ProdottoPerBambini() : Prodotto(){
            fascia = fasceselettore[0];
        }
        ProdottoPerBambini(string c_name, double c_prezzo,int c_fascia) : Prodotto(c_name,c_prezzo){
            fascia = fasceselettore[c_fascia];    
        }
        ProdottoPerBambini(string c_name, double c_prezzo,string c_fascia) : Prodotto(c_name,c_prezzo){
            fascia = c_fascia;    
        }
        ostream& write(ostream &os){
            os<<"["<<codice<<"] "<<name<<" : "<<prezzo<<" euro"<<" per bambini dai "<<fascia<<" anni"<<endl;
            return os;
        }       
};


string ProdottoPerBambini :: fasceselettore[4] = {"0-3","3-6","6-9","9-12"};



ostream& operator<<(ostream& os,Prodotto &miop){
    return miop.write(os);
}

class Venditore{
    protected:
        string name;
        static int nextcodice;
        int codice;
        Prodotto *arrayprodotti[20];
        int numprodotti = 0;
    public:
        Venditore(){
            name = "noname";
            codice = nextcodice;
            nextcodice++;
        }
        Venditore(string c_name){
            name = c_name;
            codice = nextcodice;
            nextcodice++;
        }
        double CalcolaPrezzoTotale(){
            double tot = 0;
            for (int i = 0; i < numprodotti; i++)
            {  
                tot = tot + arrayprodotti[i]->getprezzo();
            }
            return tot;
        }
        double CalcolaValoreMagazzino(){
            double tot = 0;
            for (int i = 0; i < numprodotti; i++)
            {  
                tot = tot + arrayprodotti[i]->gettotale();
            }
            return tot;
        }
        void AggiungiProdotto(Prodotto *p){
            if(numprodotti<20){
                arrayprodotti[numprodotti] = p; 
                numprodotti++;
            }
            else{
                cout<<"Errore magazzino pieno"<<endl;
                return;
            }
        }
        friend ostream& operator<<(ostream& os,Venditore p){
            os<<"["<<p.codice<<"] "<<p.name<<" ha : "<<endl;
            os<<"_______________________________________"<<endl;
            for (int i = 0; i < p.numprodotti; i++)
            {
                os<<*p.arrayprodotti[i];
            }
            os<<"_______________________________________"<<endl;
            os<<"Valore magazzino : "<<p.CalcolaValoreMagazzino()<<endl;
            return os;
        }     
};

int Venditore:: nextcodice = 0;

void swap(Venditore *array[],int i, int j){
    Venditore *aux;
    aux = array[i];
    array[i] = array[j];
    array[j] = aux;
}

int partition(Venditore *array[],int low,int high,double pivot){
    int i = low;
    int j = low;

    while (i<=high)
    {
        if(array[i]->CalcolaValoreMagazzino()>pivot){
            i++;
        }
        else{
            swap(array,i,j);
            i++;
            j++;
        }
    }
    
    return j-1;
    
}


void quicksort(Venditore *array[],int low,int high){
    if(low<high){
        double pivot = array[high]->CalcolaValoreMagazzino();
        int pos = partition(array,low,high,pivot);
        quicksort(array,low,pos-1);
        quicksort(array,pos+1,high);
    }
}


void caricavenditore(Venditore &P,string nomefile){
    nomefile = nomefile +".txt";
    ifstream miofile(nomefile);
    if (miofile.is_open()){
    }
    else{
        return;
    }
    string buffer;
    while (getline(miofile,buffer,';'))
    {
        if(buffer == "P"){
            getline(miofile,buffer,';');
            string nome = buffer;
            getline(miofile,buffer,'\n');
            double prezzo = stof(buffer);
            Prodotto *newprodotto = new Prodotto(nome,prezzo);
            P.AggiungiProdotto(newprodotto);

        }

        if(buffer == "PA"){
            getline(miofile,buffer,';');
            string nome = buffer;
            getline(miofile,buffer,';');
            double prezzo = stof(buffer);
            getline(miofile,buffer,'\n');
            int data = stod(buffer);
            ProdottoAlimentare *newprodotto = new ProdottoAlimentare(nome,prezzo,data);
            P.AggiungiProdotto(newprodotto);

        }
        if(buffer == "PPB"){
            getline(miofile,buffer,';');
            string nome = buffer;
            getline(miofile,buffer,';');
            double prezzo = stof(buffer);
            getline(miofile,buffer,'\n');
            string fascia = buffer;
            ProdottoPerBambini *newprodotto = new ProdottoPerBambini(nome,prezzo,buffer);
            P.AggiungiProdotto(newprodotto);
        }
    }
    miofile.close();
}



int main(){
    Venditore *Array[3];
    Array[0] = new Venditore("shop");
    caricavenditore(*Array[0],"primo");
    Array[1] = new Venditore("rinascente");
    caricavenditore(*Array[1],"rinascente");
    Array[2] = new Venditore("rinascente");
    caricavenditore(*Array[2],"cristaldi");
    quicksort(Array,0,2);
    


    char x = '0';
    while (x=='0')
    {
        cout<<"Benvenuto nel menu"<<endl<<"Cosa vuoi fare? : "<<endl;
        cout<<"1 Stampare un venditore "<<endl;
        cout<<"2 Stampare tutti i venditori in ordine crescente "<<endl;
        cout<<"3 Stampare tutti i venditori in ordine decrescente "<<endl;
        cout<<"9 Per uscire"<<endl;
        cin>>x;
        if(x == '1'){
            int s;
            cout<<"Quale venditore vuoi stampare?"<<endl;
            cin>>s;
            if(s<=2 && s>=0){
                cout<<endl<<*Array[s];
                x = '0';
            }
            else{
                cout<<"Scelta non valida!"<<endl;
                x = '0';
            }
        }
        else if(x == '2'){
            for (int i = 0; i < 3; i++)
            {
                cout<<*Array[i];
            }
            x = '0';
            
        }
        else if(x == '3'){
            for (int i = 2; i >= 0; i--)
            {
                cout<<*Array[i];
            }
            x = '0';
            
        }
        else if(x == '9'){
            cout<<"Arrivederci!"<<endl;
            exit(-1);
        }
        else{
            cout<<"Scelta non valida"<<endl;
            x = '0';
        }
    }
    
}