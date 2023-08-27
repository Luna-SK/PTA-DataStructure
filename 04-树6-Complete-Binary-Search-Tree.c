#include <stdio.h>

#define MAXSIZE 1000

int InOrder[MAXSIZE], result[MAXSIZE];
int N, InOrderIndex = 0;

void sort(int *array, int n)
{
    int temp;
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = 0; j < n - i - 1; j++)
        {
            if (array[j] > array[j + 1])
            {
                temp = array[j];
                array[j] = array[j + 1];
                array[j + 1] = temp;
            }
        }
    }
}

void BuildTree(int rootIndex)
{
    if (rootIndex >= N)
    {
        return;
    }
    BuildTree(rootIndex * 2 + 1);
    result[rootIndex] = InOrder[InOrderIndex++];
    BuildTree(rootIndex * 2 + 2);
}

int main(void)
{
    scanf("%d", &N);

    for (int i = 0; i < N; i++)
    {
        scanf("%d", &InOrder[i]);
    }
    sort(InOrder, N);
    BuildTree(0);
    for (int i = 0; i < N - 1; i++)
    {
        printf("%d ", result[i]);
    }
    printf("%d", result[N - 1]);
}