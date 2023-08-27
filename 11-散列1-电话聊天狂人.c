#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

const int MAXSIZE = 1000000;

typedef char PhoneNum[12];

typedef struct LNode
{
    PhoneNum data;
    int count;
    struct LNode *next;
} LNode, *List;

typedef struct HNode
{
    int tableSize;
    List *heads;
} HNode, *HashTable;

HashTable CreateTable(int dataSize);
int NextPrime(int num);
void Insert(HashTable table, const char *phone);
int Hash(int data, int tableSize);
List Find(List p, const char *data);
void Print(HashTable table);

int main(void)
{
    int dataSize;
    scanf("%d", &dataSize);
    dataSize *= 2;
    HashTable table = CreateTable(dataSize);
    Print(table);
    return 0;
}

HashTable CreateTable(int dataSize)
{
    HashTable table = (HashTable)malloc(sizeof(HNode));
    table->tableSize = NextPrime(dataSize);
    table->heads = (List *)malloc(sizeof(List) * table->tableSize);
    for (int i = 0; i < table->tableSize; i++)
    {
        table->heads[i] = NULL;
    }
    PhoneNum phone;
    for (int i = 0; i < dataSize; i++)
    {
        scanf("%s", phone);
        Insert(table, phone);
    }
    return table;
}

int NextPrime(int num)
{
    num = num % 2 ? num + 2: num + 1;
    while (num < MAXSIZE)
    {
        int i;
        for (i = 3; i * i < num; i += 2)
        {
            if (num % i == 0)
            {
                break;
            }
        }
        if (i * i >= num)
        {
            break;
        }
        num += 2;
    }
    return num;
}

void Insert(HashTable table, const char *phone)
{
    int index = Hash(atoi(phone + 5), table->tableSize);
    List position = Find(table->heads[index], phone);
    if (position)
    {
        position->count++;
    }
    else
    {
        List node = (List)malloc(sizeof(LNode));
        strcpy(node->data, phone);
        node->count = 1;
        node->next = table->heads[index];
        table->heads[index] = node;
    }
}

int Hash(int data, int tableSize)
{
    return data % tableSize;
}

List Find(List p, const char *data)
{
    while (p && strcmp(p->data, data))
    {
        p = p->next;
    }
    return p;
}

void Print(HashTable table)
{
    int maxCount = 1, sameCount = 1;
    PhoneNum max = "";
    for (int i = 0; i < table->tableSize; i++)
    {
        for (List p = table->heads[i]; p; p = p->next)
        {
            if (p->count > maxCount)
            {
                maxCount = p->count;
                strcpy(max, p->data);
                sameCount = 1;
            }
            else if (p->count == maxCount)
            {
                sameCount++;
                if (strcmp(p->data, max) < 0)
                {
                    strcpy(max, p->data);
                }
            }
        }
    }
    printf("%s %d", max, maxCount);
    if (sameCount > 1)
    {
        printf(" %d", sameCount);
    }
    printf("\n");
}