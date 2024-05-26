#include <iostream>
#include <cstring>
#include <fstream>
using namespace std;


class Attrezzatura{
    protected:
        string nome;
        string marca;
        int anno_acquisto;
    public:
        Attrezzatura(){
            nome = " ";
            marca =" ";
            anno_acquisto = 0;
        }
        Attrezzatura(string c_name,string c_marca, int c_anno){
            nome = c_name;
            marca = c_marca;
            anno_acquisto = c_anno;
        }
        string getname(){return nome;}
        string getmarca(){return marca;}
        int getanno(){return anno_acquisto;}
        void setname(string c_nome){nome = c_nome; }
        void setmarca(string c_marca){nome = c_marca; }
        void setanno(int c_anno){anno_acquisto = c_anno;}
        virtual ostream& write(ostream& os)const{
            os<<"Nome "<<nome<<" Marca "<<marca<<" Acquistato nel "<<anno_acquisto<<endl;
            return os;
        }
        virtual void inserisci(){
            cout<<"Inserisci i dati separati da ;"<<endl;
            char buffer[524];
            cin>>buffer;

            nome = strtok(buffer,";");
            marca = strtok(buffer,";");
            anno_acquisto = atoi(strtok(buffer,";"));
            return;
        }
        virtual bool getattivo(){return true;}
};


class AttrezzoCardio: public Attrezzatura{
    protected:
        int potenza;
        bool attivo;
    public:
        AttrezzoCardio() : Attrezzatura(){
            potenza = 0;
            attivo = false;
        }
        AttrezzoCardio(string c_name,string c_marca, int c_anno,int c_potenza,bool c_uso = true) : Attrezzatura(c_name,c_marca,c_anno){
            potenza = c_potenza;
            attivo = c_uso;
        }
        bool getattivo(){return attivo;}
        void inserisci(){
            cout<<"Inserisci i dati separati da ;"<<endl;
            char buffer[524];
            cin>>buffer;

            nome = strtok(buffer,";");
            marca = strtok(NULL,";");
            anno_acquisto = atoi(strtok(NULL,";"));
            potenza =  atoi(strtok(NULL,";"));
            char *token;
            token = strtok(NULL,"\n");
            if(strcmp(token,"True")){
                attivo = true;
            }
            else{
                attivo = false;
            }
            
            return;
        }
        ostream& write(ostream& os)const{
            os<<"Nome "<<nome<<" Marca "<<marca<<" Acquistato nel "<<anno_acquisto<<" Potenza "<<potenza<<"watt ";
            if(attivo){
                os<<"in uso"<<endl;
            }
            else{
                os<<"non in uso"<<endl;
            }
            return os;
        }
};

class AttrezzoPesi: public Attrezzatura{
    protected:
        int peso;
        bool attivo;
    public:
        AttrezzoPesi(): Attrezzatura(){
            peso = 0;
            attivo = false;
        }
        AttrezzoPesi(string c_name,string c_marca, int c_anno,int c_peso,bool uso) : Attrezzatura(c_name,c_marca,c_anno){
            peso = c_peso;
            attivo = uso;
        }
        bool getattivo(){return attivo;}
        void inserisci(){
            cout<<"Inserisci i dati separati da ;"<<endl;
            char buffer[524];
            cin>>buffer;

            nome = strtok(buffer,";");
            marca = strtok(NULL,";");
            anno_acquisto = atoi(strtok(NULL,";"));
            peso =  atoi(strtok(NULL,";"));
            char *token;
            token = strtok(NULL,"\n");
            if(strcmp(token,"True") == 0){
                attivo = true;
            }
            else{
                attivo = false;
            }
            
            return;
        }
        ostream& write(ostream& os)const{
            os<<"Nome "<<nome<<" Marca "<<marca<<" Acquistato nel "<<anno_acquisto<<" Peso "<<peso<<"kg ";
            if(attivo){
                os<<"in uso"<<endl;
            }
            else{
                os<<"non in uso"<<endl;
            }
            return os;
        }
};


ostream& operator<<(ostream& os,Attrezzatura &miaattrezzatura){
    return miaattrezzatura.write(os);
}


class Palestra{
    protected:
        string nome;
        Attrezzatura *attrezzi[20];
        int numattrezzi;
    public:
        Palestra(){
            attrezzi[0] = NULL;
            numattrezzi = 0;
        }
        Palestra(string c_nome){
            nome = c_nome;
            numattrezzi = 0;
        }
        void aggiungiAttrezzo(Attrezzatura *newattrezzo){
            if(numattrezzi<20){
                attrezzi[numattrezzi] = newattrezzo;
                numattrezzi++;
            }
            else{
                cout<<"Impossibile aggiungere altri attrezzi"<<endl;
            }
        }
        int contaAttrezziDisponibili(){ 
            int conta = 0;
            for (int i = 0; i < numattrezzi; i++)
            {
                if(attrezzi[i]->getattivo()){
                    conta++;
                }
            }
            return conta;          
        }
    friend ostream& operator<<(ostream& os,Palestra palestra){
        os<<" "<<palestra.nome<<" ha attrezzi  : "<<endl;
        for (int i = 0; i < palestra.numattrezzi; i++){
            os<<*palestra.attrezzi[i]<<endl;
        }
        return os;
    }
};



void CaricaPalestra(Palestra &miapalestra){
    ifstream miofile("Jeasi.txt");
    if(miofile.is_open());
    else{
        exit(-1);
    }
    string buffer;
    while (getline(miofile,buffer,';'))
    {
        if(buffer == "#A"){
            cout<<"Sto leggendo un Attrezzatura semplice"<<endl;
            getline(miofile,buffer,';');
            string name = buffer;
            getline(miofile,buffer,';');
            string marca = buffer;
            getline(miofile,buffer,'\n');
            int anno = stoi(buffer);
            Attrezzatura *p = new Attrezzatura(name,marca,anno);
            miapalestra.aggiungiAttrezzo(p);

        }        
        if(buffer == "#AC"){
            cout<<"Sto leggendo un Attrezzatura da Cardio (fimmini...)"<<endl;
            getline(miofile,buffer,';');
            string name = buffer;
            getline(miofile,buffer,';');
            string marca = buffer;
            getline(miofile,buffer,';');
            int anno = stoi(buffer);
            getline(miofile,buffer,';');
            int potenza = stoi(buffer);
            getline(miofile,buffer,'\n');
            bool attivo;
            if(buffer == "True" || buffer =="true"){
                attivo = true;
            }
            else{
                attivo = false;
            }
            AttrezzoCardio *p = new AttrezzoCardio(name,marca,anno,potenza,attivo);
            miapalestra.aggiungiAttrezzo(p);
        }
        if(buffer == "#AP"){
            cout<<"Sto leggendo un Attrezzatura da CHAD (VAI UOMO)"<<endl;
            getline(miofile,buffer,';');
            string name = buffer;
            getline(miofile,buffer,';');
            string marca = buffer;
            getline(miofile,buffer,';');
            int anno = stoi(buffer);
            getline(miofile,buffer,';');
            int peso = stoi(buffer);
            getline(miofile,buffer,'\n');
            bool attivo;
            if(buffer == "True" || buffer =="true"){
                attivo = true;
            }
            else{
                attivo = false;
            }
            AttrezzoPesi *p = new AttrezzoPesi(name,marca,anno,peso,attivo);
            miapalestra.aggiungiAttrezzo(p);
        }
    }
    miofile.close();
}


int main(){
    Palestra Jeasi("Jeasi");
    CaricaPalestra(Jeasi);
    cout<<Jeasi;
}