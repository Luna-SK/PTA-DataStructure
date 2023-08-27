#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define null -1
#define MAXSIZE 10

typedef int Tree;
typedef Tree ElementType;
typedef struct TNode
{
    Tree left;
    Tree right;
} TreeNode;
TreeNode T[MAXSIZE];

typedef struct Queue
{
    ElementType *elements;
    int front;
    int rear;
    int size;
    int capacity;
} *Queue;

Tree CreateTree(TreeNode *T);
void PrintLeaves(Tree root);
Queue CreateQueue();
void Enqueue(Queue queue, Tree tree);
ElementType Dequeue(Queue queue);

int main(void)
{
    Tree root = CreateTree(T);
    PrintLeaves(root);
    return 0;
}

Tree CreateTree(TreeNode *T)
{
    int n, root;
    char left, right;
    scanf("%d", &n);
    bool check[n];
    for (int i = 0; i < n; i++)
    {
        check[i] = false;
    }
    for (int i = 0; i < n; i++)
    {
        scanf(" %c %c", &left, &right);
        if (left != '-')
        {
            T[i].left = left - '0';
            check[T[i].left] = true;
        }
        else
        {
            T[i].left = null;
        }
        if (right != '-')
        {
            T[i].right = right - '0';
            check[T[i].right] = true;
        }
        else
        {
            T[i].right = null;
        }
    }
    for (root = 0; root < n; root++)
    {
        if (!check[root])
        {
            break;
        }
    }
    return root;
}

void PrintLeaves(Tree root)
{
    Tree temp, leaves[MAXSIZE];
    int count = 0;
    if (root == null)
    {
        return;
    }
    Queue queue = CreateQueue();
    Enqueue(queue, root);
    while (queue->size)
    {
        temp = Dequeue(queue);
        if ((T[temp].left == null) && (T[temp].right == null))
        {
            leaves[count++] = temp;
        }
        if (T[temp].left != null)
        {
            Enqueue(queue, T[temp].left);
        }
        if (T[temp].right != null)
        {
            Enqueue(queue, T[temp].right);
        }
    }
    for (int i = 0; i < count - 1; i++)
    {
        printf("%d ", leaves[i]);
    }
    printf("%d", leaves[count - 1]);
}

Queue CreateQueue()
{
    Queue queue = (Queue)malloc(sizeof(struct Queue));
    queue->elements = (ElementType *)malloc(sizeof(ElementType) * MAXSIZE);
    queue->capacity = MAXSIZE;
    queue->size = 0;
    queue->front = 0;
    queue->rear = 0;
    return queue;
}

void Enqueue(Queue queue, Tree tree)
{
    queue->size++;
    queue->rear = (queue->rear + 1) % queue->capacity;
    queue->elements[queue->rear] = tree;
}

ElementType Dequeue(Queue queue)
{
    queue->size--;
    queue->front = (queue->front + 1) % queue->capacity;
    return queue->elements[queue->front];
}