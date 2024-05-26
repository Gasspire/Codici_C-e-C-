#include <iostream>
#include <fstream>
using namespace std;

struct nodo{
    int Pokedexnumber;
    string name;
    string type1;
    string type2;
    int Hp;
    int Attack;
    int Deff;
    int SpAttack;
    int SpDeff;
    int Speed;
    int bst;
    nodo *nextnodo;
};


ostream& operator<< (ostream& os,nodo *mionodo){
    os<<"Pokemon numero: "<<mionodo->Pokedexnumber<<" "<<mionodo->name<<" "<<"di tipo "<<mionodo->type1<<" "<<mionodo->type2<<endl;
    os<<"HP: "<<mionodo->Hp<<" Attack :"<<mionodo->Attack<<" Defense : "<<mionodo->Deff<<" Sp. Attack : "<<mionodo->SpAttack<<" Sp.Deff : "<<mionodo->SpDeff<<" Speed : "<<mionodo->Speed<<endl;
    os<<"Totale Bst "<<mionodo->bst<<endl<<endl;
    return os; 
}


class Pokedex{
    public:
        nodo *head;
    public:
        Pokedex(){head = NULL;}
        void Inserisci(int c_pokeid, string c_name,string c_type1,string c_type2,int c_hp, int c_attack,int c_deff,int c_SpAttack,int c_SpDeff,int c_speed ){
            nodo *newnodo = new nodo;
            newnodo->Pokedexnumber = c_pokeid;
            newnodo->name = c_name;
            newnodo->type1 = c_type1;
            newnodo->type2 = c_type2;
            newnodo->Hp = c_hp;
            newnodo->Attack = c_attack;
            newnodo->Deff = c_deff;
            newnodo->SpAttack = c_SpAttack;
            newnodo->SpDeff = c_SpDeff;
            newnodo->Speed = c_speed;
            newnodo->bst = c_hp+c_attack+c_deff+c_SpAttack+c_SpDeff+c_speed;
            newnodo->nextnodo = NULL;
            if(head==NULL){
                head = newnodo;
                return;
            }
            nodo* current = head;
            nodo* previous;
            while (current!=NULL)
            {
                previous = current;
                current = current->nextnodo;
            }
            previous->nextnodo = newnodo;
        }
        void Inserisci(nodo *nododaaggiungere){
            nodo *newnodo = new nodo;
            newnodo->Pokedexnumber = nododaaggiungere->Pokedexnumber;
            newnodo->name = nododaaggiungere->name;
            newnodo->type1 = nododaaggiungere->type1;
            newnodo->type2 = nododaaggiungere->type2;
            newnodo->Hp = nododaaggiungere->Hp;
            newnodo->Attack = nododaaggiungere->Attack;
            newnodo->Deff = nododaaggiungere->Deff;
            newnodo->SpAttack = nododaaggiungere->SpAttack;
            newnodo->SpDeff = nododaaggiungere->SpDeff;
            newnodo->Speed = nododaaggiungere->Speed;
            newnodo->bst = nododaaggiungere->bst;
            newnodo->nextnodo = NULL;
            if(head==NULL){
                head = newnodo;
                return;
            }
            else{
                nodo* current = head;
                nodo* previous;
                while (current!=NULL)
                {
                    previous = current;
                    current = current->nextnodo;
                }
                previous->nextnodo = newnodo;
            }
        }
        void Print(){
            nodo* current = head;
            if(current==NULL){
                cout<<"Lista vuota"<<endl;
                return;
            }
            while (current!=NULL)
            {
                cout<<current;
                current = current->nextnodo;
            }
        }
        void copiaGodmon(Pokedex &pokegod){
            nodo* current = head;
            if(current==NULL){
                cout<<"Lista vuota"<<endl;
                return;
            }
            while (current!=NULL)
            {
                if(current->bst>500) pokegod.Inserisci(current);
                current = current->nextnodo;
            }
        }
};


void Riempilista(Pokedex &pokedex){
    ifstream miofile("pokedex.txt");
    if(miofile.is_open()){
        cout<<"File caricato correttamente!"<<endl;
    }
    else{
        cout<<"Non sono riuscito ad aprire il file"<<endl;
        return;
    }
    string buffer;
    while (getline(miofile,buffer,','))
    {
        int pokeid = stoi(buffer);
        
        getline(miofile,buffer,',');
        string c_name = buffer;

        getline(miofile,buffer,',');
        string c_type1 = buffer;

        getline(miofile,buffer,',');
        string c_type2 = buffer;

        getline(miofile,buffer,',');
        int c_hp = stoi(buffer);

        getline(miofile,buffer,',');
        int c_attack = stoi(buffer);

        getline(miofile,buffer,',');
        int c_deff = stoi(buffer);

        getline(miofile,buffer,',');
        int c_SpAttack = stoi(buffer);

        getline(miofile,buffer,',');
        int c_SpDeff= stoi(buffer);
        
        getline(miofile,buffer,'\n');
        int c_speed = stoi(buffer);
        
        pokedex.Inserisci(pokeid,c_name,c_type1,c_type2,c_hp,c_attack,c_deff,c_SpAttack,c_SpDeff,c_speed);
    }

    cout<<"Pokedex caricato correttamente!"<<endl;
    miofile.close();
    return;
}




int main(){
    Pokedex Pokedex1;
    Riempilista(Pokedex1);
    Pokedex Godmon;
    Pokedex1.copiaGodmon(Godmon);
    Godmon.Print();
}