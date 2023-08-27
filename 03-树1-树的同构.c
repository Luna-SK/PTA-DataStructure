#include <stdio.h>
#include <stdbool.h>

#define MAXSIZE 10
#define null -1

typedef int Tree;
typedef struct TNode
{
    char element;
    Tree left;
    Tree right;
} TreeNode;
TreeNode T1[MAXSIZE], T2[MAXSIZE];

Tree CreateTree(TreeNode *T);
bool Isomorphic(Tree R1, Tree R2);

int main(void)
{
    Tree R1, R2;
    R1 = CreateTree(T1);
    R2 = CreateTree(T2);
    if (Isomorphic(R1, R2))
    {
        printf("Yes\n");
    }
    else
    {
        printf("No\n");
    }
    return 0;
}

Tree CreateTree(TreeNode *T)
{
    int n, root;
    char left, right;
    scanf("%d", &n);
    if (n == 0)
    {
        return null;
    }
    bool check[n];
    for (int i = 0; i < n; i++)
    {
        check[i] = false;
    }
    for (int i = 0; i < n; i++)
    {
        scanf(" %c %c %c", &T[i].element, &left, &right);
        if (left == '-')
        {
            T[i].left = null;
        }
        else
        {
            T[i].left = left - '0';
            check[T[i].left] = true;
        }
        if (right == '-')
        {
            T[i].right = null;
        }
        else
        {
            T[i].right = right - '0';
            check[T[i].right] = true;
        }
    }
    for (root= 0; root < n; root++)
    {
        if (!check[root])
        {
            break;
        }
    }
    return root;
}

bool Isomorphic(Tree R1, Tree R2)
{
    if ((R1 == null) && (R2 == null))
    {
        return true;
    }
    if (((R1 == null) && (R2 != null)) || ((R1 != null) && (R2 == null)))
    {
        return false;
    }
    if (T1[R1].element != T2[R2].element)
    {
        return false;
    }
    if ((T1[R1].left == null) && (T2[R2].left == null))
    {
        return Isomorphic(T1[R1].right, T2[R2].right);
    }

    if ((T1[R1].left != null) && (T2[R2].left != null) && (T1[T1[R1].left].element == T2[T2[R2].left].element))
    {
        return (Isomorphic(T1[R1].left, T2[R2].left) && Isomorphic(T1[R1].right, T2[R2].right));
    }
    else
    {
        return (Isomorphic(T1[R1].left, T2[R2].right) && Isomorphic(T1[R1].right, T2[R2].left));
    }
}