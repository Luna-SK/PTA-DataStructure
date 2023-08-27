#include <stdio.h>
#include <stdlib.h>

#define MAXSIZE 1001

typedef struct Heap
{
    int *data;
    int size;
    int capacity;
} Heap, *MinHeap;

MinHeap CreateMinHeap()
{
    MinHeap H = (MinHeap)malloc(sizeof(Heap));
    H->data = (int *)malloc((MAXSIZE + 1) * sizeof(int));
    H->data[0] = -10001;
    H->size = 0;
    H->capacity = MAXSIZE;
    return H;
}

void Insert(MinHeap H, int element)
{
    int i = ++H->size;
    while (H->data[i / 2] > element)
    {
        H->data[i] = H->data[i / 2];
        i /= 2;
    }
    H->data[i] = element;
}

void OutputPath(MinHeap H, int start)
{
    while (start != 1)
    {
        printf("%d ", H->data[start]);
        start /= 2;
    }
    printf("%d", H->data[start]);
}

int main(void)
{
    int N, M, start;
    scanf("%d %d", &N, &M);
    MinHeap H = CreateMinHeap();
    for (int i = 0, element; i < N; i++)
    {
        scanf("%d", &element);
        Insert(H, element);
    }
    for (int i = 1; i < M; i++)
    {
        scanf("%d", &start);
        OutputPath(H, start);
        printf("\n");
    }
    scanf("%d", &start);
    OutputPath(H, start);
    return 0;
}
