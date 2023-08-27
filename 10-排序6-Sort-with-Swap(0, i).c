#include <stdio.h>

int main(void)
{
    int n, s = 0, k = 0;
    scanf("%d", &n);
    int a[n], t[n];
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &a[i]);
        t[a[i]] = i;
    }
    for (int i = 0; i < n; i++)
    {
        if (t[i] == i)
        {
            s++;
        }
    }
    for (int i = 0; i < n; i++)
    {
        if (t[i] != i)
        {
            while (t[i] != i)
            {
                t[i] = i;
                i = a[i];
            }
            k++;
        }
    }
    if (k == 0)
    {
        printf("0");
    }
    else if (a[0] == 0)
    {
        printf("%d", n - s + k);
    }
    else
    {
        printf("%d", n - s + k - 2);
    }
    return 0;
}