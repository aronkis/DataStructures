#ifndef _DATA_STRUCTURES_HASHTABLE_H_
#define _DATA_STRUCTURES_HASHTABLE_H_

typedef struct HASH_TABLE {
    // Members
    int PlaceHolder; // placeholder to be removed when actual implementation is added
} HASH_TABLE;

typedef struct HASH_TABLE_ITERATOR
{
    HASH_TABLE *HashTable; // set by call to HtGetFirstKey
    // Other Member
} HASH_TABLE_ITERATOR;

int HtCreate(HASH_TABLE **HashTable);
int HtDestroy(HASH_TABLE **HashTable);

// Returns -1 if Key already exist in HashTable or the parameters are invalid
int HtSetKeyValue(HASH_TABLE *HashTable, char *Key, int Value);

// Returns -1 if Key does not exist in HashTable or the parameters are invalid
int HtGetKeyValue(HASH_TABLE *HashTable, char *Key, int *Value);

// Returns -1 if Key does not exist in HashTable or the parameters are invalid
int HtRemoveKey(HASH_TABLE *HashTable, char *Key);

//  Returns:
//       1  - HashTable contains Key
//       0  - HashTable does not contain Key
//      -1  - Error or invalid parameter
int HtHasKey(HASH_TABLE *HashTable, char *Key);

// Initializes the iterator and gets the first key in the hash table
// Returns:
//       -1 - Error or invalid parameter
//       -2 - No keys in the hash table
//      >=0 - Success
int HtGetFirstKey(HASH_TABLE *HashTable, HASH_TABLE_ITERATOR **Iterator, char **Key);

// Returns the next key in the hash table contained in the iterator
// Iterator saves the state of the iteration
// Returns:
//       -1 - Error or invalid parameter
//       -2 - No more keys in the hash table
//      >=0 - Success
int HtGetNextKey(HASH_TABLE_ITERATOR *Iterator, char **Key);

int HtReleaseIterator(HASH_TABLE_ITERATOR **Iterator);

// Removes every element in the hash table
int HtClear(HASH_TABLE *HashTable);

// Returns the number of keys in the HashTable, or -1 in case of error
int HtGetKeyCount(HASH_TABLE *HashTable);

#endif