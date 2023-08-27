#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int *result;

bool Compare(const int *a, const int *b, int n);
bool InsertSort(int *a, int n);
bool MergeSort(int *a, int n);
void MergePass(int *a, int *b, int n, int length);
void Merge(int *a, int *b, int L, int R, int RightEnd);

int main(void)
{
    int n;
    scanf("%d", &n);
    int insert[n], merge[n];
    result = (int *)malloc(sizeof(int) * n);
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &insert[i]);
        merge[i] = insert[i];
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
    else if (MergeSort(merge, n))
    {
        printf("Merge Sort\n");
        for (int i = 0; i < n - 1; i++)
        {
            printf("%d ", merge[i]);
        }
        printf("%d\n", merge[n - 1]);
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

bool MergeSort(int *a, int n)
{
    bool flag = false;
    int length = 1;
    int *temp = (int *)malloc(sizeof(int) * n);
    while (length < n)
    {
        MergePass(a, temp, n, length);
        length *= 2;
        if (flag)
        {
            for (int i = 0; i < n; i++)
            {
                a[i] = temp[i];
            }
            free(temp);
            return true;
        }
        if (Compare(temp, result, n))
        {
            flag = true;
        }
        MergePass(temp, a, n, length);
        length *= 2;
        if (flag)
        {
            free(temp);
            return true;
        }
        if (Compare(a, result, n))
        {
            flag = true;
        }
    }
    free(temp);
    return false;
}

void MergePass(int *a, int *b, int n, int length)
{
    int i;
    for (i = 0; i <= n - 2 * length; i += 2 * length)
    {
        Merge(a, b, i, i + length, i + 2 * length - 1);
    }
    if (i + length < n)
    {
        Merge(a, b, i, i + length, n - 1);
    }
    else
    {
        while (i < n)
        {
            b[i] = a[i];
            i++;
        }
    }
}

void Merge(int *a, int *b, int L, int R, int RightEnd)
{
    int LeftEnd = R - 1;
    int temp = L;
    while (L <= LeftEnd && R <= RightEnd)
    {
        if (a[L] < a[R])
        {
            b[temp++] = a[L++];
        }
        else
        {
            b[temp++] = a[R++];
        }
    }
    while (L <= LeftEnd)
    {
        b[temp++] = a[L++];
    }
    while (R <= RightEnd)
    {
        b[temp++] = a[R++];
    }
}