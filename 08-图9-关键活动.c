#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

const int INF = 10000000;

typedef struct QNode
{
    int *data;
    int front, end;
    int capacity;
} QNode, *Queue;

typedef struct ENode
{
    int V, W, time;
} Edge;

typedef struct AdjVNode
{
    int V, time;
    struct AdjVNode *next;
} AdjVNode, *PtrToAdjV;

typedef PtrToAdjV *AdjList;

typedef struct GNode
{
    int Nv, Ne;
    AdjList G;
} GNode, *LGraph;

LGraph CreateGraph(int Nv, int Ne, Edge *ESet, bool reverse);
void InsertEdge(LGraph Graph, int V, int W, int time);
bool TopSort(LGraph Graph, int *times);
void TopSortReverse(LGraph Graph, int *latestTimes, int earliestFinishTime);
void KeyPath(LGraph Graph, int *earliestTimes, int *latestTimes);
void Initialize(LGraph Graph, int *Indegree);
int FindMax(int *array, int n);
Queue CreateQueue(int n);
void Enqueue(Queue queue, int V);
int Dequeue(Queue queue);
bool IsEmpty(Queue queue);

int main(void)
{
    int Nv, Ne;
    scanf("%d %d", &Nv, &Ne);
    Edge ESet[Ne];
    for (int i = 0; i < Ne; i++)
    {
        scanf("%d %d %d", &ESet[i].V, &ESet[i].W, &ESet[i].time);
        ESet[i].V--;
        ESet[i].W--;
    }
    LGraph Graph = CreateGraph(Nv, Ne, ESet, false);
    int earliestTimes[Graph->Nv];
    if (TopSort(Graph, earliestTimes))
    {
        LGraph RGraph = CreateGraph(Nv, Ne, ESet, true);
        int latestTimes[Graph->Nv];
        int earliestFinishTime = FindMax(earliestTimes, Graph->Nv);
        printf("%d\n", earliestFinishTime);
        TopSortReverse(RGraph, latestTimes, earliestFinishTime);
        KeyPath(Graph, earliestTimes, latestTimes);
    }
    else
    {
        printf("0\n");
    }
    return 0;
}

LGraph CreateGraph(int Nv, int Ne, Edge *ESet, bool reverse)
{
    LGraph Graph = (LGraph)malloc(sizeof(GNode));
    Graph->Nv = Nv;
    Graph->Ne = Ne;
    Graph->G = (AdjList)malloc(sizeof(PtrToAdjV) * Graph->Ne);
    for (int i = 0; i < Graph->Nv; i++)
    {
        Graph->G[i] = NULL;
    }
    for (int i = 0; i < Graph->Ne; i++)
    {
        if (reverse)
        {
            InsertEdge(Graph, ESet[i].W, ESet[i].V, ESet[i].time);
        }
        else
        {
            InsertEdge(Graph, ESet[i].V, ESet[i].W, ESet[i].time);
        }
    }
    return Graph;
}

void InsertEdge(LGraph Graph, int V, int W, int time)
{
    PtrToAdjV edge = (PtrToAdjV)malloc(sizeof(AdjVNode));
    edge->V = W;
    edge->time = time;
    edge->next = Graph->G[V];
    Graph->G[V] = edge;
}

bool TopSort(LGraph Graph, int *times)
{
    Queue queue = CreateQueue(Graph->Nv);
    int Indegree[Graph->Nv];
    Initialize(Graph, Indegree);
    for (int i = 0; i < Graph->Nv; i++)
    {
        times[i] = 0;
    }
    int V, count = 0;
    for (int V = 0; V < Graph->Nv; V++)
    {
        if (Indegree[V] == 0)
        {
            Enqueue(queue, V);
            count++;
        }
    }
    while (!IsEmpty(queue))
    {
        V = Dequeue(queue);
        for (PtrToAdjV W = Graph->G[V]; W; W = W->next)
        {
            if (--Indegree[W->V] == 0)
            {
                Enqueue(queue, W->V);
                count++;
            }
            if (times[V] + W->time > times[W->V])
            {
                times[W->V] = times[V] + W->time;
            }
        }
    }
    free(queue->data);
    free(queue);
    if (count < Graph->Nv)
    {
        return false;
    }
    return true;
}

void TopSortReverse(LGraph Graph, int *latestTimes, int earliestFinishTime)
{
    Queue queue = CreateQueue(Graph->Nv);
    int Indegree[Graph->Nv];
    Initialize(Graph, Indegree);
    for (int V = 0; V < Graph->Nv; V++)
    {
        if (Indegree[V] != 0)
        {
            latestTimes[V] = INF;
        }
        else
        {
            latestTimes[V] = earliestFinishTime;
            Enqueue(queue, V);
        }
    }
    int V;
    while (!IsEmpty(queue))
    {
        V = Dequeue(queue);
        for (PtrToAdjV W = Graph->G[V]; W; W = W->next)
        {
            if (--Indegree[W->V] == 0)
            {
                Enqueue(queue, W->V);
            }
            if (latestTimes[V] - W->time < latestTimes[W->V])
            {
                latestTimes[W->V] = latestTimes[V] - W->time;
            }
        }
    }
    free(queue->data);
    free(queue);
}

void KeyPath(LGraph Graph, int *earliestTimes, int *latestTimes)
{
    int rest;
    for (int V = 0; V < Graph->Nv; V++)
    {
        for (PtrToAdjV W = Graph->G[V]; W; W = W->next)
        {
            rest = latestTimes[W->V] - earliestTimes[V] - W->time;
            if (rest == 0)
            {
                printf("%d->%d\n", V + 1, W->V + 1);
            }
        }
    }
}

void Initialize(LGraph Graph, int *Indegree)
{
    for (int V = 0; V < Graph->Nv; V++)
    {
        Indegree[V] = 0;
    }
    for (int V = 0; V < Graph->Nv; V++)
    {
        for (PtrToAdjV W = Graph->G[V]; W; W = W->next)
        {
            Indegree[W->V]++;
        }
    }
}

int FindMax(int *array, int n)
{
    int i, max = 0;
    for (i = 0; i < n; i++)
    {
        if (array[i] > max)
        {
            max = array[i];
        }
    }
    return max;
}

Queue CreateQueue(int n)
{
    Queue queue = (Queue)malloc(sizeof(QNode));
    queue->data = (int *)malloc(sizeof(int) * (n + 1));
    queue->front = queue->end = 0;
    queue->capacity = n;
    return queue;
}

void Enqueue(Queue queue, int V)
{
    queue->data[queue->front] = V;
    queue->front = (queue->front + 1) % (queue->capacity + 1);
}

int Dequeue(Queue queue)
{
    int temp = queue->data[queue->end];
    queue->end = (queue->end + 1) % (queue->capacity + 1);
    return temp;
}

bool IsEmpty(Queue queue)
{
    return queue->front == queue->end;
}
