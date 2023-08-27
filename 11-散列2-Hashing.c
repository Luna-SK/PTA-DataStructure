#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

const int MAXSIZE = 100000;

typedef struct HNode
{
    int tableSize;
    bool *data;
} HNode, *HashTable;

HashTable CreateTable(int m);
int NextPrime(int num);
void OutputPosition(HashTable table, int length);
int Hash(int data, int tableSize);

int main(void)
{
    int m, n;
    scanf("%d %d", &m, &n);
    HashTable table = CreateTable(m);
    OutputPosition(table, n);
    return 0;
}

HashTable CreateTable(int m)
{
    HashTable table = (HashTable)malloc(sizeof(HNode));
    table->tableSize = NextPrime(m);
    table->data = (bool *)malloc(sizeof(bool) * table->tableSize);
    for (int i = 0; i < table->tableSize; i++)
    {
        table->data[i] = false;
    }
    return table;
}

int NextPrime(int num)
{
    if (num == 1)
    {
        return 2;
    }
    num = num % 2 ? num + 2 : num + 1;
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

void OutputPosition(HashTable table, int length)
{
    int data, currentPosi, newPosi, k;
    for (int i = 0; i < length; i++)
    {
        scanf("%d", &data);
        newPosi = currentPosi = Hash(data, table->tableSize);
        k = 1;
        while (k < table->tableSize && table->data[newPosi])
        {
            newPosi = (currentPosi + k * k) % table->tableSize;
            k++;
        }
        if (k >= table->tableSize)
        {
            printf("-");
        }
        else
        {
            table->data[newPosi] = true;
            printf("%d", newPosi);
        }
        if (i < length - 1)
        {
            printf(" ");
        }
    }
    free(table->data);
    free(table);
}

int Hash(int data, int tableSize)
{
    return data % tableSize;
}