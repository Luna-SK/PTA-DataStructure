#include <stdio.h>
#include <stdlib.h>

void MergeSort(int *a, int n);
void MergePass(int *a, int *temp, int n, int length);
void Merge(int *a, int *temp, int L, int R, int REnd);

int main(void)
{
    int n;
    scanf("%d", &n);
    int a[n];
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &a[i]);
    }
    MergeSort(a, n);
    for (int i = 0; i < n - 1; i++)
    {
        printf("%d ", a[i]);
    }
    printf("%d", a[n - 1]);
}

void MergeSort(int *a, int n)
{
    int *temp = (int *)malloc(sizeof(int) * n);
    int length = 1;
    if (temp != NULL)
    {
        while (length < n)
        {
            MergePass(a, temp, n, length);
            length *= 2;
            MergePass(temp, a, n, length);
            length *= 2;
        }
        free(temp);
    }
    else
    {
        printf("Error!\n");
    }
}

void MergePass(int *a, int *temp, int n, int length)
{
    int i;
    for (i = 0; i <= n - 2 * length; i += 2 * length)
    {
        Merge(a, temp, i, i + length, i + 2 * length - 1);
    }
    if (i + length < n)
    {
        Merge(a, temp, i, i + length, n - 1);
    }
    else
    {
        while (i < n)
        {
            temp[i] = a[i];
            i++;
        }
    }
}

void Merge(int *a, int *temp, int L, int R, int REnd)
{
    int NumElements = REnd - L + 1;
    int LEnd = R - 1;
    int t = L;
    while (L <= LEnd && R <= REnd)
    {
        if (a[L] < a[R])
        {
            temp[t++] = a[L++];
        }
        else
        {
            temp[t++] = a[R++];
        }
    }
    while (L <= LEnd)
    {
        temp[t++] = a[L++];
    }
    while (R <= REnd)
    {
        temp[t++] = a[R++];
    }
}

// void MSort(int *a, int *temp, int L, int REnd);

// void MergeSort(int *a, int n)
// {
//     int *temp = (int *)malloc(sizeof(int) * n);
//     if (temp != NULL)
//     {
//         MSort(a, temp, 0, n - 1);
//         free(temp);
//     }
//     else
//     {
//         printf("Error!\n");
//     }
// }

// void MSort(int *a, int *temp, int L, int REnd)
// {
//     if (L < REnd)
//     {
//         int center = (L + REnd) / 2;
//         MSort(a, temp, L, center);
//         MSort(a, temp, center + 1, REnd);
//         Merge(a, temp, L, center + 1, REnd);
//     }
// }

// void Merge(int *a, int *temp, int L, int R, int REnd)
// {
//     int NumElements = REnd - L + 1;
//     int LEnd = R - 1;
//     int t = L;
//     while (L <= LEnd && R <= REnd)
//     {
//         if (a[L] < a[R])
//         {
//             temp[t++] = a[L++];
//         }
//         else
//         {
//             temp[t++] = a[R++];
//         }
//     }
//     while (L <= LEnd)
//     {
//         temp[t++] = a[L++];
//     }
//     while (R <= REnd)
//     {
//         temp[t++] = a[R++];
//     }
//     for (int i = 0; i < NumElements; i++, REnd--)
//     {
//         a[REnd] = temp[REnd];
//     }
// }

// for (int i = 1; i < n; i++)
// {
//     int temp = a[i], j;
//     for (j = i; j > 0 && a[j - 1] > temp; j--)
//     {
//         a[j] = a[j - 1];
//     }
//     a[j] = temp;
// }
// for (int i = 0; i < n - 1; i++)
// {
//     printf("%d ", a[i]);
// }
// printf("%d", a[n - 1]);