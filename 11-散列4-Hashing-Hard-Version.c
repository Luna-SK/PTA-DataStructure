#include <stdio.h>
#include <stdlib.h>

typedef struct ENode
{
    int V, W;
} ENode, *Edge;

typedef struct AdjVNode
{
    int AdjV;
    struct AdjVNode *next;
} AdjVNode, *PtrToAdjV;

typedef struct VNode
{
    int data;
    int degree;
    PtrToAdjV FirstEdge;
} VNode, *AdjList;

typedef struct GNode
{
    int Nv;
    AdjList G;
} GNode, *LGraph;

typedef struct Node
{
    int index;
    LGraph Graph;
} Node, *Data;

LGraph BuildGraph();
LGraph CreateGraph();
void InsertEdge(LGraph Graph, int V, int W);
int compare(const void *a, const void *b);
void AdjustDegree(LGraph Graph, int deletePoint);

int main(void)
{
    LGraph Graph = BuildGraph();
    int size = 0;
    Data list = (Data)malloc(sizeof(Node) * Graph->Nv);
    for (int i = 0; i < Graph->Nv; i++)
    {
        if (Graph->G[i].data >= 0)
        {
            list[size].index = i;
            list[size].Graph = Graph;
            size++;
        }
    }
    for (int i = 0; i < size; i++)
    {
        qsort(list + i, size - i, sizeof(Node), compare);
        printf("%d", Graph->G[(list + i)->index].data);
        if (i < size - 1)
        {
            printf(" ");
        }
        AdjustDegree(Graph, (list + i)->index);
    }
    printf("\n");
    return 0;
}

LGraph BuildGraph()
{
    LGraph Graph = CreateGraph();
    for (int i = 0, j; i < Graph->Nv; i++)
    {
        if (Graph->G[i].data >= 0)
        {
            j = Graph->G[i].data % Graph->Nv;
            while (j != i)
            {
                InsertEdge(Graph, j, i);
                j = (j + 1) % Graph->Nv;
            }
        }
    }
    return Graph;
}

LGraph CreateGraph()
{
    int Nv;
    scanf("%d", &Nv);
    LGraph Graph = (LGraph)malloc(sizeof(GNode));
    Graph->Nv = Nv;
    Graph->G = (AdjList)malloc(sizeof(VNode) * Nv);
    for (int i = 0; i < Nv; i++)
    {
        scanf("%d", &Graph->G[i].data);
        Graph->G[i].degree = 0;
        Graph->G[i].FirstEdge = NULL;
    }
    return Graph;
}

void InsertEdge(LGraph Graph, int V, int W)
{
    PtrToAdjV node = (PtrToAdjV)malloc(sizeof(AdjVNode));
    node->AdjV = W;
    node->next = Graph->G[V].FirstEdge;
    Graph->G[V].FirstEdge = node;
    Graph->G[W].degree++;
}

int compare(const void *a, const void *b)
{
    if (((Data)a)->Graph->G[((Data)a)->index].degree > ((Data)b)->Graph->G[((Data)b)->index].degree)
    {
        return 1;
    }
    else if (((Data)a)->Graph->G[((Data)a)->index].degree == ((Data)b)->Graph->G[((Data)b)->index].degree)
    {
        if (((Data)a)->Graph->G[((Data)a)->index].data > ((Data)b)->Graph->G[((Data)b)->index].data)
        {
            return 1;
        }
        else if (((Data)a)->Graph->G[((Data)a)->index].data > ((Data)b)->Graph->G[((Data)b)->index].data)
        {
            return 0;
        }
        else
        {
            return -1;
        }
    }
    else
    {
        return -1;
    }
}

void AdjustDegree(LGraph Graph, int deletePoint)
{
    PtrToAdjV p = Graph->G[deletePoint].FirstEdge;
    while (p)
    {
        Graph->G[p->AdjV].degree--;
        p = p->next;
    }
}