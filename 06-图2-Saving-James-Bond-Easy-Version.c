#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct VNode
{
    int x;
    int y;
    bool safe;
} Coordinate;

bool IsReachable(int x1, int x2, int y1, int y2, int maxJump);
bool IsSafe(int x, int y, int maxJump);
void CreateSets(Coordinate *P, int maxJump, int *sets, int length);
void Union(int *sets, int i, int j);
int Find(int *sets, int data);
bool Judge(Coordinate *P, int *sets, int length);

int main(void)
{
    int Nv, maxJump;
    scanf("%d %d", &Nv, &maxJump);
    Coordinate P[Nv + 1];
    int sets[Nv + 1];
    P[0].safe = false;
    P[0].x = P[0].y = 0;
    sets[0] = -1;
    for (int i = 1; i <= Nv; i++)
    {
        scanf("%d %d", &P[i].x, &P[i].y);
        P[i].safe = false;
        sets[i] = -1;
    }
    CreateSets(P, maxJump, sets, Nv + 1);
    if (Judge(P, sets, Nv + 1))
    {
        printf("Yes\n");
    }
    else
    {
        printf("No\n");
    }
}

bool IsReachable(int x1, int y1, int x2, int y2, int maxJump)
{
    if ((x1 != 0 || y1 != 0) && (x2 != 0 || y2 != 0))
    {
        return (x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2) <= maxJump * maxJump;
    }
    else if ((x1 == 0 && y1 == 0) && (x2 != 0 || y2 != 0))
    {
        return x2 * x2 + y2 * y2 <= (maxJump + 15) * (maxJump + 15);
    }
    else if ((x2 == 0 && y2 == 0) && (x1 != 0 || y1 != 0))
    {
        return x1 * x1 + y1 * y1 <= (maxJump + 15) * (maxJump + 15);
    }
    return false;
}

bool IsSafe(int x, int y, int maxJump)
{
    if (x == 0 && y == 0)
    {
        return false;
    }
    return (50 - abs(x)) <= maxJump || (50 - abs(y)) <= maxJump;
}

void CreateSets(Coordinate *P, int maxJump, int *sets, int length)
{
    for (int i = 0; i < length; i++)
    {
        if (IsSafe(P[i].x, P[i].y, maxJump))
        {
            P[i].safe = true;
        }
        for (int j = 0; j < length; j++)
        {
            if (i < j && IsReachable(P[i].x, P[i].y, P[j].x, P[j].y, maxJump))
            {
                Union(sets, i, j);
            }
        }
    }
}

void Union(int *sets, int i, int j)
{
    int root1 = Find(sets, i);
    int root2 = Find(sets, j);
    if (root1 > root2)
    {
        sets[root2] += sets[root1];
        sets[root1] = root2;
    }
    else if(root1 < root2)
    {
        sets[root1] += sets[root2];
        sets[root2] = root1;
    }
}

int Find(int *sets, int data)
{
    if (sets[data] < 0)
    {
        return data;
    }
    else
    {
        return sets[data] = Find(sets, sets[data]);
    }
}

bool Judge(Coordinate *P, int *sets, int length)
{
    int origin, destination;
    origin = Find(sets, 0);
    for (int i = 0; i < length; i++)
    {
        if (P[i].safe)
        {
            destination = Find(sets, i);
            if (origin == destination)
            {
                return true;
            }
        }
    }
    return false;
}