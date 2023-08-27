#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAXVNUM 10

typedef struct QNode
{
    int *data;
    int front;
    int end;
    int size;
} QNode, *Queue;

typedef struct GNode
{
    int Nv;
    int Ne;
    int G[MAXVNUM][MAXVNUM];
} GNode, *MGraph;

MGraph CreateGraph();
void DFS(MGraph Graph);
void DFSUtil(MGraph Graph, int V, bool *collected);
void BFS(MGraph Graph);
void BFSUtil(MGraph Graph, int V, bool *collected);
Queue CreateQueue(int size);
void Enqueue(Queue queue, int data);
int Dequeue(Queue queue);
bool IsEmpty(Queue queue);

int main(void)
{
    MGraph Graph = CreateGraph();
    DFS(Graph);
    BFS(Graph);
    return 0;
}

MGraph CreateGraph()
{
    MGraph Graph = (MGraph)malloc(sizeof(GNode));
    int V1, V2;
    scanf("%d %d", &Graph->Nv, &Graph->Ne);
    for (int i = 0; i < Graph->Nv; i++)
    {
        for (int j = 0; j < Graph->Ne; j++)
        {
            Graph->G[i][j] = 0;
        }
    }
    for (int i = 0; i < Graph->Ne; i++)
    {
        scanf("%d %d", &V1, &V2);
        Graph->G[V1][V2] = Graph->G[V2][V1] = 1;
    }
    return Graph;
}

void DFS(MGraph Graph)
{
    bool collected[MAXVNUM];
    for (int V = 0; V < Graph->Nv; V++)
    {
        collected[V] = false;
    }
    for (int V = 0; V < Graph->Nv; V++)
    {
        if (!collected[V])
        {
            printf("{ ");
            DFSUtil(Graph, V, collected);
            printf("}\n");
        }
    }
}

void DFSUtil(MGraph Graph, int V, bool *collected)
{
    collected[V] = true;
    printf("%d ", V);
    for (int W = 0; W < Graph->Nv; W++)
    {
        if (!collected[W] && Graph->G[V][W])
        {
            DFSUtil(Graph, W, collected);
        }
    }
}

void BFS(MGraph Graph)
{
    bool collected[MAXVNUM];
    for (int V = 0; V < Graph->Nv; V++)
    {
        collected[V] = false;
    }
    for (int V = 0; V < Graph->Nv; V++)
    {
        if (!collected[V])
        {
            printf("{ ");
            BFSUtil(Graph, V, collected);
            printf("}\n");
        }
    }
}

void BFSUtil(MGraph Graph, int V, bool *collected)
{
    int W;
    Queue queue = CreateQueue(Graph->Nv);
    Enqueue(queue, V);
    collected[V] = true;
    while (!IsEmpty(queue))
    {
        W = Dequeue(queue);
        printf("%d ", W);
        for (int U = 0; U < Graph->Nv; U++)
        {
            if (!collected[U] && Graph->G[W][U])
            {
                Enqueue(queue, U);
                collected[U] = true;
            }
        }
    }
}
Queue CreateQueue(int size)
{
    Queue queue = (Queue)malloc(sizeof(QNode));
    queue->size = size;
    queue->front = queue->end = 0;
    queue->data = (int *)malloc(sizeof(int) * (size + 1));
    return queue;
}

void Enqueue(Queue queue, int data)
{
    queue->data[queue->front] = data;
    queue->front = (queue->front + 1) % (queue->size + 1);
}
int Dequeue(Queue queue)
{
    int temp = queue->end;
    queue->end = (queue->end + 1) % (queue->size + 1);
    return queue->data[temp];
}
bool IsEmpty(Queue queue)
{
    return queue->front == queue->end;
}