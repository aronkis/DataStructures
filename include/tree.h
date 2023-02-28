#ifndef _DATA_STRUCTURES_TREE_H_
#define _DATA_STRUCTURES_TREE_H_

typedef struct TREE {
    // Members
    int Value;
    int IsRoot;
    struct TREE* LChild;
    struct TREE* RChild;
} TREE;

int TreeCreate(TREE **Tree);
int TreeDestroy(TREE **Tree);

// Duplicates are allowed
int TreeInsert(TREE *Tree, int Value);

// Removes all elements equal to Value
int TreeRemove(TREE *Tree, int Value);


//  Returns:
//       1  - Tree contains Value
//       0  - Tree does not contain Value
//      -1  - Error or invalid parameter
int TreeContains(TREE *Tree, int Value);

// Returns the number of elements in Tree or -1 in case of error or invalid parameter
int TreeGetCount(TREE *Tree);

// Returns the height of Tree or -1 in case of error or invalid parameter
int TreeGetHeight(TREE *Tree);

// Removes every element of the tree
int TreeClear(TREE *Tree);

int TreeGetNthPreorder(TREE *Tree, int Index, int *Value);
int TreeGetNthInorder(TREE *Tree, int Index, int *Value);
int TreeGetNthPostorder(TREE *Tree, int Index, int *Value);

void print2D(TREE* Tree);
void PrintPostOrder(TREE* Tree);
void PrintInOrder(TREE* Tree);
void PrintPreOrder(TREE* Tree);

#endif