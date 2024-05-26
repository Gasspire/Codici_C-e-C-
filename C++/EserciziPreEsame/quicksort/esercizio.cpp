#include <iostream>
using namespace std;




template <typename t> void printarray(t array[],int lenght){
    for (int i = 0; i < lenght; i++)
    {
        cout<<array[i]<<endl;
    }
    return;
}

void swap(int array[],int i,int j){
    int aux = array[i];
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
    int array[10] = {9,4,2,8,1,0,5,3,7,6};
    int lenght = 10;
    printarray(array,lenght);
    quicksort(array,0,lenght-1);
    cout<<"Print post quicksort!"<<endl;
    printarray(array,lenght);
    
}