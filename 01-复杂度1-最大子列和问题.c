# include <stdio.h>

int main(void)
{
    int n, sum = 0, max = 0;
    scanf("%d", &n);
    int a[n];
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &a[i]);
    }
    for (int i = 0; i < n; i++)
    {
        sum += a[i];
        if (sum > max)
        {
            max = sum;
        }
        else if (sum < 0)
        {
            sum = 0;
        }
    }
    printf("%d\n", max);
    return 0;
}
