#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct Node
{
    int data;
    struct Node *left;
    struct Node *right;
    bool accessed;
} Node, *Tree;

Tree Insert(Tree root, int data)
{
    if (root == NULL)
    {
        root = (Tree)malloc(sizeof(Node));
        root->data = data;
        root->left = root->right = NULL;
        root->accessed = false;
    }
    else if (root->data < data)
    {
        root->right = Insert(root->right, data);
    }
    else if (root->data > data)
    {
        root->left = Insert(root->left, data);
    }
    return root;
}

void Free(Tree root)
{
    if (root == NULL)
    {
        return;
    }
    if (root->left != NULL)
    {
        Free(root->left);
    }
    if (root->right != NULL)
    {
        Free(root->right);
    }
    free(root);
}

bool Search(Tree root, int data)
{
    if (root == NULL)
    {
        return false;
    }
    if (root->accessed)
    {
        if (root->data == data)
        {
            return false;
        }
        while (root->data != data)
        {
            if (root->data > data)
            {
                root = root->left;
            }
            else
            {
                root = root->right;
            }
            if (root == NULL || (!root->accessed && root->data != data))
            {
                return false;
            }
        }
        root->accessed = true;
        return true;
    }
    else
    {
        if (root->data == data)
        {
            root->accessed = true;
            return true;
        }
        else
        {
            return false;
        }
    }
}

bool IsSameBST(Tree root, int *CompareBST, int length)
{
    for (int i = 0; i < length; i++)
    {
        if (!Search(root, CompareBST[i]))
        {
            return false;
        }
    }
    return true;
}

void ResetAccessed(Tree root)
{
    if (root == NULL)
    {
        return;
    }
    if (root->left != NULL)
    {
        ResetAccessed(root->left);
    }
    if (root->right != NULL)
    {
        ResetAccessed(root->right);
    }
    root->accessed = false;
}

int main(void)
{
    int N, L, data;
    scanf("%d", &N);
    Tree BST = NULL;
    while (N != 0)
    {
        scanf("%d", &L);
        int CompareBST[N];
        for (int i = 0; i < N; i++)
        {
            scanf("%d", &data);
            BST = Insert(BST, data);
        }
        for (int i = 0; i < L; i++)
        {
            ResetAccessed(BST);
            for (int j = 0; j < N; j++)
            {
                scanf("%d", &CompareBST[j]);
            }
            if (IsSameBST(BST, CompareBST, N))
            {
                printf("Yes\n");
            }
            else
            {
                printf("No\n");
            }
        }
        Free(BST);
        BST = NULL;
        scanf("%d", &N);
    }
    return 0;
}