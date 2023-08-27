#include <stdio.h>
#include <stdlib.h>

typedef struct Node
{
    int data;
    struct Node *left;
    struct Node *right;
    int height;
} Node, *Tree;

int Max(int, int);
int GetHeight(Tree);
Tree CreateTree();
Tree CreateNode(int);
Tree Insert(Tree, int);
Tree SingleLeftRotation(Tree);
Tree SingleRightRotation(Tree);
Tree DoubleLeftRightRotation(Tree);
Tree DoubleRightLeftRotation(Tree);

int main(void)
{
    Tree root = CreateTree();
    printf("%d", root->data);
    return 0;
}

int Max(int a, int b)
{
    return a > b ? a : b;
}

int GetHeight(Tree root)
{
    if (root == NULL)
    {
        return -1;
    }
    return Max(GetHeight(root->left), GetHeight(root->right)) + 1;
}

Tree CreateTree()
{
    int N, data;
    Tree root;
    scanf("%d", &N);
    for (int i = 0; i < N; i++)
    {
        scanf("%d", &data);
        root = Insert(root, data);
    }
    return root;
}

Tree CreateNode(int data)
{
    Tree node = (Tree)malloc(sizeof(Node));
    node->data = data;
    node->left = node->right = NULL;
    node->height = 0;
    return node;
}

Tree Insert(Tree root, int data)
{
    if (root == NULL)
    {
        root = CreateNode(data);
    }
    else if (data < root->data)
    {
        root->left = Insert(root->left, data);
        if (GetHeight(root->left) - GetHeight(root->right) == 2)
        {
            if (data < root->left->data)
            {
                root = SingleLeftRotation(root);
            }
            else
            {
                root = DoubleLeftRightRotation(root);
            }
        }
    }
    else if (data > root->data)
    {
        root->right = Insert(root->right, data);
        if (GetHeight(root->left) - GetHeight(root->right) == -2)
        {
            if (data > root->right->data)
            {
                root = SingleRightRotation(root);
            }
            else
            {
                root = DoubleRightLeftRotation(root);
            }
        }
    }
    root->height = Max(GetHeight(root->left), GetHeight(root->right)) + 1;
    return root;
}

Tree SingleLeftRotation(Tree root)
{
    Tree newRoot = root->left;
    root->left = newRoot->right;
    newRoot->right = root;
    root->height = Max(GetHeight(root->left), GetHeight(root->right)) + 1;
    newRoot->height = Max(GetHeight(newRoot->left), root->height) + 1;
    return newRoot;
}

Tree SingleRightRotation(Tree root)
{
    Tree newRoot = root->right;
    root->right = newRoot->left;
    newRoot->left = root;
    root->height = Max(GetHeight(root->left), GetHeight(root->right)) + 1;
    newRoot->height = Max(GetHeight(newRoot->right), root->height) + 1;
    return newRoot;
}

Tree DoubleLeftRightRotation(Tree root)
{
    root->left = SingleRightRotation(root->left);
    root = SingleLeftRotation(root);
    return root;
}

Tree DoubleRightLeftRotation(Tree root)
{
    root->right = SingleLeftRotation(root->right);
    root = SingleRightRotation(root);
    return root;
}
