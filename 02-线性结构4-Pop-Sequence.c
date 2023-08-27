#include <stdio.h>
#include <stdbool.h>


void Input(int *, int);
bool Check(int *, int, int);

int main(void)
{
    int m, n, k;
    int top = -1;
    scanf("%d %d %d", &m, &n, &k);
    int stack[n];
    bool results[n];
    for (int i = 0; i < k; i++)
    {
        Input(stack, n);
        if (Check(stack, m, n))
        {
            results[i] = true;
        }
        else
        {
            results[i] = false;
        }
    }
    for (int i = 0; i < k; i++)
    {
        if(results[i])
        {
            printf("YES\n");
        }
        else
        {
            printf("NO\n");
        }
    }
    return 0;
}

void Input(int *stack, int n)
{
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &stack[i]);
    }
}

bool Check(int *stack, int m, int n)
{
    int count = 0, index = 0, pre = 0;
    if (m == 1)
    {
        for (int i = 0; i < n; i++)
        {
            if (stack[i - 1] > stack[i])
            {
                return false;
            }
        }
    }
    else
    {
        while (index < n - 1)
        {
            if (stack[index] > stack[index + 1])
            {
                count++;
                if (count + 1 > m)
                {
                    return false;
                }
            }
            else
            {
                count = 0;
                if (stack[pre] > stack[index + 1])
                {
                    return false;
                }
                pre = index + 1;
            }
            index++;
        }
    }
    return true;
}