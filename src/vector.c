#include "vector.h"
#include "common.h"
#include "string.h"
#include <stdio.h>

#define INITIAL_SIZE    100

int VecCreate(VECTOR **Vector)
{
    VECTOR *vec = NULL;

    if (NULL == Vector)
    {
        return -1;
    }

    vec = (VECTOR*)malloc(sizeof(VECTOR));
    if (NULL == vec)
    {
        return -1;
    }

    memset(vec, 0, sizeof(*vec));

    vec->Count = 0;
    vec->Size = INITIAL_SIZE;
    vec->Array = (int*)malloc( sizeof(int) * INITIAL_SIZE );
    if (NULL == vec->Array) 
    {
        free(vec);
        return -1;
    }

    *Vector = vec;

    return 0;
}

int VecDestroy(VECTOR **Vector)
{
    VECTOR *vec = *Vector;

    if (NULL == Vector)
    {
        return -1;
    }

    free(vec->Array);
    free(vec);

    *Vector = NULL;
    return 0;
}

int VecInsertTail(VECTOR *Vector, int Value)
{
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

int VecInsertHead(VECTOR *Vector, int Value)
{
    if (NULL == Vector)
    {
        return -1;
    }

    if (Vector->Count >= Vector->Size)
    {
        /// REALLOC
        return -1;
    }

    for (int i = Vector->Count-1; i >= 0; i--)
    {
        Vector->Array[i + 1] = Vector->Array[i];
    }
    Vector->Array[0] = Value;
    Vector->Count++;

    return 0;
}

int VecInsertAfterIndex(VECTOR *Vector, int Index, int Value)
{
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

int VecRemoveByIndex(VECTOR *Vector, int Index)
{
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
    // -1
    return 0;
}

int VecGetValueByIndex(VECTOR *Vector, int Index, int *Value)
{
    if (NULL == Vector)
    {
        return -1;
    }

    if (Vector->Count < Index || Index < 0)
    {
        return -1;
    }

    *Value = Vector->Array[Index];
    // -1
    return 0;
}

int VecGetCount(VECTOR *Vector)
{
    if (NULL == Vector)
    {
        return -1;
    }

    return Vector->Count;
}

int VecClear(VECTOR *Vector)
{
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

int VecSort(VECTOR *Vector)
{
    if (NULL == Vector)
    {
        return -1;
    }

    for (int i = 0; i < Vector->Count - 1; i++)
    {
        for (int j = i + 1; j < Vector->Count; j++)
        {
            if (Vector->Array[i] < Vector->Array[j])
            {
                int temp = Vector->Array[i];
                Vector->Array[i] = Vector->Array[j];
                Vector->Array[j] = temp;
            }
        }
    }
    return 0;
}

int VecAppend(VECTOR *DestVector, VECTOR *SrcVector)
{
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

void PrintVector(VECTOR* Vector)
{
    printf("\nSorted Vector = ");
    for (int i = 0; i < Vector->Count; i++)
    {
        printf("%d ", Vector->Array[i]);
    }
    printf("\n");
}
