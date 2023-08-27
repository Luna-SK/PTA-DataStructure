#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define MAXSIZE 64

typedef struct Data
{
    char element;
    int frequency;
} Data;

typedef struct Node
{
    char element;
    int frequency;
    struct Node *left;
    struct Node *right;
} Node, *Tree;

typedef struct Heap
{
    Tree *data;
    int size;
    int capacity;
} Heap, *MinHeap;

void AdjustSubMinHeap(MinHeap H, int rootIndex);
MinHeap CreateMinHeap(Data *data, int N);
void Insert(MinHeap H, Tree tree);
Tree DeleteMin(MinHeap H);
Tree CreateHuffmanTree(MinHeap H);
int WPLUtil(Tree root, int depth);
int WPL(Tree root);
Tree CreateNode();
void FreeTree(Tree root);
bool Judge(int correctWPL, Data *data, int N);

int main(void)
{
    int N, M;
    scanf("%d", &N);
    Data data[N];
    for (int i = 0; i < N; i++)
    {
        scanf(" %c %d", &data[i].element, &data[i].frequency);
    }
    MinHeap H = CreateMinHeap(data, N);
    Tree Huffman = CreateHuffmanTree(H);
    int correctWPL = WPL(Huffman);
    scanf("%d", &M);
    for (int i = 0; i < M; i++)
    {
        if (Judge(correctWPL, data, N))
        {
            printf("Yes\n");
        }
        else
        {
            printf("No\n");
        }
    }
    return 0;
}

void AdjustSubMinHeap(MinHeap H, int rootIndex)
{
    int parent, child;
    Tree temp = H->data[rootIndex];
    int frequency = temp->frequency;
    for (parent = rootIndex; parent * 2 <= H->size; parent = child)
    {
        child = parent * 2;
        if ((child != H->size) && (H->data[child]->frequency > H->data[child + 1]->frequency))
        {
            child++;
        }
        if (frequency <= H->data[child]->frequency)
        {
            break;
        }
        else
        {
            H->data[parent] = H->data[child];
        }
    }
    H->data[parent] = temp;
}

MinHeap CreateMinHeap(Data *data, int N)
{
    MinHeap H = (MinHeap)malloc(sizeof(Heap));
    H->data = (Tree *)malloc((N + 1) * sizeof(Tree));
    H->data[0] = (Tree)malloc(sizeof(Node));
    H->data[0]->frequency = -1;
    H->data[0]->element = '\0';
    H->data[0]->left = H->data[0]->right = NULL;
    H->size = N;
    H->capacity = N;
    for (int i = 1; i <= N; i++)
    {
        H->data[i] = (Tree)malloc(sizeof(Node));
        H->data[i]->element = data[i - 1].element;
        H->data[i]->frequency = data[i - 1].frequency;
        H->data[i]->left = H->data[i]->right = NULL;
    }
    for (int i = H->size / 2; i > 0; i--)
    {
        AdjustSubMinHeap(H, i);
    }
    return H;
}

void Insert(MinHeap H, Tree tree)
{
    int i = ++H->size;
    while (H->data[i / 2]->frequency > tree->frequency)
    {
        H->data[i] = H->data[i / 2];
        i /= 2;
    }
    H->data[i] = tree;
}

Tree DeleteMin(MinHeap H)
{
    Tree max = H->data[1];
    Tree temp = H->data[H->size--];
    int parent = 1;
    for (int child; parent * 2 <= H->size; parent = child)
    {
        child = parent * 2;
        if (child != H->size && H->data[child]->frequency > H->data[child + 1]->frequency)
        {
            child++;
        }
        if (temp->frequency <= H->data[child]->frequency)
        {
            break;
        }
        else
        {
            H->data[parent] = H->data[child];
        }
    }
    H->data[parent] = temp;
    return max;
}

Tree CreateHuffmanTree(MinHeap H)
{
    Tree parent;
    int N = H->size;
    for (int i = 1; i < N; i++)
    {
        parent = (Tree)malloc(sizeof(Node));
        parent->left = DeleteMin(H);
        parent->right = DeleteMin(H);
        parent->element = '\0';
        parent->frequency = parent->left->frequency + parent->right->frequency;
        Insert(H, parent);
    }
    return DeleteMin(H);
}

int WPLUtil(Tree root, int depth)
{
    if (root->left == NULL && root->right == NULL) //segmentation fault
    {
        return root->frequency * depth;
    }
    else
    {
        return WPLUtil(root->left, depth + 1) + WPLUtil(root->right, depth + 1);
    }
}

int WPL(Tree root)
{
    return WPLUtil(root, 0);
}

Tree CreateNode()
{
    Tree node = (Tree)malloc(sizeof(Node));
    node->element = '\0';
    node->frequency = 0;
    node->left = node->right = NULL;
    return node;
}

void FreeTree(Tree root)
{
    if (!root)
    {
        return;
    }
    FreeTree(root->left);
    FreeTree(root->right);
    free(root);
}

bool Judge(int correctWPL, Data *data, int N)
{
    bool flag = true;
    char element;
    char string[MAXSIZE];
    Tree tree = CreateNode();
    Tree temp;
    int wpl = 0;
    for (int i = 0; i < N; i++)
    {
        scanf(" %c %s", &element, string);
        temp = tree;
        for (int j = 0; j < strlen(string); j++)
        {
            if (string[j] == '0')
            {
                if (!temp->left)
                {
                    temp->left = CreateNode();
                }
                temp = temp->left;
            }
            else
            {
                if (!temp->right)
                {
                    temp->right = CreateNode();
                }
                temp = temp->right;
            }
            if (temp->frequency)
            {
                flag = false;
            }
        }
        if (temp->left || temp->right)
        {
            flag = false;
        }
        temp->element = element;
        temp->frequency = data[i].frequency * strlen(string);
        wpl += temp->frequency;
    }
    if (wpl != correctWPL)
    {
        flag = false;
    }
    FreeTree(tree);
    return flag;
}
