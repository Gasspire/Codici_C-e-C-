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
    int i = leftindex;
    int j = midindex+1;
    int k = leftindex;
    int arraytemp[20];

    while (i<=midindex && j <= rightindex)
    {
        if(array[i]<=array[j]){
            arraytemp[k] = array[i];
            i++;
            k++;
        }
        else{
            arraytemp[k] = array[j];
            j++;
            k++;
        }
    }
    while (i<=midindex)
    {
        arraytemp[k] = array[i];
        i++;
        k++;
    }
    while (j<=rightindex)
    {
        arraytemp[k] = array[j];
        j++;
        k++;
    }
    
    for (int p = leftindex; p < rightindex; p++)
    {
        array[p] = arraytemp[p];
    }
    
    
}

void mergeSort(int array[], int lelftindex, int rightindex) {
    if(lelftindex<rightindex){
        int midindex = (lelftindex+rightindex)/2;
        mergeSort(array,lelftindex,midindex);
        mergeSort(array,midindex+1,rightindex);
        merge(array,lelftindex,midindex,rightindex);
    }
}





int main(){
    int Array[]={5,4,2,1,7,0,3,6,9,9};
    int lenght = 10;
    printarray(Array,lenght);
    mergeSort(Array,0,lenght-1);
    printarray(Array,lenght);
}