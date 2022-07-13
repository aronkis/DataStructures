#include "ccvector.h"
#include "common.h"
#include "string.h"
#include <stdio.h>

#define INITIAL_SIZE    100

int VecCreate(CC_VECTOR** Vector)
{
    CC_VECTOR* vec = NULL;

    CC_UNREFERENCED_PARAMETER(Vector);

    if (NULL == Vector)
    {
        return -1;
    }

    vec = (CC_VECTOR*)malloc(sizeof(CC_VECTOR));
    if (NULL == vec)
    {
        return -1;
    }

    memset(vec, 0, sizeof(*vec));

    vec->Count = 0;
    vec->Size = INITIAL_SIZE;
    vec->Array = (int*)malloc(sizeof(int) * INITIAL_SIZE);
    if (NULL == vec->Array)
    {
        free(vec);
        return -1;
    }

    *Vector = vec;

    return 0;
}

int VecDestroy(CC_VECTOR** Vector)
{
    CC_VECTOR* vec = *Vector;

    if (NULL == Vector)
    {
        return -1;
    }

    free(vec->Array);
    free(vec);

    *Vector = NULL;

    return 0;
}

int VecInsertTail(CC_VECTOR* Vector, int Value)
{
    CC_UNREFERENCED_PARAMETER(Vector);
    CC_UNREFERENCED_PARAMETER(Value);

    if (NULL == Vector)
    {
        return -1;
    }

    if (Vector->Count >= Vector->Size)
    {
        /// REALLOC
        return -1;
    }

    Vector->Array[Vector->Count] = Value;
    Vector->Count++;

    return 0;
}

int VecInsertHead(CC_VECTOR* Vector, int Value)
{
    CC_UNREFERENCED_PARAMETER(Vector);
    CC_UNREFERENCED_PARAMETER(Value);

    if (NULL == Vector)
    {
        return -1;
    }

    if (Vector->Count >= Vector->Size)
    {
        /// REALLOC
        return -1;
    }

    for (int i = Vector->Count - 1; i >= 0; i--)
    {
        Vector->Array[i + 1] = Vector->Array[i];
    }

    Vector->Array[0] = Value;
    Vector->Count++;

    return 0;
}

int VecInsertAfterIndex(CC_VECTOR* Vector, int Index, int Value)
{
    CC_UNREFERENCED_PARAMETER(Vector);
    CC_UNREFERENCED_PARAMETER(Index);
    CC_UNREFERENCED_PARAMETER(Value);

    if (NULL == Vector)
    {
        return -1;
    }

    if (Vector->Count >= Vector->Size)
    {
        /// REALLOC
        return -1;
    }

    for (int i = Vector->Count - 1; i >= Index; i--)
    {
        Vector->Array[i + 1] = Vector->Array[i];
    }

    Vector->Array[Index] = Value;
    Vector->Count++;

    return 0;
}

int VecRemoveByIndex(CC_VECTOR* Vector, int Index)
{
    CC_UNREFERENCED_PARAMETER(Vector);
    CC_UNREFERENCED_PARAMETER(Index);

    if (NULL == Vector)
    {
        return -1;
    }

    if (Vector->Count < Index || Index < 0)
    {
        return -1;
    }

    for (int i = Index; i <= Vector->Count - 1; i++)
    {
        Vector->Array[i] = Vector->Array[i + 1];
    }

    Vector->Count--;

    return 0;
}

int VecGetValueByIndex(CC_VECTOR* Vector, int Index, int* Value)
{
    CC_UNREFERENCED_PARAMETER(Vector);
    CC_UNREFERENCED_PARAMETER(Index);
    CC_UNREFERENCED_PARAMETER(Value);

    if (NULL == Vector)
    {
        return -1;
    }

    if (Vector->Count < Index || Index < 0)
    {
        return -1;
    }

    *Value = Vector->Array[Index];

    return 0;
}

int VecGetCount(CC_VECTOR* Vector)
{
    CC_UNREFERENCED_PARAMETER(Vector);

    if (NULL == Vector)
    {
        return -1;
    }

    return Vector->Count;
}

int VecClear(CC_VECTOR* Vector)
{
    CC_UNREFERENCED_PARAMETER(Vector);

    if (NULL == Vector)
    {
        return -1;
    }

    while (Vector->Count)
    {
        VecRemoveByIndex(Vector, 0);
    }

    return 0;
}

void Swap(int* a, int* b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

int Partition(CC_VECTOR* Vector, int Left, int Right)
{
    if (NULL == Vector || Left < 0 || Right > Vector->Count)
    {
        return -1;
    }

    int pivot = Vector->Array[Right];
    int pos = Left - 1;

    for (int i = Left; i < Right; i++)
    {
        if (Vector->Array[i] > pivot)
        {
            pos++;
            Swap(&Vector->Array[pos], &Vector->Array[i]);
        }
    }

    Swap(&Vector->Array[pos + 1], &Vector->Array[Right]);

    return ++pos;
}

int QuickSort(CC_VECTOR* Vector, int Left, int Right)
{
    if (NULL == Vector || Left < 0 || Right > Vector->Count)
    {
        return -1;
    }

    if (Left < Right)
    {
        int currentPos = Partition(Vector, Left, Right);
        QuickSort(Vector, Left, currentPos - 1);
        QuickSort(Vector, currentPos + 1, Right);
    }

    return 0;
}

int VecSort(CC_VECTOR* Vector)
{
    CC_UNREFERENCED_PARAMETER(Vector);

    if (NULL == Vector)
    {
        return -1;
    }

    int retVal = -1;
    retVal = QuickSort(Vector, 0, Vector->Count - 1);

    if (retVal == 0)
    {
        return 0;
    }
    else
    {
        return -1;
    }
}

int VecAppend(CC_VECTOR* DestVector, CC_VECTOR* SrcVector)
{
    CC_UNREFERENCED_PARAMETER(DestVector);
    CC_UNREFERENCED_PARAMETER(SrcVector);

    if (NULL == DestVector || NULL == SrcVector)
    {
        return -1;
    }

    if (SrcVector->Count + DestVector->Count + 1 >= SrcVector->Size)
    {
        return -1;
    }

    // If we want to append the SrcVector to the SrcVector
    // then we have to keep the original size of the SrcVector
    int numberOfElements = DestVector->Count;

    for (int i = 0; i < numberOfElements; i++)
    {
        SrcVector->Array[SrcVector->Count] = DestVector->Array[i];
        SrcVector->Count++;
    }

    return 0;
}

void PrintVector(CC_VECTOR* Vector)
{
    printf("The Vector is = ");
    for (int i = 0; i < Vector->Count; i++)
    {
        printf("%d ", Vector->Array[i]);
    }
    printf("\n");
}
