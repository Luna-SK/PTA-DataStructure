#include <stdio.h>
#include <stdlib.h>

#define MAXSIZE 100001

typedef struct Node
{
    int value;
    int next;
} Node;

int Reverse(Node[], int, int);
void Print(Node[], int);

int main(void)
{
    Node list[MAXSIZE];
    int fa, a, n, k;
    scanf("%d %d %d", &fa, &n, &k);
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &a);
        scanf("%d %d", &list[a].value, &list[a].next);
    }
    fa = Reverse(list, fa, k);
    Print(list, fa);
}

int Reverse(Node list[], int fa, int k0)
{
    int p, n, listHead = fa, k = k0, head = fa, tail = fa;
    while (tail != -1 && k != 1)
    {
        tail = list[tail].next;
        k--;
    }
    k = k0;
    if (tail != -1)
    {
        listHead = tail;
    }
    while (tail != -1)
    {
        p = head;
        while (head != tail)
        {
            head = list[p].next;
            list[p].next = list[tail].next;
            list[tail].next = p;
            p = head;
        }
        while (k != 1)
        {
            p = list[p].next;
            k--;
        }
        k = k0;
        head = tail = list[p].next;
        while (tail != -1 && k != 1)
        {
            tail = list[tail].next;
            k--;
        }
        k = k0;
        if (tail != -1)
        {
            list[p].next = tail;
        }
    }
    return listHead;
}

void Print(Node list[], int fa)
{
    int p = fa;
    while (list[p].next != -1)
    {
        printf("%05d %d %05d\n", p, list[p].value, list[p].next);
        p = list[p].next;
    }
    printf("%05d %d %d\n", p, list[p].value, list[p].next);
}