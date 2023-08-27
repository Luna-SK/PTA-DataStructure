#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct Edge
{
    int V, W;
    int weight;
} Edge, *EdgeSet;

typedef struct GNode
{
    int Nv, Ne;
    EdgeSet Eset;
} GNode, *EGraph;

EGraph CreateGraph();
int compare(const void *a, const void *b);
int Kruskal(EGraph Graph);
bool CheckCycle(int *ESet, int V, int W);
int Find(int *ESet, int x);
void Union(int *ESet, int root1, int root2);

int main(void)
{
    EGraph Graph = CreateGraph();
    int minWeight = Kruskal(Graph);
    printf("%d\n", minWeight);
    return 0;
}

EGraph CreateGraph()
{
    EGraph Graph = (EGraph)malloc(sizeof(GNode));
    scanf("%d %d", &Graph->Nv, &Graph->Ne);
    Graph->Eset = (EdgeSet)malloc(sizeof(Edge) * Graph->Ne);
    for (int i = 0; i < Graph->Ne; i++)
    {
        scanf("%d %d %d", &Graph->Eset[i].V, &Graph->Eset[i].W, &Graph->Eset[i].weight);
        Graph->Eset[i].V--;
        Graph->Eset[i].W--;
    }
    qsort(Graph->Eset, Graph->Ne, sizeof(Edge), compare);
    return Graph;
}

int compare(const void *a, const void *b)
{
    return ((EdgeSet)a)->weight - ((EdgeSet)b)->weight;
}

int Kruskal(EGraph Graph)
{
    int ESet[Graph->Ne];
    for (int i = 0; i < Graph->Ne; i++)
    {
        ESet[i] = -1;
    }
    int minWeight = 0, edgeIndex = 0, edgeCount = 0;
    while (edgeCount < Graph->Nv - 1 && edgeIndex < Graph->Ne)
    {
        if (CheckCycle(ESet, Graph->Eset[edgeIndex].V, Graph->Eset[edgeIndex].W))
        {
            minWeight += Graph->Eset[edgeIndex].weight;
            edgeCount++;
        }
        edgeIndex++;
    }
    if (edgeCount < Graph->Nv - 1)
    {
        minWeight = -1;
    }
    free(Graph->Eset);
    free(Graph);
    return minWeight;
}

bool CheckCycle(int *ESet, int V, int W)
{
    int root1 = Find(ESet, V);
    int root2 = Find(ESet, W);
    if (root1 == root2)
    {
        return false;
    }
    else
    {
        Union(ESet, root1, root2);
        return true;
    }
}

int Find(int *ESet, int x)
{
    if (ESet[x] < 0)
    {
        return x;
    }
    else
    {
        return ESet[x] = Find(ESet, ESet[x]);
    }
}

void Union(int *ESet, int root1, int root2)
{
    if (ESet[root1] > ESet[root2])
    {
        ESet[root2] += ESet[root1];
        ESet[root1] = root2;
    }
    else
    {
        ESet[root1] += ESet[root2];
        ESet[root2] = root1;
    }
}