#include <iostream>
using namespace std;

void printarray(int array[],int lenght){
   for (int i = 0; i < lenght; i++)
    {
        cout<<" "<<array[i];
    }
    cout<<endl;

}

void swap(int array[],int i, int j){
    int aux;
    aux = array[i];
    array[i] = array[j];
    array[j] = aux;
}


int partition(int array[],int low,int high,int pivot){
    int i = low;
    int j = low;
    while (i<=high)
    {
        if(array[i]>pivot){
            i++;
        }
        else{
            swap(array,i,j);
            i++;
            j++;
        }
    }
    return j-1;
}




void quicksort(int array[],int low,int high){
    if(low<high){
        int pivot = array[high];
        int pos = partition(array,low,high,pivot);
        quicksort(array,low,pos-1);
        quicksort(array,pos+1,high);
    }
}


int main(){
    int array[7] = {6,4,2,1,3,0,7};
    int lenght = 7;
    quicksort(array,0,lenght-1);
    printarray(array,lenght);

}