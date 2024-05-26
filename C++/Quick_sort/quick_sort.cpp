#include <iostream>
using namespace std;

void printarray(int array[], int lenght){
    for (int i = 0; i<lenght; i++){
        cout<<" "<<array[i]<<" ";
    }
    cout<<endl;
    return;
}

void swap(int array[],int pos1,int pos2){
    int temp;
	temp = array[pos1];
	array[pos1] = array[pos2];
	array[pos2] = temp;
}

int partition(int arr[], int low, int high, int pivot){
    //Questa funzione ci permette di trovare la posizione corretta del nostro pivot
	int i = low;
	int j = low;
	while( i <= high){ //Si mette maggiore uguale perché appena i arriva ad high, deve fare l'ultimo scambio
		if(arr[i] > pivot){
            //troviamo il primo elemento dell'array più piccolo rispetto al nostro pivot
			i++;
		}
		else{
            //trovato l'elemento più piccolo del pivot, lo scambiamo con il j-esimo elemento del nostro array che sarà più grande del pivot
            //sappiamo per certo che sarà più grande perché altrimenti verrebbe scelto prima quell'elemento rispetto all'i-esimo
            cout<<"Sto swappando "<<i<<" "<<j<<endl;
            printarray(arr,high+1);
			swap(arr,i,j);
			i++;
			j++;
		}
	}
	return j-1;
}

void quickSort(int arr[], int low, int high){
    if (low<high){
        //Scegliamo il pivot in modo che sia l'ultimo elemento dell'array
        int pivot = arr[high];
        int pos = partition(arr,low,high,pivot);
        //Adesso abbiamo che il nostro pivot sarà nella corretta posizione e da qui lo dividiamo in due sottoarray cioè 0 - pos-1 e pos+1 - high.
        //N.B: Non prendiamo pos come elemento perché altrimenti prenderemmo l'elemento che si trova già nella posizione corretta!
        //su questi applichiamo ricorsivamente l'algoritmo e otterremo l'array ordinato!
        quickSort(arr,low,pos-1);
        quickSort(arr,pos+1,high);
    }
}

int main(){
    int Array[]={1,9,7,3,2,5};
    int lenght = 6;
    printarray(Array,lenght);
    quickSort(Array,0,lenght-1);

}