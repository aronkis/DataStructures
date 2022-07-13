#include "ccstack.h"
#include "common.h"
#include "string.h"

#define INITIAL_SIZE    100

int StCreate(CC_STACK** Stack)
{
    CC_STACK* stack = NULL;

    CC_UNREFERENCED_PARAMETER(Stack);

    if (NULL == Stack)
    {
        return -1;
    }

    stack = (CC_STACK*)malloc(sizeof(CC_STACK));
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

int StDestroy(CC_STACK** Stack)
{
    CC_STACK* stack = *Stack;

    if (NULL == Stack)
    {
        return -1;
    }

    free(stack->Data);
    free(stack);

    *Stack = NULL;

    return 0;
}

int StPush(CC_STACK* Stack, int Value)
{
    CC_UNREFERENCED_PARAMETER(Stack);
    CC_UNREFERENCED_PARAMETER(Value);

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

int StPop(CC_STACK* Stack, int* Value)
{
    CC_UNREFERENCED_PARAMETER(Stack);
    CC_UNREFERENCED_PARAMETER(Value);

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

int StPeek(CC_STACK* Stack, int* Value)
{
    CC_UNREFERENCED_PARAMETER(Stack);
    CC_UNREFERENCED_PARAMETER(Value);

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

int StIsEmpty(CC_STACK* Stack)
{
    CC_UNREFERENCED_PARAMETER(Stack);

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

int StGetCount(CC_STACK* Stack)
{
    CC_UNREFERENCED_PARAMETER(Stack);

    if (NULL == Stack)
    {
        return -1;
    }

    return Stack->Top + 1;
}

int StClear(CC_STACK* Stack)
{
    CC_UNREFERENCED_PARAMETER(Stack);

    if (NULL == Stack)
    {
        return -1;
    }

    Stack->Top = -1;

    return 0;
}

int StPushStack(CC_STACK* Stack, CC_STACK* StackToPush)
{
    CC_UNREFERENCED_PARAMETER(Stack);
    CC_UNREFERENCED_PARAMETER(StackToPush);


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

    int number = 0;

    while (StackToPush->Top > -1)
    {
        StPop(StackToPush, &number);
        StPush(Stack, number);
    }

    return 0;
}