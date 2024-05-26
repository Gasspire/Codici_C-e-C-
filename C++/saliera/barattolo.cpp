#include <iostream>

using namespace std;

class Barattolo{
    private:
        int volume;
        int quantita;
    public:
        Barattolo(int c_volume = 100,int c_quantita = 100){
            volume = c_volume;
            quantita = c_quantita;
        }
        void visualizza(){
            cout<<"Il volume e' di : "<<volume<<" e attualmente contine : "<<quantita<<endl;
        }
};

int main(){
    Barattolo clever;
    clever.visualizza();
}