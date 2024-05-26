#include <iostream>
using namespace std;


template <typename t> void printarray(t array[],int lenght){
    for (int i = 0; i < lenght; i++)
    {
        cout<<array[i]<<endl;
    }
    return;
}

void merge(int array[],int leftindex,int midindex,int rightindex){
    int i = leftindex;
    int j = midindex + 1;
    int k = leftindex;
    int arraytemp[20];
    while (i<=midindex && j<= rightindex)
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
        int midindex = (leftindex+rightindex)/2;
        mergesort(array,leftindex,midindex);
        mergesort(array,midindex+1,rightindex);
        merge(array,leftindex,midindex,rightindex);
    }
}



int main(){
    int array[10] = {9,4,2,8,1,0,5,3,7,6};
    int lenght = 10;
    printarray(array,lenght);
    mergesort(array,0,lenght-1);
    cout<<"Post merge"<<endl;
    printarray(array,lenght);
    
}