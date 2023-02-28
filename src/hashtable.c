#include "hashtable.h"
#include "common.h"
#include <string.h>

int HtCreate(HASH_TABLE **HashTable)
{
    return -1;
}

int HtDestroy(HASH_TABLE **HashTable)
{
    return -1;
}

int HtSetKeyValue(HASH_TABLE *HashTable, char *Key, int Value)
{
    return -1;
}

int HtGetKeyValue(HASH_TABLE *HashTable, char *Key, int *Value)
{
    return -1;
}

int HtRemoveKey(HASH_TABLE *HashTable, char *Key)
{
    return -1;
}

int HtHasKey(HASH_TABLE *HashTable, char *Key)
{
    return -1;
}

int HtGetFirstKey(HASH_TABLE* HashTable, HASH_TABLE_ITERATOR **Iterator, char **Key)
{
    HASH_TABLE_ITERATOR *iterator = NULL;


    if (NULL == HashTable)
    {
        return -1;
    }
    if (NULL == Iterator)
    {
        return -1;
    }
    if (NULL == Key)
    {
        return -1;
    }

    iterator = (HASH_TABLE_ITERATOR*)malloc(sizeof(HASH_TABLE_ITERATOR));
    if (NULL == iterator)
    {
        return -1;
    }

    memset(iterator, 0, sizeof(*iterator));

    iterator->HashTable = HashTable;
    // INITIALIZE THE REST OF THE FIELDS OF iterator

    *Iterator = iterator;

    // FIND THE FIRST KEY AND SET Key

    return 0;
}

int HtGetNextKey(HASH_TABLE_ITERATOR *Iterator, char **Key)
{
    return -1;
}

int HtReleaseIterator(HASH_TABLE_ITERATOR **Iterator)
{
    return -1;
}

int HtClear(HASH_TABLE *HashTable)
{
    return -1;
}

int HtGetKeyCount(HASH_TABLE *HashTable)
{
    return -1;
}
