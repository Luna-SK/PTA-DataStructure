#include <stdio.h>
#include <stdlib.h>

#define MAXSIZE 10
#define NotFound 0
typedef int ElementType;

typedef int Position;
typedef struct LNode *List;
struct LNode
{
    ElementType Data[MAXSIZE];
    Position Last; /* 保存线性表中最后一个元素的位置 */
};

List ReadInput(); /* 裁判实现，细节不表。元素从下标1开始存储 */
Position BinarySearch(List L, ElementType X);

int main()
{
    List L;
    ElementType X;
    Position P;

    L = ReadInput();
    scanf("%d", &X);
    P = BinarySearch(L, X);
    printf("%d\n", P);

    return 0;
}

List ReadInput()
{
    int size;
    scanf("%d", &size);
    List L = (List)malloc(sizeof(struct LNode));
    L->Data[0] = -1;
    for (int i = 1; i <= size; i++)
    {
        scanf("%d", &(L->Data[i]));
    }
    L->Last = size;
    return L;
}

Position BinarySearch(List L, ElementType X)
{
    Position p, start = 1, end = L->Last;
    while (start <= end)
    {
        p = (start + end) / 2;
        if (L->Data[p] == X)
        {
            return p;
        }
        else if (L->Data[p] > X)
        {
            end = p - 1;
        }
        else if (L->Data[p] < X)
        {
            start = p + 1;
        }
    }
    return NotFound;
}
