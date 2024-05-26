#include <iostream>
#include <fstream>
using namespace std;


class Studente{
    protected:
        string nome;
        static string generefasce[2];
        string genere;
        string classe;
        double media;
    public:
        Studente(){
            nome = "noname";
            classe = " ";
            media = 0;
        }
        Studente(string c_nome = "_", string c_classe = "_", double c_media = 0.0,int genselett=0){
            nome = c_nome;
            classe = c_classe;
            media = c_media;
            genere = generefasce[genselett];
        }
        double getmedia(){return media;}        
        ostream& write(ostream& os){
            os<<nome<<" "<<genere<<" della "<<classe<<" e ha la media del "<<media<<endl;
            return os;
        }
};



ostream& operator<<(ostream& os,Studente s){
    return s.write(os);
}

string Studente :: generefasce[2] = {"F","M"};

class Classe{
    protected:
        string nome;
        Studente *array[20];
        int numalunni = 0;
    public:
        Classe(){
            nome = " ";

        }
        Classe (string c_nome){
            nome = c_nome;
        }
        void AggiungiStudente(Studente *P){
            if(numalunni<20){
                array[numalunni] = P;
                numalunni++;
            }
            else{
                cout<<"Classe al completo!"<<endl;
            }
        }
        double Media(){
            double somma = 0;
            for (int i = 0; i < numalunni; i++)
            {
                somma = somma + array[numalunni]->getmedia();
                cout<<array[numalunni]->getmedia();
            }
            return somma/numalunni;
        }
        friend ostream& operator<< (ostream& os,Classe p){
            os<<"La classe : "<<p.nome<<" ha "<<p.numalunni<<" alunni e sono: "<<endl;
            for (int i = 0; i < p.numalunni; i++)
            {
                os<<*p.array[i];
            }
            os<<"___________________________________"<<endl<<"La media della classe e' : "<<p.Media();
            return os;
        }
};

void CaricaClasse(Classe &p,string nomefile){
    nomefile = nomefile + ".txt";
    ifstream miofile(nomefile);
    string buffer;
    while (getline(miofile,buffer,';'))
    {
        string nome = buffer;
        getline(miofile,buffer,';');
        string classe = buffer;
        getline(miofile,buffer,';');

        double media = stof(buffer);
        int n = stod(buffer);
        Studente *sos = new Studente(nome,classe,media,n);
        p.AggiungiStudente(sos);
    
    }
    miofile.close();
}

int main(){
    Classe s2;
    CaricaClasse(s2,"classe");
    cout<<s2;
}