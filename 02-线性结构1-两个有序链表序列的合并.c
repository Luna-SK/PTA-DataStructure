#include <stdio.h>
#include <stdlib.h>

typedef int ElementType;
typedef struct Node *PtrToNode;
struct Node
{
    ElementType Data;
    PtrToNode Next;
};
typedef PtrToNode List;

List Read();        /* 细节在此不表 */
void Print(List L); /* 细节在此不表；空链表将输出NULL */

List Merge(List L1, List L2);

int main()
{
    List L1, L2, L;
    L1 = Read();
    L2 = Read();
    L = Merge(L1, L2);
    Print(L);
    Print(L1);
    Print(L2);
    return 0;
}

/* 你的代码将被嵌在这里 */
List Merge(List L1, List L2)
{
    List p = (List)malloc(sizeof(struct Node));
    List rear = p, t1 = L1, t2 = L2;
    L1 = L1->Next;
    L2 = L2->Next;
    t1->Next = NULL;
    t2->Next = NULL;
    while (L1 && L2)
    {
        if (L1->Data == L2->Data)
        {
            rear->Next = L1;
            L1 = L1->Next;
            rear->Next->Next = L2;
            L2 = L2->Next;
            rear = rear->Next->Next;
            rear->Next = NULL;
        }
        else if (L1->Data < L2->Data)
        {
            rear->Next = L1;
            L1 = L1->Next;
            rear = rear->Next;
            rear->Next = NULL;
        }
        else
        {
            rear->Next = L2;
            L2 = L2->Next;
            rear = rear->Next;
            rear->Next = NULL;
        }
    }
    while (L1)
    {
        rear->Next = L1;
        L1 = NULL;
    }
    while (L2)
    {
        rear->Next = L2;
        L2 = NULL;
    }
    return p;
}