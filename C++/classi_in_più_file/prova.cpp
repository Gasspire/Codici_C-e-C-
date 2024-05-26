#include <iostream>
#include <cstring>
#include "User.h" //Qui aggiungiamo l'header delle classi a cui facciamo riferimento e naturalmente poi daremo al compilatore solo il file .cpp della classe
using namespace std;


int main(){
    User Giulio(400000,"Giulio","Cuttone","Grafik desiner!");
    cout<<"User registratco come : "<<Giulio.getname()<<" "<<Giulio.getsurname()<<" ha "<<Giulio.getage()<<" anni ed e' un "<<Giulio.getroleuser();
}