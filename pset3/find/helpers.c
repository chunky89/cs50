/**
 * helpers.c
 *
 * Computer Science 50
 * Problem Set 3
 *
 * Helper functions for Problem Set 3.
 */
       
#include <cs50.h>
#include <stdio.h>
#include <math.h>
#include "helpers.h"

/**
 * Returns true if value is in array of n values, else false.
 */
bool search(int value, int values[], int n)
{
    // TODO: implement a searching algorithm
    //return linearSearch(value, values, n);
    return binarySearch(value, values, n);
    
}

bool linearSearch(int value, int values[], int n){
    if(n <= 0){
        return false;
    }
    else {
        for(int i = 0; i< n; i++){
            if(values[i] == value){
                return true;
            }
        }
    }
    return false;    
}

bool binarySearch(int value, int values[], int n){
    int start = 0;
    int end = n-1;
    int mid_point = (start+end)/2;
    
    if (n <= 0){
        return false;
    }
    
    while(start <= end){
        
        if(values[mid_point] == value){
            return true;
        }
        // move to the left of the array
        else if(value < values[mid_point]){
            end = mid_point-1;
        }
        // move to the right of the array
        else if (value > values[mid_point]){
            start = mid_point+1;
        }
        mid_point = (start+end)/2;
    }
    // if reach here, not found
    return false;
}

/**
 * Sorts array of n values.
 */
void sort(int values[], int n)
{
    // TODO: implement an O(n^2) sorting algorithm
    selectionSort(values, n);
    //bubbleSort(values, n);
    //insertionSort(values, n);
    return;
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

// this function swaps the value of array indexed by index1 and index2
void swap(int values[], int index1, int index2){
    int temp = values[index1];
    values[index1] = values[index2];
    values[index2] = temp;
}

// for debugging
void printArray(int values[], int n){
    for (int i = 0; i<n; i++){
        printf("%d ", values[i]);
    }
    printf("\n");
}