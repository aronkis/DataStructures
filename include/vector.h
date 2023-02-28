#ifndef _DATA_STRUCTURES_VECTOR_H_
#define _DATA_STRUCTURES_VECTOR_H_

typedef struct VECTOR {
    int *Array;
    int Size;
    int Count;
} VECTOR;

int VecCreate(VECTOR **Vector);
int VecDestroy(VECTOR **Vector);

int VecInsertTail(VECTOR *Vector, int Value);
int VecInsertHead(VECTOR *Vector, int Value);
int VecInsertAfterIndex(VECTOR *Vector, int Index, int Value);
int VecRemoveByIndex(VECTOR *Vector, int Index);
int VecGetValueByIndex(VECTOR *Vector, int Index, int *Value);

// Returns the number of element in Vector or -1 in case of error or invalid parameters
int VecGetCount(VECTOR *Vector);
int VecClear(VECTOR *Vector);

// Sort the vector in decreasing order
int VecSort(VECTOR *Vector);

// Appends all the elements in DestVector to SrcVector
int VecAppend(VECTOR *DestVector, VECTOR *SrcVector);

void PrintVector(VECTOR* Vector);

#endif
