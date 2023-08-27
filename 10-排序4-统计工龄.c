#include <stdio.h>

int main(void)
{
    int n, age;
    scanf("%d", &n);
    int bucket[51];
    for (int i = 0; i <= 50; i++)
    {
        bucket[i] = 0;
    }
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &age);
        bucket[age]++;
    }
    for (int i = 0; i <= 50; i++)
    {
        if (bucket[i] > 0)
        {
            printf("%d:%d\n", i, bucket[i]);
        }
    }
    return 0;
}