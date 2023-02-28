#ifndef _DATA_STRUCTURES_HEAP_H_
#define _DATA_STRUCTURES_HEAP_H_

#include "vector.h"

typedef struct HEAP{
    // Members
    int* Array; // elements
    int Count; // Current number of elements
    int Size; // Max size
    int Type; // 0 - MinHeap; 1 - MaxHeap  
} HEAP;

// HpCreateMaxHeap and HpCreateMinHeap should create a max heap or a min heap,
// respectively. InitialElements is an optional parameter and, if it is not null, the constructed
// heap should initially contain all the elements in the provided vector.
int HpCreateMaxHeap(HEAP **MaxHeap, VECTOR* InitialElements);
int HpCreateMinHeap(HEAP **MinHeap, VECTOR* InitialElements);
int HpDestroy(HEAP **Heap);

int HpInsert(HEAP *Heap, int Value);

// HpRemove should remove all elements with the value Value in the heap
int HpRemove(HEAP *Heap, int Value);

// HpGetExtreme should return the maximum/minimum value in the heap, depending on the
// type of heap constructed
int HpGetExtreme(HEAP *Heap, int* ExtremeValue);

// HpPopExtreme should return the maximum/minimum value in the heap, and remove all
// instances of said value from the heap
int HpPopExtreme(HEAP *Heap, int* ExtremeValue);

// Returns the number of elements in Heap or -1 in case of error or invalid parameter
int HpGetElementCount(HEAP *Heap);

// HpSortToVector should construct and return (in the SortedVector parameter) a vector
// sorted in increasing order containing all the elements present in the heap
int HpSortToVector(HEAP *Heap, VECTOR* SortedVector);

int printHeap(HEAP* Heap);

//int IsMinHeap(HEAP* Heap, int i);
//int IsMaxHeap(HEAP* Heap, int i);

#endif