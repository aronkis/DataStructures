#ifndef _DATA_STRUCTURES_STACK_H_
#define _DATA_STRUCTURES_STACK_H_

typedef struct STACK{
    // Members
    int* Data;
    int Top;
    int Size;
} STACK;

int StCreate(STACK **Stack);
int StDestroy(STACK **Stack);

int StPush(STACK *Stack, int Value);
int StPop(STACK *Stack, int *Value);

// Gets top of stack without popping the value
int StPeek(STACK *Stack, int *Value);

//  Returns:
//       1  - Stack is empty
//       0  - Stack is not empty
//      -1  - Error or invalid parameter
int StIsEmpty(STACK *Stack);

// Returns the number of elements in the stack
int StGetCount(STACK *Stack);

// Removes all elements from the stack
int StClear(STACK *Stack);

// StPushStack removes all the elements from the StackToPush and appends
// them to the first stack
// ex: Stack1: 1, 2, 3
//     Stack2: 1, 4, 5
// After push: Stack1: 1, 2, 3, 1, 4, 5
//             Stack2: empty
int StPushStack(STACK *Stack, STACK *StackToPush);

#endif
