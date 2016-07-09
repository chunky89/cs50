/**
 * helpers.h
 *
 * Computer Science 50
 * Problem Set 3
 *
 * Helper functions for Problem Set 3.
 */
 
#include <cs50.h>

/**
 * Returns true if value is in array of n values, else false.
 */
bool search(int value, int values[], int n);

bool linearSearch(int value, int values[], int n);
// iterative version of binary search
bool binarySearch(int value, int values[], int n);
// recursive version of binary search
bool binarySearchRecur(int value, int values[], int n, int start, int end);


/**
 * Sorts array of n values.
 */
void sort(int values[], int n);

void selectionSort(int values[], int n);
void bubbleSort(int values[], int n);
void insertionSort(int values[], int n);
void countingSort(int values[], int n);
// this function swaps the value of array indexed by index1 and index2
void swap(int values[], int index1, int index2);
// for debugging
void printArray(int values[], int n);