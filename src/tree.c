#include "tree.h"
#include "common.h"
#include <stdio.h>

#define INITIAL_SIZE    100
#define COUNT           10

TREE* MyParent = NULL; // For FindNode

int TreeCreate(TREE **Tree)
{
    if (NULL == Tree)
    {
        return -1;
    }

    TREE* DummyTree = (TREE*)malloc(sizeof(TREE));

    if (DummyTree == NULL)
    {
        return -1;
    }

    DummyTree->LChild = NULL;
    DummyTree->RChild = NULL;
    DummyTree->Value = 0;
    DummyTree->IsRoot = 1;

    *Tree = DummyTree;

    return 0;
}

int TreeDestroy(TREE **Tree)
{
    TREE* TempTree = *Tree;

    if (NULL == TempTree)
    {
        return -1;
    }

    TreeClear(TempTree);

    *Tree = NULL;

    return 0;
  
}

int TreeInsert(TREE *Tree, int Value)
{
    TREE* TempNode = (TREE*)malloc(sizeof(TREE));
    if (NULL == TempNode)
    {
        return -1;
    }

    TREE* Current;
    TREE* Parent;

    TempNode->Value = Value;
    TempNode->LChild = NULL;
    TempNode->RChild = NULL;
 
    if (Tree == NULL || Tree->IsRoot == 1)
    {
        Tree->Value = Value;
        Tree->LChild = NULL;
        Tree->RChild = NULL;
        Tree->IsRoot = 0;
        return 0;
    }
    else
    {
        Current = Tree;
        Parent = NULL;
        while (1)
        {
            Parent = Current;

            if (Value <= Parent->Value)
            {
                Current = Current->LChild;
                if (NULL == Current)
                {
                    Parent->LChild = TempNode;
                    return 0;
                }
            }
            else
            {
                Current = Current->RChild;
                if (NULL == Current)
                {
                    Parent->RChild = TempNode;
                    return 0;
                }
            }
        }
    }

    return 0;
}

TREE* findNode(TREE* Tree, int Value)
{
    TREE* CurrentNode = Tree;
    TREE* PreviousNode = Tree;

    while (CurrentNode != NULL)
    {
        if (Value == CurrentNode->Value)
        {
            MyParent = PreviousNode;
            return CurrentNode;
        }

        else if (Value < CurrentNode->Value)
        {
            PreviousNode = CurrentNode;
            CurrentNode = CurrentNode->LChild;
        }
        else
        {
            PreviousNode = CurrentNode;
            CurrentNode = CurrentNode->RChild;
        }
    }

    MyParent = PreviousNode;
    return NULL;
}

int TreeRemove(TREE *Tree, int Value)
{
    TREE* P;
    TREE* Parent;
    TREE* Successor;

    P = findNode(Tree, Value);

    if (NULL == P)
    {
        return 0;
    }

    if (P->LChild == NULL && P->RChild == NULL)
    {
        if (P == Tree)
        {
            Tree->IsRoot = 1;
            return 0;
        }

        Parent = MyParent;

        if (Parent->LChild == P)
        {
            Parent->LChild = NULL;
        }
        else
        {
            Parent->RChild = NULL;
        }
        return 0;
    }

    if (P->LChild == NULL)                
    {
        if (P == Tree)
        {
            Tree = Tree->RChild;
            return 0;
        }

        Parent = MyParent;    

        if (Parent->LChild == P)
            Parent->LChild = Parent->RChild;
        else
            Parent->RChild = P->RChild;

        return 0;
    }

    if (P->RChild == NULL)
    {
        if (P == Tree)
        {
            Tree = Tree->LChild;
            return 0;
        }

        Parent = MyParent;     

       
        if (Parent->LChild == P)
            Parent->LChild = P->LChild;
        else
            Parent->RChild = P->LChild;

        return 0;
    }

    if (P->RChild->LChild == NULL)
    {
       
        P->Value = P->RChild->Value;         
        P->RChild = P->RChild->RChild;
        return 0;                       
    }

    Successor = P->RChild;
    TREE* SuccParent = P;             

    
    while (Successor->LChild != NULL)
    {
        SuccParent = Successor;
        Successor = Successor->LChild;
    }

    P->Value = Successor->Value;
    SuccParent->LChild = Successor->RChild;

    return 0;
}

int TreeContains(TREE *Tree, int Value)
{
    if (NULL == Tree || Tree->IsRoot == 1)
    {
        return 0;
    }

    if (Tree->Value == Value)
    {
        return 1;
    }

    else if (Value <= Tree->Value)
    {
        return TreeContains(Tree->LChild, Value);
    }
    else
    {
        return TreeContains(Tree->RChild, Value);
    }
}

int TreeGetCount(TREE *Tree)
{
    if (NULL == Tree)
    {
        return 0;
    }

    if (Tree->IsRoot == 1)
    {
        return 0;
    }

    else
    {
        return 1 + TreeGetCount(Tree->LChild) + TreeGetCount(Tree->RChild);
    }
}

int TreeGetHeight(TREE *Tree)
{
    if (NULL == Tree)
    {
        return 0;
    }

    if (Tree->IsRoot == 1)
    {
        return 0;
    }

    int lHeight = TreeGetHeight(Tree->LChild);
    int rHeight = TreeGetHeight(Tree->RChild);
   
    if (lHeight > rHeight)
        return (lHeight + 1);
    else
        return (rHeight + 1);

}

int TreeClear(TREE *Tree)
{
    if (Tree == NULL)
    {
        return 1;
    }
    TreeClear(Tree->LChild);
    TreeClear(Tree->RChild);
    free(Tree);
    
    return 0;
}

int TreeGetNthPreorder(TREE *Tree, int Index, int *Value)
{
    static int Count = 0;
    static int MaxCount = 0;

    if (TreeGetCount(Tree) > MaxCount)
    {
        MaxCount = TreeGetCount(Tree);
    }

    if (MaxCount < Index)
    {
        *Value = -1;
        return -1;
    }

    if (Tree == NULL)
    {
        return 0;
    }

    if (Tree->IsRoot == 1)
    {
        *Value = -1;
        return -1;
    }

    if (Count <= Index) 
    {
        Count++;

        // when count = n then print element
        if (Count == Index)
        {
            *Value = Tree->Value;
        }

        /* first recur on left child */
        TreeGetNthPreorder(Tree->LChild, Index, Value);
        

        /* now recur on right child */
        TreeGetNthPreorder(Tree->RChild, Index, Value);
    }

    return 0;
}

int TreeGetNthInorder(TREE *Tree, int Index, int *Value)
{
    static int Count = 0;
    static int MaxCount = 0;

    if (TreeGetCount(Tree) > MaxCount)
    {
        MaxCount = TreeGetCount(Tree);
    }

    if (MaxCount < Index)
    {
        *Value = -1;
        return -1;
    }
   
    if (Tree == NULL)
    {
        return 0;
    }

    if (Tree->IsRoot == 1)
    {
        *Value = -1;
        return -1;
    }

    if (Count <= Index) 
    {
        /* first recur on left child */
        TreeGetNthInorder(Tree->LChild, Index, Value);
        Count++;

        // when count = n then print element
        if (Count == Index)
        {
            *Value = Tree->Value;
        }

        /* now recur on right child */
        TreeGetNthInorder(Tree->RChild, Index, Value);
    }

    return 0;
}

int TreeGetNthPostorder(TREE *Tree, int Index, int *Value)
{
    static int Count = 0;
    static int MaxCount = 0;

    if (TreeGetCount(Tree) > MaxCount)
    {
        MaxCount = TreeGetCount(Tree);
    }

    if (MaxCount < Index)
    {
        *Value = -1;
        return -1;
    }

    if (Tree == NULL)
    {
        return 0;
    }

    if (Tree->IsRoot == 1)
    {
        *Value = -1;
        return -1;
    }

    if (Count <= Index)
    {
        // first recur on left subtree
        TreeGetNthPostorder(Tree->LChild, Index, Value);

        // then recur on right subtree
        TreeGetNthPostorder(Tree->RChild, Index, Value);

        Count++;

        if (Count == Index)
        {
            *Value = Tree->Value;
        }
    }
    return 0;
}

void print2DUtil(TREE* Tree, int space)
{
    // Base case
    if (Tree == NULL)
        return;

    // Increase distance between levels
    space += COUNT;

    // Process right child first
    print2DUtil(Tree->RChild, space);

    // Print current node after space
    // count
    printf("\n");
    for (int i = COUNT; i < space; i++)
        printf(" ");
    printf("%d\n", Tree->Value);

    // Process left child
    print2DUtil(Tree->LChild, space);
}

// Wrapper over print2DUtil()
void print2D(TREE* Tree)
{
    printf("-----------PRINTING TREE------------\n");
    if (Tree->IsRoot == 1)
    {
        return;
    }
    // Pass initial space count as 0
    print2DUtil(Tree, 0);

    printf("\n-----------PRINTING ENDED-----------\n\n");
}

void PrintPostOrder(TREE* Tree)
{
    if (Tree == NULL)
        return;

    if (Tree->IsRoot == 1)
    {
        return;
    }

    // first recur on left subtree
    PrintPostOrder(Tree->LChild);

    // then recur on right subtree
    PrintPostOrder(Tree->RChild);

    // now deal with the node
    printf("%d ", Tree->Value);
}

void PrintInOrder(TREE* Tree)
{

    if (Tree == NULL)
        return;

    if (Tree->IsRoot == 1)
    {
        return;
    }

    // first recur on left subtree
    PrintInOrder(Tree->LChild);

    // now deal with the node
    printf("%d ", Tree->Value);

    // then recur on right subtree
    PrintInOrder(Tree->RChild);
}

void PrintPreOrder(TREE* Tree)
{
    if (Tree == NULL)
        return;

    if (Tree->IsRoot == 1)
    {
        return;
    }

    /* first print data of node */
    printf("%d ", Tree->Value);

    /* then recur on left subtree */
    PrintPreOrder(Tree->LChild);

    /* now recur on right subtree */
    PrintPreOrder(Tree->RChild);
}
