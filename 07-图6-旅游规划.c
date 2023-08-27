#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

const int INIFINITY = 10000;

typedef struct ENode
{
    int V, W;
    int length, cost;
} ENode, *Edge;

typedef struct AdjVNode
{
    int AdjV;
    int length, cost;
    struct AdjVNode *next;
} AdjVNode, *PtrToAdjV;

typedef PtrToAdjV *AdjList;

typedef struct GNode
{
    int Nv, Ne;
    int start, end;
    AdjList G;
} GNode, *LGraph;

LGraph BuildGraph();
void InsertEdge(LGraph Graph, Edge E);
void Dijkstra(LGraph Graph, int *dist, int *cost);
int FindVMin(int *dist, bool *collected, int n);

int main(void)
{
    LGraph Graph = BuildGraph();
    int dist[Graph->Nv], cost[Graph->Nv];
    for (int i = 0; i < Graph->Nv; i++)
    {
        dist[i] = cost[i] = INIFINITY;
    }
    Dijkstra(Graph, dist, cost);
    printf("%d %d\n", dist[Graph->end], cost[Graph->end]);
    return 0;
}

LGraph BuildGraph()
{
    LGraph Graph = (LGraph)malloc(sizeof(GNode));
    scanf("%d %d %d %d", &Graph->Nv, &Graph->Ne, &Graph->start, &Graph->end);
    Graph->G = (AdjList)malloc(sizeof(PtrToAdjV) * Graph->Nv);
    for (int i = 0; i < Graph->Nv; i++)
    {
        Graph->G[i] = NULL;
    }
    Edge E = (Edge)malloc(sizeof(ENode));
    for (int i = 0; i < Graph->Ne; i++)
    {
        scanf("%d %d %d %d", &E->V, &E->W, &E->length, &E->cost);
        InsertEdge(Graph, E);
    }
    return Graph;
}

void InsertEdge(LGraph Graph, Edge E)
{
    PtrToAdjV NewNode = (PtrToAdjV)malloc(sizeof(AdjVNode));
    NewNode->AdjV = E->W;
    NewNode->length = E->length;
    NewNode->cost = E->cost;
    NewNode->next = Graph->G[E->V];
    Graph->G[E->V] = NewNode;
    NewNode = (PtrToAdjV)malloc(sizeof(AdjVNode));
    NewNode->AdjV = E->V;
    NewNode->length = E->length;
    NewNode->cost = E->cost;
    NewNode->next = Graph->G[E->W];
    Graph->G[E->W] = NewNode;
}

void Dijkstra(LGraph Graph, int *dist, int *cost)
{
    dist[Graph->start] = cost[Graph->start] = 0;
    bool collected[Graph->Nv];
    for (int i = 0; i < Graph->Nv; i++)
    {
        collected[i] = false;
    }
    while (true)
    {
        int V = FindVMin(dist, collected, Graph->Nv);
        collected[V] = true;
        if (V < 0)
        {
            break;
        }
        for (PtrToAdjV W = Graph->G[V]; W; W = W->next)
        {
            if (!collected[W->AdjV])
            {
                if (dist[V] + W->length < dist[W->AdjV])
                {
                    dist[W->AdjV] = dist[V] + W->length;
                    cost[W->AdjV] = cost[V] + W->cost;
                }
                else if (dist[V] + W->length == dist[W->AdjV] && cost[V] + W->cost < cost[W->AdjV])
                {
                    cost[W->AdjV] = cost[V] + W->cost;
                }
            }
        }
    }
}

int FindVMin(int *dist, bool *collected, int n)
{
    int min = INIFINITY, minV = -1;
    for (int i = 0; i < n; i++)
    {
        if (!collected[i] && dist[i] < min)
        {
            min = dist[i];
            minV = i;
        }
    }
    return minV;
}
