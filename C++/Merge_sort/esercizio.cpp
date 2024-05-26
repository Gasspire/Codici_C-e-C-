#include <iostream>
using namespace std;

void printarray(int array[], int lenght){
    for (int i = 0; i<lenght; i++){
        cout<<" "<<array[i]<<" ";
    }
    cout<<endl;
    return;
}

void merge(int array[],int leftindex,int midindex,int rightindex){
    //Adesso creiamo dei contatori che ci servono per scorrere gli array, ricordiamoci che non partiranno da 0, bensì dall'indice più a sinistra
    int i = leftindex;
    int j = midindex+1;
    int k = leftindex;
    //Creiamo un array temporaneo che ci funge da appoggio
    int arraytemp[10];
    //Bene, ora scorriamo i nostri due array separatamente fino a quando uno dei due non finisce
    while (i<= midindex && j <= rightindex)
    {
        if(array[i]<=array[j]){
            arraytemp[k]= array[i];
            i++;
            k++;
        }
        else{
            arraytemp[k]= array[j];
            j++;
            k++;
        }
    }
    //Una volta usciti da questo while, vuol dire solo che abbiamo finito gli elementi di uno dei due array, o di entrambi.
    //quindi nel dubbio aggiungiamo gli ultimi elementi dell'array (nel caso in cui ce ne siano)
    while (i <= midindex) {
        arraytemp[k] = array[i];
        i++;
        k++;
    }

    while (j <= rightindex) {
        arraytemp[k] = array[j];
        j++;
        k++;
    }
    //Finiamo di copiare l'array temporaneo su quello definitivo
    for (int p = leftindex; p <= rightindex; p++) {
        array[p] = arraytemp[p];
    }
    printarray(array,rightindex+1);
}

void mergeSort(int array[], int lelftindex, int rightindex) {
    //Troviamo l'indice medio dell'array in modo da suddividerlo in 2 array più piccoli
    int midindex;
    if (lelftindex<rightindex)
    {
        midindex = (lelftindex+rightindex) / 2;
        //Bene, ora che abbiamo l'array diviso in due parti, dividiamolo ancora fino ad avere degli array di soli 2 elementi
        //Tutto questo viene fatto in modo ricorsivo
        mergeSort(array,lelftindex,midindex);
        mergeSort(array,midindex+1,rightindex);
        //A questo punto dobbiamo "Fonderli tutti assieme", usando una funzione che chiameremo merge
        merge(array,lelftindex,midindex,rightindex);
    }
}


int main(){
    int Array[]={5,4,2,1,7,0,3,6};
    int lenght = 8;
    printarray(Array,lenght);
    mergeSort(Array,0,lenght-1);
    printarray(Array,lenght);


}