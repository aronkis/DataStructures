#include "cctree.h"
#include "common.h"
#include <stdio.h>

#define COUNT    10

CC_TREE* gMyParent = NULL; // For FindNode

int TreeCreate(CC_TREE** Tree)
{
    CC_UNREFERENCED_PARAMETER(Tree);

    if (NULL == Tree)
    {
        return -1;
    }

    CC_TREE* dummyTree = (CC_TREE*)malloc(sizeof(CC_TREE));

    if (dummyTree == NULL)
    {
        return -1;
    }

    dummyTree->LChild = NULL;
    dummyTree->RChild = NULL;
    dummyTree->Value = 0;
    dummyTree->IsRoot = 1;

    *Tree = dummyTree;

    return 0;
}

int TreeDestroy(CC_TREE** Tree)
{
    CC_TREE* dummyTree = *Tree;

    CC_UNREFERENCED_PARAMETER(Tree);

    if (NULL == dummyTree)
    {
        return -1;
    }

    TreeClear(dummyTree);

    *Tree = NULL;

    return 0;
}

int TreeInsert(CC_TREE* Tree, int Value)
{
    CC_UNREFERENCED_PARAMETER(Tree);
    CC_UNREFERENCED_PARAMETER(Value);

    CC_TREE* dummyNode = (CC_TREE*)malloc(sizeof(CC_TREE));

    if (NULL == dummyNode)
    {
        return -1;
    }

    CC_TREE* current;
    CC_TREE* parent;

    dummyNode->Value = Value;
    dummyNode->LChild = NULL;
    dummyNode->RChild = NULL;

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
        current = Tree;
        parent = NULL;

        while (1)
        {
            parent = current;

            if (Value <= parent->Value)
            {
                current = current->LChild;

                if (NULL == current)
                {
                    parent->LChild = dummyNode;
                    return 0;
                }
            }
            else
            {
                current = current->RChild;

                if (NULL == current)
                {
                    parent->RChild = dummyNode;
                    return 0;
                }
            }
        }
    }

    return 0;
}

CC_TREE* FindNode(CC_TREE* Tree, int Value)
{
    CC_TREE* currentNode = Tree;
    CC_TREE* previousNode = Tree;

    while (currentNode != NULL)
    {
        if (Value == currentNode->Value)
        {
            gMyParent = previousNode;
            return currentNode;
        }
        else if (Value < currentNode->Value)
        {
            previousNode = currentNode;
            currentNode = currentNode->LChild;
        }
        else
        {
            previousNode = currentNode;
            currentNode = currentNode->RChild;
        }
    }

    gMyParent = previousNode;

    return NULL;
}

int TreeRemove(CC_TREE* Tree, int Value)
{
    CC_UNREFERENCED_PARAMETER(Tree);
    CC_UNREFERENCED_PARAMETER(Value);

    if (NULL == Tree)
    {
        return -1;
    }

    CC_TREE* p;
    CC_TREE* parent;
    CC_TREE* successor;

    p = FindNode(Tree, Value);

    if (NULL == p)
    {
        return 0;
    }

    if (p->LChild == NULL && p->RChild == NULL)
    {
        if (p == Tree)
        {
            Tree->IsRoot = 1;
            return 0;
        }

        parent = gMyParent;

        if (parent->LChild == p)
        {
            parent->LChild = NULL;
        }
        else
        {
            parent->RChild = NULL;
        }
        return 0;
    }

    if (p->LChild == NULL)
    {
        if (p == Tree)
        {
            Tree = Tree->RChild;
            return 0;
        }

        parent = gMyParent;

        if (parent->LChild == p)
        {
            parent->LChild = parent->RChild;
        }

        else
        {
            parent->RChild = p->RChild;
        }

        return 0;
    }

    if (p->RChild == NULL)
    {
        if (p == Tree)
        {
            Tree = Tree->LChild;
            return 0;
        }

        parent = gMyParent;

        if (parent->LChild == p)
        {
            parent->LChild = p->LChild;
        }
        else
        {
            parent->RChild = p->LChild;
        }

        return 0;
    }

    if (p->RChild->LChild == NULL)
    {

        p->Value = p->RChild->Value;
        p->RChild = p->RChild->RChild;
        return 0;
    }

    successor = p->RChild;
    CC_TREE* SuccParent = p;

    while (successor->LChild != NULL)
    {
        SuccParent = successor;
        successor = successor->LChild;
    }

    p->Value = successor->Value;
    SuccParent->LChild = successor->RChild;

    return 0;
}

int TreeContains(CC_TREE* Tree, int Value)
{
    CC_UNREFERENCED_PARAMETER(Tree);
    CC_UNREFERENCED_PARAMETER(Value);

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

int TreeGetCount(CC_TREE* Tree)
{
    CC_UNREFERENCED_PARAMETER(Tree);

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

int TreeGetHeight(CC_TREE* Tree)
{
    CC_UNREFERENCED_PARAMETER(Tree);

    if (NULL == Tree)
    {
        return 0;
    }

    if (Tree->IsRoot == 1)
    {
        return 0;
    }

    int leftHeight = TreeGetHeight(Tree->LChild);
    int rightHeight = TreeGetHeight(Tree->RChild);

    if (leftHeight > rightHeight)
    {
        return (leftHeight + 1);
    }
    else
    {
        return (rightHeight + 1);
    }
}

int TreeClear(CC_TREE* Tree)
{
    CC_UNREFERENCED_PARAMETER(Tree);

    if (Tree == NULL)
    {
        return 1;
    }

    TreeClear(Tree->LChild);
    TreeClear(Tree->RChild);
    free(Tree);

    return 0;
}

int TreeGetNthPreorder(CC_TREE* Tree, int Index, int* Value)
{
    CC_UNREFERENCED_PARAMETER(Tree);
    CC_UNREFERENCED_PARAMETER(Index);
    CC_UNREFERENCED_PARAMETER(Value);

    static int count = -1;
    static int maxCount = 0;

    if (TreeGetCount(Tree) > maxCount)
    {
        maxCount = TreeGetCount(Tree);
    }

    if (Tree == NULL)
    {
        return 0;
    }

    if (maxCount < Index || Tree->IsRoot == 1)
    {
        *Value = -1;
        return -1;
    }

    if (count <= Index)
    {
        count++;

        if (count == Index)
        {
            *Value = Tree->Value;
        }

        // first recur on left child 
        TreeGetNthPreorder(Tree->LChild, Index, Value);

        /* now recur on right child */
        TreeGetNthPreorder(Tree->RChild, Index, Value);
    }

    return 0;
}

int TreeGetNthInorder(CC_TREE* Tree, int Index, int* Value)
{
    CC_UNREFERENCED_PARAMETER(Tree);
    CC_UNREFERENCED_PARAMETER(Index);
    CC_UNREFERENCED_PARAMETER(Value);

    static int count = -1;
    static int maxCount = 0;

    if (TreeGetCount(Tree) > maxCount)
    {
        maxCount = TreeGetCount(Tree);
    }

    if (Tree == NULL)
    {
        return 0;
    }

    if (maxCount < Index || Tree->IsRoot == 1)
    {
        *Value = -1;
        return -1;
    }

    if (count <= Index)
    {
        /* first recur on left child */
        TreeGetNthInorder(Tree->LChild, Index, Value);

        count++;

        if (count == Index)
        {
            *Value = Tree->Value;
        }

        /* now recur on right child */
        TreeGetNthInorder(Tree->RChild, Index, Value);
    }

    return 0;
}

int TreeGetNthPostorder(CC_TREE* Tree, int Index, int* Value)
{
    CC_UNREFERENCED_PARAMETER(Tree);
    CC_UNREFERENCED_PARAMETER(Index);
    CC_UNREFERENCED_PARAMETER(Value);

    static int count = -1;
    static int maxCount = 0;

    if (TreeGetCount(Tree) > maxCount)
    {
        maxCount = TreeGetCount(Tree);
    }

    if (Tree == NULL)
    {
        return 0;
    }

    if (maxCount < Index || Tree->IsRoot == 1)
    {
        *Value = -1;
        return -1;
    }

    if (count <= Index)
    {
        // first recur on left subtree
        TreeGetNthPostorder(Tree->LChild, Index, Value);

        // then recur on right subtree
        TreeGetNthPostorder(Tree->RChild, Index, Value);

        count++;

        if (count == Index)
        {
            *Value = Tree->Value;
        }
    }

    return 0;
}

void Print2DUtil(CC_TREE* Tree, int space)
{
    // Base case
    if (Tree == NULL)
    {
        return;
    }

    // Increase distance between levels
    space += COUNT;

    // Process right child first
    Print2DUtil(Tree->RChild, space);

    // Print current node after space
    printf("\n");
    for (int i = COUNT; i < space; i++)
    {
        printf(" ");
    }

    printf("%d\n", Tree->Value);

    // Process left child
    Print2DUtil(Tree->LChild, space);
}

// Wrapper over print2DUtil()
void Print2D(CC_TREE* Tree)
{
    printf("-----------PRINTING TREE------------\n");
    if (Tree->IsRoot == 1)
    {
        return;
    }

    // Pass initial space count as 0
    Print2DUtil(Tree, 0);

    printf("\n-----------PRINTING ENDED-----------\n\n");
}

void PrintPostOrder(CC_TREE* Tree)
{
    if (Tree == NULL)
    {
        return;
    }

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

void PrintInOrder(CC_TREE* Tree)
{
    if (Tree == NULL)
    {
        return;
    }

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

void PrintPreOrder(CC_TREE* Tree)
{
    if (Tree == NULL)
    {
        return;
    }

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
