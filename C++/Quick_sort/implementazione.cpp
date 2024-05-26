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

int partition(int array[],int low, int high, int pivot){
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


void quickSort(int array[],int low,int high){
    if(low<high){
        int pivot = array[high];
        int pos = partition(array,low,high,pivot);
        quickSort(array,low,pos-1);
        quickSort(array,pos+1,high);
    }
}









int main(){
    int Array[]={1,9,7,3,9,5};
    int lenght = 6;
    printarray(Array,lenght);
    quickSort(Array,0,lenght-1);
    printarray(Array,lenght);

}