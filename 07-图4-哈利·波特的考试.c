#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAXVNUM 100
#define INFINITY 100000

typedef struct ENode
{
    int V, W;
    int weight;
} ENode, *Edge;

typedef struct GNode
{
    int Nv, Ne;
    int G[MAXVNUM][MAXVNUM];
} GNode, *MGraph;

MGraph CreateGraph();
void InsertEdge(MGraph Graph, Edge E);
void FindAnimal(MGraph Graph);
void Floyd(MGraph Graph);

int main(void)
{
    MGraph Graph = CreateGraph();
    FindAnimal(Graph);
    return 0;
}

MGraph CreateGraph()
{
    MGraph Graph = (MGraph)malloc(sizeof(GNode));
    scanf("%d %d", &Graph->Nv, &Graph->Ne);
    for (int i = 0; i < Graph->Nv; i++)
    {
        for (int j = 0; j < Graph->Nv; j++)
        {
            if (i == j)
            {
                Graph->G[i][j] = 0;
            }
            else
            {
                Graph->G[i][j] = INFINITY;
            }
        }
    }
    Edge E = (Edge)malloc(sizeof(ENode));
    for (int i = 0; i < Graph->Ne; i++)
    {
        scanf("%d %d %d", &E->V, &E->W, &E->weight);
        InsertEdge(Graph, E);
    }
    free(E);
    return Graph;
}

void InsertEdge(MGraph Graph, Edge E)
{
    Graph->G[E->V - 1][E->W - 1] = E->weight;
    Graph->G[E->W - 1][E->V - 1] = E->weight;
}

void FindAnimal(MGraph Graph)
{
    Floyd(Graph);
    int min = INFINITY, max = 0, animal;
    for (int i = 0; i < Graph->Nv; i++)
    {
        max = 0;
        for (int j = 0; j < Graph->Nv; j++)
        {
            if (Graph->G[i][j] > max)
            {
                max = Graph->G[i][j];
            }
        }
        if (max == INFINITY)
        {
            printf("0");
            return;
        }
        if (max < min)
        {
            min = max;
            animal = i + 1;
        }
    }
    printf("%d %d", animal, min);
}

void Floyd(MGraph Graph)
{
    for (int k = 0; k < Graph->Nv; k++)
    {
        for (int i = 0; i < Graph->Nv; i++)
        {
            for (int j = 0; j < Graph->Nv; j++)
            {
                if (Graph->G[i][k] + Graph->G[k][j] < Graph->G[i][j])
                {
                    Graph->G[i][j] = Graph->G[i][k] + Graph->G[k][j];
                }
            }
        }
    }
}
