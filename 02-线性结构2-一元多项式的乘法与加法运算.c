#include <stdio.h>
#include <stdlib.h>

typedef struct PolyNode
{
    int c, e;
    struct PolyNode *next;
} *Polynomial;

Polynomial Read(void);
Polynomial Mult(Polynomial p1, Polynomial p2);
Polynomial Add(Polynomial p1, Polynomial p2);
void PrintPoly(Polynomial p);
Polynomial CreateEmptyPoly(void);
void AttachTailPoly(Polynomial *rear, int c, int e);
void AttachOrderPoly(Polynomial p, int c, int e);

int main(void)
{
    Polynomial p1 = Read();
    Polynomial p2 = Read();
    Polynomial product = Mult(p1, p2);
    Polynomial sum = Add(p1, p2);
    PrintPoly(product);
    PrintPoly(sum);
    return 0;
}

Polynomial Read()
{
    int n, c, e;
    scanf("%d", &n);
    Polynomial p = CreateEmptyPoly();
    Polynomial rear = p;
    for (int i = 0; i < n; i++)
    {
        scanf("%d %d", &c, &e);
        AttachTailPoly(&rear, c, e);
    }
    return p;
}

Polynomial Mult(Polynomial p1, Polynomial p2)
{
    Polynomial p = (Polynomial)malloc(sizeof(struct PolyNode));
    p1 = p1->next;
    p2 = p2->next;
    Polynomial t2;
    while (p1)
    {
        t2 = p2;
        for (t2 = p2; t2; t2 = t2->next)
        {
            AttachOrderPoly(p, p1->c * t2->c, p1->e + t2->e);
        }
        p1 = p1->next;
    }
    return p;
}

Polynomial Add(Polynomial p1, Polynomial p2)
{
    Polynomial p = (Polynomial)malloc(sizeof(struct PolyNode));
    Polynomial rear = p;
    p1 = p1->next;
    p2 = p2->next;
    while (p1 && p2)
    {
        if(p1->e == p2->e)
        {
            if (p1->c + p2->c == 0)
            {
                p1 = p1->next;
                p2 = p2->next;
            }
            else
            {
                AttachTailPoly(&rear, p1->c + p2->c, p1->e);
                p1 = p1->next;
                p2 = p2->next;
            }
        }
        else if(p1->e > p2->e)
        {
            AttachTailPoly(&rear, p1->c, p1->e);
            p1 = p1->next;
        }
        else
        {
            AttachTailPoly(&rear, p2->c, p2->e);
            p2 = p2->next;
        }
    }
    if (p1)
    {
        rear->next = p1;
    }
    if (p2)
    {
        rear->next = p2;
    }
    return p;
}

void PrintPoly(Polynomial p)
{
    int flag = 1;
    if (p->next == NULL)
    {
        printf("0 0\n");
        return;
    }
    for (p = p->next; p; p = p->next)
    {
        if (flag)
        {
            flag = 0;
        }
        else
        {
            printf(" ");
        }
        printf("%d %d", p->c, p->e);
    }
    printf("\n");
    return;
}

Polynomial CreateEmptyPoly()
{
    Polynomial p = (Polynomial)malloc(sizeof(struct PolyNode));
    p->next = NULL;
    return p;
}

void AttachTailPoly(Polynomial *rear, int c, int e)
{
    Polynomial p = (Polynomial)malloc(sizeof(struct PolyNode));
    (*rear)->next = p;
    p->c = c;
    p->e = e;
    p->next = NULL;
    *rear = (*rear)->next;
    return;
}

void AttachOrderPoly(Polynomial p, int c, int e)
{
    if (p->next == NULL)
    {
        AttachTailPoly(&p, c, e);
        return;
    }
    while (p->next->e > e)
    {
        p = p->next;
        if (p->next == NULL)
        {
            AttachTailPoly(&p, c, e);
            return;
        }
    }
    if(p->next->e == e)
    {
        if(p->next->c + c == 0)
        {
            Polynomial temp = p->next;
            p->next = p->next->next;
            free(temp);
        }
        else
        {
            p->next->c = p->next->c + c;
        }
    }
    else
    {
        Polynomial temp = (Polynomial)malloc(sizeof(struct PolyNode));
        temp->c = c;
        temp->e = e;
        temp->next = p->next;
        p->next = temp;
    }
    return;
}
