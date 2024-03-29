#include "heap.h"
#include "common.h"
#include <stdio.h>
#include <string.h>

#define INITIAL_SIZE    100

int swap(HEAP* Heap, int i, int j)
{
    if (NULL == Heap || i > Heap->Count || i < 0 || j > Heap->Count || j < 0)
    {
        return -1;
    }

    int temp = Heap->Array[i];
    Heap->Array[i] = Heap->Array[j];
    Heap->Array[j] = temp;

    return 0;
}

int MinHeapMaker(HEAP* Heap, int k)
{
    if (NULL == Heap || k > Heap->Count || k < 0)
    {
        return -1;
    }

    int j;
    while (2 * k <= Heap->Count)
    {
        j = 2 * k;
        if (j < Heap->Count && Heap->Array[j + 1] < Heap->Array[j])
        {
            j++;
        }
        if (Heap->Array[k] <= Heap->Array[j])
        {
            return 0;
        }
        swap(Heap, k, j);
        k = j;
    }

    return 0;
}

int MaxHeapMaker(HEAP* Heap, int k)
{
    if (NULL == Heap || k > Heap->Count || k < 0)
    {
        return -1;
    }

    int j;
    while (2 * k <= Heap->Count)
    {
        j = 2 * k;
        if (j < Heap->Count && Heap->Array[j + 1] > Heap->Array[j])
        {
            j++;
        }
        if (Heap->Array[k] >= Heap->Array[j])
        {
            return 0;
        }
        swap(Heap, k, j);
        k = j;
    }

    return 0;
}

int IsMinHeap(HEAP* heap, int i)
{
    int l = 2 * (i + 1) + 1;
    if (l < heap->Count) {
        if ((heap->Array[l] < heap->Array[i + 1]) || !IsMinHeap(heap, l)) {
            return 0;
        }
    }
    int r = 2 * (i + 1) + 2;
    if (r < heap->Count) {
        if ((heap->Array[r] < heap->Array[i + 1]) || !IsMinHeap(heap, r)) {
            return 0;
        }
    }
    return 1;
}

int IsMaxHeap(HEAP* heap, int i)
{
    int l = 2 * (i + 1) + 1;
    if (l < heap->Count) {
        if ((heap->Array[l] > heap->Array[i + 1]) || !IsMaxHeap(heap, l)) {
            return 0;
        }
    }
    int r = 2 * (i + 1) + 2;
    if (r < heap->Count) {
        if ((heap->Array[r] > heap->Array[i + 1]) || !IsMaxHeap(heap, r)) {
            return 0;
        }
    }
    return 2;
} 

int MinHeapFix(HEAP* Heap)
{
    if (NULL == Heap)
    {
        return -1;
    }

    int i = Heap->Count;
    while (i > 1 && Heap->Array[i] < Heap->Array[i / 2])
    {
        swap(Heap, i / 2, i);
        i /= 2;
    }

    return 0;
}

int MaxHeapFix(HEAP* Heap)
{
    if (NULL == Heap)
    {
        return -1;
    }

    int i = Heap->Count;

    while (i > 1 && Heap->Array[i] > Heap->Array[i / 2])
    {
        swap(Heap, i / 2, i);
        i /= 2;
    }

    return 0;
}

int HeapSearch(HEAP* Heap, int Value)
{
    if (NULL == Heap)
    {
        return -1;
    }

    for (int i = 1; i <= Heap->Count; i++)
    {
        if (Heap->Array[i] == Value)
        {
            return i;
        }
    }
    return 0;
}

int HpCreateMaxHeap(HEAP **MaxHeap, VECTOR* InitialElements)
{
    HEAP* mHeap = NULL;

    if (NULL == MaxHeap)
    {
        return -1;
    }

    mHeap = (HEAP*)malloc(sizeof(HEAP));

    if (NULL == mHeap)
    {
        return -1;
    }

    if (InitialElements != NULL)
    {
        mHeap->Size = INITIAL_SIZE;
        mHeap->Count = 0;
        mHeap->Type = 1;
        mHeap->Array = (int*)malloc(sizeof(int) * (INITIAL_SIZE + 1));

        if (NULL == mHeap->Array)
        {
            free(mHeap);
            return -1;
        }

        mHeap->Count = InitialElements->Count;

        for (int i = 0; i < InitialElements->Count; i++)
        {
            mHeap->Array[i + 1] = InitialElements->Array[i];
        }

        for (int k = (mHeap->Count + 1) / 2; k > 0; k--)
        {
            MaxHeapMaker(mHeap, k);
        }

        *MaxHeap = mHeap;
    }
    else
    {
        mHeap->Array = (int*)malloc(sizeof(int) * INITIAL_SIZE + 1);

        if (NULL == mHeap->Array)
        {
            free(mHeap);
            return -1;
        }

        mHeap->Size = INITIAL_SIZE;
        mHeap->Count = 0;
        mHeap->Type = 1;

        *MaxHeap = mHeap;
    }

    return 0;
}

int HpCreateMinHeap(HEAP **MinHeap, VECTOR* InitialElements)
{
   HEAP* mHeap = NULL;

    if (NULL == MinHeap)
    {
        return -1;
    }

    mHeap = (HEAP*)malloc(sizeof(HEAP));

    if (NULL == mHeap)
    {
        return -1;
    }


    if (InitialElements != NULL)
    {
        mHeap->Size = INITIAL_SIZE;
        mHeap->Count = 0;
        mHeap->Array = (int*)malloc(sizeof(int) * (INITIAL_SIZE + 1));
        mHeap->Type = 0;

        if (NULL == mHeap->Array)
        {
            free(mHeap);
            return -1;
        }

        mHeap->Count = InitialElements->Count;

        for (int i = 0; i < InitialElements->Count; i++)
        {
            mHeap->Array[i + 1] = InitialElements->Array[i];
        }

        for (int k = (mHeap->Count + 1) / 2; k > 0; k--)
        {
            MinHeapMaker(mHeap, k);
        }

        *MinHeap = mHeap;
    }
    else
    {
        mHeap->Array = (int*)malloc(sizeof(int) * INITIAL_SIZE + 1);

        if (NULL == mHeap->Array)
        {
            free(mHeap);
            return -1;
        }

        mHeap->Size = INITIAL_SIZE;
        mHeap->Count = 0;
        mHeap->Type = 0;

        *MinHeap = mHeap;
    }

    return 0;
}

int HpDestroy(HEAP **Heap)
{
    HEAP* heap = *Heap;

    if (NULL == Heap)
    {
        return -1;
    }

    free(heap->Array);
    free(heap);

    *Heap = NULL;
    
    return 0;
}

int HpInsert(HEAP *Heap, int Value)
{

    if (NULL == Heap || Heap->Count >= Heap->Size)
    {
        return -1;
    }
    
    Heap->Count++;
    Heap->Array[Heap->Count] = Value;    
    
    if (Heap->Type == 0)
    {
         MinHeapFix(Heap);
    }
    else if (Heap->Type == 1)
    {
        MaxHeapFix(Heap);
    }

    return 0;
}

int HpRemove(HEAP *Heap, int Value)
{

    if (NULL == Heap || Heap->Count == 0)
    {
        return -1;
    }

    if (Heap->Count == 1)
    {
        Heap->Count--;
        return 0;
    }

    int Pos = HeapSearch(Heap, Value);

    while (Pos)
    {
        Heap->Array[Pos] = Heap->Array[Heap->Count];
        Heap->Count--;

        if (Heap->Type == 0)
        {
            if (Pos == 1 || Heap->Array[Pos / 2] < Heap->Array[Pos])
            {
                MinHeapMaker(Heap, Pos);
            }
            else
            {
                MinHeapFix(Heap);
            }
        }
        else if (Heap->Type == 1)
        {
            if (Pos == 1 || Heap->Array[Pos / 2] > Heap->Array[Pos])
            {
                MaxHeapMaker(Heap, Pos);
            }
            else
            {
                MaxHeapFix(Heap);
            }
        }
        Pos = HeapSearch(Heap, Value);
    }
    return 0;
}

int HpGetExtreme(HEAP *Heap, int* ExtremeValue)
{
    if (NULL == Heap)
    {
        return -1;
    }

    *ExtremeValue = Heap->Array[1];
   
    return 0;
}

int HpPopExtreme(HEAP *Heap, int* ExtremeValue)
{
    if (NULL == Heap)
    {
        return -1;
    }
    
    *ExtremeValue = Heap->Array[1];

    int retVal = 0;
    retVal = HpRemove(Heap, Heap->Array[1]);

    return retVal;
}

int HpGetElementCount(HEAP *Heap)
{
    if (NULL == Heap)
    {
        return -1;
    }

    return Heap->Count;
}

int HpSortToVector(HEAP *Heap, VECTOR* SortedVector)
{
                                                // Heap->Array[0] unused. 
    if (NULL == Heap || NULL == SortedVector || Heap->Count > SortedVector->Size)
    {
        return -1;
    }

    if (SortedVector->Count > 0)
    {
        // If the vector is not empty, the user
        // might not want to overwrite those elements.
        return -1;
    }

    if (Heap->Type == 0)
    {
        while (Heap->Count)
        {
            VecInsertTail(SortedVector, Heap->Array[1]);
            HpRemove(Heap, Heap->Array[1]);
        }
    }
    else
    {
        while (Heap->Count)
        {
            VecInsertHead(SortedVector, Heap->Array[1]);
            HpRemove(Heap, Heap->Array[1]);
        }
    }

    return 0;
}

int printHeap(HEAP* Heap)
{
    if (NULL == Heap)
    {
        return -1;
    }

    printf("Heap = ");
    for (int i = 1; i <= Heap->Count; i++)
    {
        printf("%d ", Heap->Array[i]);
    }
    return 0;
}