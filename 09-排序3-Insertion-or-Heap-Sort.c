#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int *result;

bool Compare(const int *a, const int *b, int n);
bool InsertSort(int *a, int n);
bool HeapSort(int *a, int n);
void BuildMaxHeap(int *a, int n);
void Percdown(int *a, int n);
void Swap(int *a, int *b);

int main(void)
{
    int n;
    scanf("%d", &n);
    int insert[n], heap[n];
    result = (int *)malloc(sizeof(int) * n);
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &insert[i]);
        heap[i] = insert[i];
    }
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &result[i]);
    }
    if (InsertSort(insert, n))
    {
        printf("Insertion Sort\n");
        for (int i = 0; i < n - 1; i++)
        {
            printf("%d ", insert[i]);
        }
        printf("%d\n", insert[n - 1]);
    }
    else if (HeapSort(heap, n))
    {
        printf("Heap Sort\n");
        for (int i = 0; i < n - 1; i++)
        {
            printf("%d ", heap[i]);
        }
        printf("%d\n", heap[n - 1]);
    }
    free(result);
    return 0;
}

bool Compare(const int *a, const int *b, int n)
{
    for (int i = 0; i < n; i++)
    {
        if (a[i] != b[i])
        {
            return false;
        }
    }
    return true;
}

bool InsertSort(int *a, int n)
{
    bool flag = false;
    for (int i = 1, j, temp; i < n; i++)
    {
        temp = a[i];
        for (j = i; j > 0 && temp < a[j - 1]; j--)
        {
            a[j] = a[j - 1];
        }
        a[j] = temp;
        if (flag)
        {
            return true;
        }
        if (Compare(a, result, n))
        {
            flag = true;
        }
    }
    return false;
}

bool HeapSort(int *a, int n)
{
    bool flag = false;
    int tail = n - 1;
    BuildMaxHeap(a, n);
    for (int i = 0; i < n - 1; i++)
    {
        Swap(&a[0], &a[tail]);
        Percdown(a, tail--);
        if (flag)
        {
            return true;
        }
        if (Compare(a, result, n))
        {
            flag = true;
        }
    }
    return false;
}

void BuildMaxHeap(int *a, int n)
{
    for (int root = n / 2; root >= 0; root--)
    {
        int temp = a[root];
        int child, parent = root;
        while (parent * 2 + 1 < n)
        {
            child = parent * 2 + 1;
            if (child + 1 < n && a[child] < a[child + 1])
            {
                child++;
            }
            if (temp >= a[child])
            {
                break;
            }
            else
            {
                a[parent] = a[child];
                parent = child;
            }
            a[parent] = temp;
        }
    }
}

void Percdown(int *a, int n)
{
    int temp = a[0];
    int parent = 0, child;
    while (parent * 2 + 1 < n)
    {
        child = parent * 2 + 1;
        if (child + 1 < n && a[child] < a[child + 1])
        {
            child++;
        }
        if (temp >= a[child])
        {
            break;
        }
        else
        {
            a[parent] = a[child];
            parent = child;
        }
    }
    a[parent] = temp;
}

void Swap(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}
