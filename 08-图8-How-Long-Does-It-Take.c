#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct QNode
{
    int *data;
    int front, end;
    int capacity;
} QNode, *Queue;

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

LGraph CreateGraph();
void InsertEdge(LGraph Graph, int V, int W, int time);
int CalculateTime(LGraph Graph);
void Initialize(LGraph Graph, int *Indegree);
int FindMax(int *array, int n);
Queue CreateQueue(int n);
void Enqueue(Queue queue, int V);
int Dequeue(Queue queue);
bool IsEmpty(Queue queue);

int main(void)
{
    LGraph Graph = CreateGraph();
    int earliestTime = CalculateTime(Graph);
    if (earliestTime == -1)
    {
        printf("Impossible\n");
    }
    else
    {
        printf("%d\n", earliestTime);
    }
    return 0;
}

LGraph CreateGraph()
{
    LGraph Graph = (LGraph)malloc(sizeof(GNode));
    scanf("%d %d", &Graph->Nv, &Graph->Ne);
    Graph->G = (AdjList)malloc(sizeof(PtrToAdjV) * Graph->Ne);
    for (int i = 0; i < Graph->Nv; i++)
    {
        Graph->G[i] = NULL;
    }
    for (int i = 0, V, W, time; i < Graph->Ne; i++)
    {
        scanf("%d %d %d", &V, &W, &time);
        InsertEdge(Graph, V, W, time);
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

int CalculateTime(LGraph Graph)
{
    Queue queue = CreateQueue(Graph->Nv);
    int Indegree[Graph->Nv];
    Initialize(Graph, Indegree);
    int times[Graph->Nv];
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
    int earliestTime = FindMax(times, Graph->Nv);
    if (count < Graph->Nv)
    {
        earliestTime = -1;
    }
    return earliestTime;
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
    int max = 0;
    for (int i = 0; i < n; i++)
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