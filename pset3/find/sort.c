#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>

/**
 * 
**/

// maximum amount of hay
const int MAX = 65536;

void sort(int values[], int n);
void selectionSort(int values[], int n);
void bubbleSort(int values[], int n);
void insertionSort(int values[], int n);

// TODO: implement an O(n) sorting algorithm

// this function swaps the value of array indexed by index1 and index2
void swap(int values[], int index1, int index2);
// for debugging
void printArray(int values[], int n);



int main(void)
{
    
    // fill haystack
    int size;
    int haystack[MAX];
    for (size = 0; size < MAX; size++)
    {
        // wait for hay until EOF
        printf("\nhaystack[%i] = ", size);
        int straw = GetInt();
        if (straw == INT_MAX)
        {
            break;
        }
     
        // add hay to stack
        haystack[size] = straw;
    }
    printf("\n");
    
    printf("Before sorting:\n");
    printArray(haystack, size);
    //printf("------------------\n");
    sort(haystack, size);
    printf("After sorting:\n");
    printArray(haystack, size);
    return 0;
}


void sort(int values[], int n)
{
    // TODO: implement an O(n^2) sorting algorithm
    
    //selectionSort(values,n);
    bubbleSort(values, n);
    //insertionSort(values,n);
    return;
}

void printArray(int values[], int n){
    for (int i = 0; i<n; i++){
        printf("%d ", values[i]);
    }
    printf("\n");
}

void swap(int values[], int index1, int index2){
    int temp = values[index1];
    values[index1] = values[index2];
    values[index2] = temp;
}

void selectionSort(int values[], int n){
    int i;
    int j;
    int min_index;
    
    if (n <= 0){
        return;
    }
    // repeat until no unsorted item
    for(i = 0; i<n; i++){
        min_index = i;
        // find the index of the minimum value
        for(j = i; j<n; j++){
            if(values[j] <= values[min_index]){
                min_index = j;
            }
        }
    swap(values,i,min_index);
    }
    return;    
}

void bubbleSort(int values[], int n){
    // set swap to non-zero value to begin the algorithm
    int swap_counter = -1;
    int i;
    
    if (n <= 0){
        return;
    }
    
    //repeat until no swap happened, meaning swap counter is 0
    while(swap_counter != 0){
        swap_counter = 0;
        // for every adjacent pair that is out of order, swap them
        for(i = 0; i<n-1; i++){
            if(values[i]>= values[i+1]){
                swap(values,i,i+1);
                // increment the swap counter;
                swap_counter++;
            }
        }
    }
    return;
}

void insertionSort(int values[], int n){
    // Assume values[0] is sorted
    
    int i; //unsorted protion
    int curr_pos; //current traversing position
    int temp;
    
    if (n <= 0){
        return;
    }
    // the rest are unsorted portion
    for(i = 1; i<n; i++){
        // the index for calculating insertion position
        curr_pos = i;
        // holding the current value
        temp = values[i];
        //determine how many shifts are required to insert the holding item
        while(temp < values[curr_pos-1] && curr_pos > 0){
            // do the shifting
            values[curr_pos] = values[curr_pos-1];
            curr_pos--;
        }
        // insert the item
        values[curr_pos] = temp;
    }
    return;
}