#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXSIZE 30

typedef struct SNode
{
    int *elements;
    int top;
} *Stack;
int size;

void Input(int *PreOrder, int *InOrder, int length);
void PostOrderTraversal(int *PreOrder, int *InOrder, int length);
Stack CreateStack();
void Push(Stack stack, int item);
int Pop(Stack stack);

int main(void)
{
    int length, PreOrder[MAXSIZE], InOrder[MAXSIZE];
    scanf("%d", &length);
    size = length;
    Input(PreOrder, InOrder, length);
    PostOrderTraversal(PreOrder, InOrder, length);
    return 0;
}

void Input(int *PreOrder, int *InOrder, int length)
{
    Stack stack = CreateStack();
    char operation[5];
    int item, preCount = 0, inCount = 0;
    for (int i = 0; i < length * 2; i++)
    {
        scanf("%s", operation);
        if (strcmp(operation, "Push") == 0)
        {
            scanf("%d", &item);
            Push(stack, item);
            PreOrder[preCount++] = item;
        }
        else
        {
            InOrder[inCount++] = Pop(stack);
        }
    }
}
void PostOrderTraversal(int *PreOrder, int *InOrder, int length)
{
    if (length == 0)
    {
        return;
    }
    if (length == 1)
    {
        printf("%d", InOrder[0]);
        if (length != size)
        {
            printf(" ");
        }
        return;
    }
    int rootIndex = 0, item = PreOrder[0];
    while (InOrder[rootIndex] != PreOrder[0] && rootIndex < length)
    {
        rootIndex++;
    }
    if (rootIndex >= length)
    {
        return;
    }
    PostOrderTraversal(PreOrder + 1, InOrder, rootIndex);
    PostOrderTraversal(PreOrder + rootIndex + 1, InOrder + rootIndex + 1, length - rootIndex - 1);
    printf("%d", PreOrder[0]);
    if (length != size)
    {
        printf(" ");
    }
}

Stack CreateStack()
{
    Stack stack = (Stack)malloc(sizeof(struct SNode));
    stack->elements = (int *)malloc(sizeof(int) * MAXSIZE);
    stack->top = -1;
    return stack;
}

void Push(Stack stack, int item)
{
    stack->elements[++stack->top] = item;
}

int Pop(Stack stack)
{
    return stack->elements[stack->top--];
}