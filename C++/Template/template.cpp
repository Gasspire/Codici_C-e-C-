#include <iostream>
using namespace std;



template <typename t> void scambio(t &a, t &b){
    t c;
    c = a;
    a = b;
    b = c;
    return;
}





int main(){
    int a,b;
    a = 10;
    b = 50;
    scambio(a,b);
    cout<<"A : "<<a<<" B : "<<b<<endl;
    char s = 's';
    char S = 'S';
    scambio(s,S);
    cout<<"s : "<<s<<" S : "<<S<<endl;

}