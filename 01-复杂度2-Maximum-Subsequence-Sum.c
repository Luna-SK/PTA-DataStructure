#include <stdio.h>

int main(void)
{
    int n, sum = 0, max = -1;
    scanf("%d", &n);
    int a[n];
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &a[i]);
    }
    int start = a[0], end = a[n - 1];
    int tempStart = start;
    for (int i = 0; i < n; i++)
    {
        sum += a[i];
        if (sum > max)
        {
            max = sum;
            start = tempStart;
            end = a[i];
        }
        else if (sum < 0)
        {
            sum = 0;
            tempStart = a[i + 1];
        }
    }
    if (max < 0)
    {
        printf("0 %d %d", a[0], a[n - 1]);
    }
    else
    {
        printf("%d %d %d\n", max, start, end);
    }
    return 0;
}
