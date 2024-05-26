#include <stdio.h>
#include <stdlib.h>
#include <limits.h>


void selection_sort(int array[],int size){
    int aux;
    for (int j = 0; j<10; j++){
        int minium = array[j];
        for (int i = j; i<10; i++){
            if(minium>array[i]){
                minium = array[i];
                aux = array[j];
                array[j] = minium;
                array[i] = aux;
            }
        }
    }
}


int main(){
    int A[10] = {10,5,3,2,1,7,8,4,6,9};
    for(int i = 0; i<10; i++){
        printf("A[%d] = %d \n",i,A[i]);
    }
    selection_sort(A,10);
    for(int i = 0; i<10; i++){
        printf("A[%d] = %d \n",i,A[i]);
    }
}