#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct QNode
{
    int *data;
    int front, end;
    int size;
} QNode, *Queue;

typedef struct ENode
{
    int V, W;
} ENode, *Edge;

typedef struct AdjVNode
{
    int AdjV;
    struct AdjVNode *next;
} AdjVNode, *PtrToAdjV;

typedef struct AdjVNode **AdjList;

typedef struct GNode
{
    int Nv, Ne;
    AdjList G;
} GNode, *LGraph;

LGraph CreateGraph();
void InsertEdge(LGraph Graph, Edge E);
void Output(LGraph Graph, int V);
int BFS(LGraph Graph, int V);
Queue CreateQueue(int size);
void Enqueue(Queue queue, int data);
int Dequeue(Queue queue);
bool IsEmpty(Queue queue);

int main(void)
{
    LGraph Graph = CreateGraph();
    for (int V = 1; V <= Graph->Nv; V++)
    {
        Output(Graph, V);
    }
    return 0;
}

LGraph CreateGraph()
{
    LGraph Graph = (LGraph)malloc(sizeof(GNode));
    scanf("%d %d", &Graph->Nv, &Graph->Ne);
    Graph->G = (AdjList)malloc(sizeof(AdjVNode) * Graph->Nv);
    for (int V = 1; V <= Graph->Nv; V++)
    {
        Graph->G[V - 1] = NULL;
    }
    Edge E = (Edge)malloc(sizeof(ENode));
    for (int i = 0; i < Graph->Ne; i++)
    {
        scanf("%d %d", &E->V, &E->W);
        InsertEdge(Graph, E);
    }
    free(E);
    return Graph;
}

void InsertEdge(LGraph Graph, Edge E)
{
    PtrToAdjV NewNode = (PtrToAdjV)malloc(sizeof(AdjVNode));
    NewNode->AdjV = E->W;
    NewNode->next = Graph->G[E->V - 1];
    Graph->G[E->V - 1] = NewNode;
    NewNode = (PtrToAdjV)malloc(sizeof(AdjVNode));
    NewNode->AdjV = E->V;
    NewNode->next = Graph->G[E->W - 1];
    Graph->G[E->W - 1] = NewNode;
}

void Output(LGraph Graph, int V)
{
    int currentVCount = BFS(Graph, V);
    printf("%d: %.2lf%%\n", V, (double)currentVCount * 100 / Graph->Nv);
}

int BFS(LGraph Graph, int V)
{
    PtrToAdjV W;
    int tail, last = V, count = 1, level = 0;
    bool collected[Graph->Nv];
    for (int V = 1; V <= Graph->Nv; V++)
    {
        collected[V - 1] = false;
    }
    Queue queue = CreateQueue(Graph->Nv);
    Enqueue(queue, V);
    collected[V - 1] = true;
    while (!IsEmpty(queue))
    {
        V = Dequeue(queue);
        for (W = Graph->G[V - 1]; W; W = W->next)
        {
            if (!collected[W->AdjV - 1])
            {
                Enqueue(queue, W->AdjV);
                collected[W->AdjV - 1] = true;
                count++;
                tail = W->AdjV;
            }
        }
        if (V == last)
        {
            level++;
            last = tail;
        }
        if (level == 6)
        {
            break;
        }
    }
    return count;
}

Queue CreateQueue(int size)
{
    Queue queue = (Queue)malloc(sizeof(QNode));
    queue->front = queue->end = 0;
    queue->size = size;
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
    int temp = queue->data[queue->end];
    queue->end = (queue->end + 1) % (queue->size + 1);
    return temp;
}

bool IsEmpty(Queue queue)
{
    return queue->front == queue->end;
}