#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

const int INFINITY = 1000000;

typedef struct Point
{
    int x, y;
} Point;

typedef struct QNode
{
    int *data;
    int front, end;
    int size;
} QNode, *Queue;

int JumpDist(Point *point, int V1, int V2);
int OriginDist(Point *point, int V);
int FindSource(int *path, int V);
int BFS(Point *point, int *path, int N, int D);
Queue CreateQueue(int size);
bool IsEmpty(Queue queue);
void Enqueue(Queue queue, int data);
int Dequeue(Queue queue);

int main(void)
{
    int N, D;
    scanf("%d %d", &N, &D);
    Point point[N];
    for (int i = 0; i < N; i++)
    {
        scanf("%d %d", &point[i].x, &point[i].y);
    }
    if (7.5 + D >= 50)
    {
        printf("1\n");
    }
    else
    {
        int path[N], sortedPath[N], count = 0;
        for (int V = 0; V < N; V++)
        {
            path[V] = -1;
        }
        int minPointIndex = BFS(point, path, N, D);
        if (minPointIndex == -1)
        {
            printf("0\n");
        }
        else
        {
            for (int V = minPointIndex; V != -1; V = path[V])
            {
                sortedPath[count++] = V;
            }
            printf("%d\n", count + 1);
            for (int i = count - 1; i >= 0; i--)
            {
                printf("%d %d\n", point[sortedPath[i]].x, point[sortedPath[i]].y);
            }
        }
    }
    return 0;
}

int JumpDist(Point *point, int V1, int V2)
{
    return (point[V1].x - point[V2].x) * (point[V1].x - point[V2].x) + (point[V1].y - point[V2].y) * (point[V1].y - point[V2].y);
}

int OriginDist(Point *point, int V)
{
    return point[V].x * point[V].x + point[V].y * point[V].y;
}

int FindSource(int *path, int V)
{
    if (path[V] == -1)
    {
        return V;
    }
    else
    {
        return FindSource(path, path[V]);
    }
}

int BFS(Point *point, int *path, int N, int D)
{
    int dist[N], minDist = INFINITY, minPointIndex = -1;
    for (int V = 0; V < N; V++)
    {
        dist[V] = INFINITY;
    }
    Queue queue = CreateQueue(N);
    for (int V = 0, d; V < N; V++)
    {
        d = OriginDist(point, V);
        if (d > 7.5 * 7.5 && d <= (7.5 + D) * (7.5 + D))
        {
            Enqueue(queue, V);
            dist[V] = 1;
        }
    }
    while (!IsEmpty(queue))
    {
        int V = Dequeue(queue);
        for (int W = 0, d; W < N; W++)
        {
            d = JumpDist(point, V, W);
            if (d > D * D || OriginDist(point, W) <= 7.5 * 7.5)
            {
                continue;
            }
            if (dist[V] + 1 < dist[W])
            {
                dist[W] = dist[V] + 1;
                path[W] = V;
                Enqueue(queue, W);
            }
            if ((50 - abs(point[W].x)) <= D || (50 - abs(point[W].y)) <= D)
            {
                if (dist[W] < minDist)
                {
                    minDist = dist[W];
                    minPointIndex = W;
                }
                else if (dist[W] == minDist)
                {
                    int S1 = FindSource(path, minPointIndex);
                    int S2 = FindSource(path, W);
                    if (OriginDist(point, S1) > OriginDist(point, S2))
                    {
                        minPointIndex = W;
                    }
                }
            }
        }
    }
    return minPointIndex;
}

Queue CreateQueue(int size)
{
    Queue queue = (Queue)malloc(sizeof(QNode));
    queue->data = (int *)malloc(sizeof(int) * (size + 1));
    queue->front = queue->end = 0;
    queue->size = size;
    return queue;
}

bool IsEmpty(Queue queue)
{
    return queue->front == queue->end;
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