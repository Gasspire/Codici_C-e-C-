/*Si supponga di dover implementare una procedura che sia in grado di fornire automaticamente il resto a seguito di un pagamento. A tal fine si supponga di avere a disposizione delle monete di n tagli differenti, e sia T un array di n elementi contenente il valore dei tagli disponibili. Si supponga, inoltre, sia R il valore del resto da fornire, con R maggiore o uguale a 0.
Si fornisca la definizione risocrsiva utile al calcolo del minimo numero di monete necessarie per fornire esattamente un resto pari a R.
(Si supponga che, per ogni taglio T[i], siano disponibili infinite monete)*/

#include <iostream>
using namespace std;


int trovamonetediresto(float restotarget,int T[],int n){
    if(restotarget==0) return 0;//resto raggiunto
    if(n == 0) return 2000; //impossibile raggiungere il resto
    int minimo = trovamonetediresto(restotarget,T,n-1);//scelta in cui non prendiamo l'ultimo
    if(T[n-1]<= restotarget){ 
        int s = 1 + trovamonetediresto(restotarget-T[n-1],T,n);
        if(s<minimo){
            minimo = s;
        }
    }
    return minimo;
} 



int main(){
    int totalepagamento = 35;
    int totalepagato = 50;
    int restotarget = totalepagato - totalepagamento;
    int T[]={1,2,5};
    cout<<"minimo di monete disponibili per raggiungere "<<restotarget<<" e' "<<trovamonetediresto(restotarget,T,3);
}