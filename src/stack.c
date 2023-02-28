#include "stack.h"
#include "common.h"
#include "string.h"

#define INITIAL_SIZE    100

int StCreate(STACK **Stack)
{
    STACK* stack = NULL;
    
    if (NULL == Stack)
    {
        return -1;
    }

    stack = (STACK*)malloc(sizeof(STACK));
    if (NULL == stack)
    {
        return -1;
    }

    memset(stack, 0, sizeof(*stack));

    stack->Top = -1;
    stack->Size = INITIAL_SIZE;
    stack->Data = (int*)malloc(sizeof(int) * INITIAL_SIZE);
    if (NULL == stack->Data)
    {
        free(stack);
        return -1;
    }

    *Stack = stack;

    return 0;
}

int StDestroy(STACK **Stack)
{
    STACK* stack = *Stack;

    if (NULL == Stack)
    {
        return -1;
    }

    free(stack->Data);
    free(stack);

    return 0;
}

int StPush(STACK *Stack, int Value)
{
    if (NULL == Stack)
    {
        return -1;
    }

    if (Stack->Top >= Stack->Size)
    {
        return -1;
    }
    
    Stack->Top++;
    Stack->Data[Stack->Top] = Value;

    return 0;
}

int StPop(STACK *Stack, int *Value)
{
    if (NULL == Stack)
    {
        return -1;
    }

    // Empty
    if (Stack->Top == -1)
    {
        return -1;
    }

    *Value = Stack->Data[Stack->Top];
    Stack->Top--;

    return 0;
}

int StPeek(STACK *Stack, int *Value)
{
    if (NULL == Stack)
    {
        return -1;
    }

    // Empty
    if (Stack->Top == -1)
    {
        return -1;
    }

    *Value = Stack->Data[Stack->Top];

    return 0;
}

int StIsEmpty(STACK *Stack)
{
    if (NULL == Stack)
    {
        return -1;
    }

    if (Stack->Top == -1)
    {
        return 1;
    }

    return 0;
}

int StGetCount(STACK *Stack)
{
    if (NULL == Stack)
    {
        return -1;
    }

    int Count = Stack->Top + 1;

    return Count;
}

int StClear(STACK *Stack)
{
    if (NULL == Stack)
    {
        return -1;
    }

    Stack->Top = -1;

    return 0;
}

int StPushStack(STACK *Stack, STACK *StackToPush)
{
    if (NULL == Stack || NULL == StackToPush)
    {
        return -1;
    }

    if (Stack->Top + StackToPush->Top >= Stack->Size)
    {
        return -1;
    }

    if (Stack == StackToPush)
    {
        return -1;
    }

    int Number = 0;
    while (StackToPush->Top > -1)
    {
        StPop(StackToPush, &Number);
        StPush(Stack, Number);
    }
    
    return -1;
}