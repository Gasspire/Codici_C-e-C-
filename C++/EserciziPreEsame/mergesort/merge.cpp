#include <iostream>
using namespace std;


void merge(int array[],int leftindex,int midindex,int rightindex){
    int i = leftindex;
    int j = midindex +1;
    int k = leftindex;
    int arraytemp[rightindex];
    while (i<=midindex && j<=rightindex)
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
    for (int p = leftindex; p <= rightindex; p++)
    {
        array[p] = arraytemp[p];
    }  
}



void mergesort(int array[],int leftindex,int rightindex){
    if(leftindex<rightindex){
        int midindex = (leftindex + rightindex )/2;
        mergesort(array,leftindex,midindex);
        mergesort(array,midindex+1,rightindex);
        merge(array,leftindex,midindex,rightindex);
    }
}



int main(){
    int array[11] = {6,2,1,7,3,4,0,61,46,933,205};
    int lenght = 11;
    mergesort(array,0,lenght-1);
    for (int i = 0; i < lenght; i++)
    {
        cout<<array[i]<<" ";
    }
    
}