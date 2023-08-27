#include <stdio.h>

int Find(int *sets, int element);
void Union(int *sets, int root1, int root2);
void CheckIfConnect(int *sets);
void InputConnection(int *sets);
void Stop(int *sets, int N);

int main(void)
{
    int N;
    char operation;
    scanf("%d", &N);
    int sets[N];
    for (int i = 0; i < N; i++)
    {
        sets[i] = -1;
    }
    do
    {
        scanf(" %c", &operation);
        switch (operation)
        {
        case 'C':
            CheckIfConnect(sets);
            break;
        case 'I':
            InputConnection(sets);
            break;
        case 'S':
            Stop(sets, N);
            break;
        default:
            break;
        }
    } while (operation != 'S');
    return 0;
}

int Find(int *sets, int element)
{
    if (sets[element] < 0)
    {
        return element;
    }
    else
    {
        return sets[element] = Find(sets, sets[element]);
    }
}

void Union(int *sets, int root1, int root2)
{
    if(sets[root1] > sets[root2])
    {
        sets[root2] += sets[root1];
        sets[root1] = root2;
    }
    else
    {
        sets[root1] += sets[root2];
        sets[root2] = root1;
    }
}

void CheckIfConnect(int *sets)
{
    int element1, element2;
    scanf("%d %d", &element1, &element2);
    int root1 = Find(sets, element1 - 1);
    int root2 = Find(sets, element2 - 1);
    if (root1 == root2)
    {
        printf("yes\n");
    }
    else
    {
        printf("no\n");
    }
}

void InputConnection(int *sets)
{
    int element1, element2;
    scanf("%d %d", &element1, &element2);
    int root1 = Find(sets, element1 - 1);
    int root2 = Find(sets, element2 - 1);
    if (root1 != root2)
    {
        Union(sets, root1, root2);
    }
}

void Stop(int *sets, int N)
{
    int count = 0;
    for (int i = 0; i < N; i++)
    {
        if (sets[i] < 0)
        {
            count++;
        }
    }
    if (count == 1)
    {
        printf("The network is connected.\n");
    }
    else
    {
        printf("There are %d components.\n", count);
    }
}