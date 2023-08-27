#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const int MAXSIZE = 100000;

typedef char Account[11];
typedef char Password[17];

typedef struct DNode
{
    Account account;
    Password password;
    struct DNode *next;
} DNode, *Data;

typedef struct HNode
{
    int tableSize;
    Data *data;
} HNode, *HashTable;

HashTable CreateTable(int dataSize);
int NextPrime(int num);
void Login(HashTable table);
Data Find(HashTable table, const char *account);
int Hash(int data, int tableSize);
void Apply(HashTable table);

int main(void)
{
    int dataSize;
    scanf("%d", &dataSize);
    HashTable table = CreateTable(dataSize);
    char op;
    for (int i = 0; i < dataSize; i++)
    {
        scanf(" %c", &op);
        switch (op)
        {
        case 'L':
            Login(table);
            break;
        case 'N':
            Apply(table);
            break;
        default:
            break;
        }
    }
    return 0;
}

HashTable CreateTable(int dataSize)
{
    HashTable table = (HashTable)malloc(sizeof(HNode));
    table->tableSize = NextPrime(dataSize);
    table->data = (Data *)malloc(sizeof(Data) * table->tableSize);
    for (int i = 0; i < table->tableSize; i++)
    {
        table->data[i] = NULL;
    }
    return table;
}

int NextPrime(int num)
{
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

void Login(HashTable table)
{
    Account account;
    Password password;
    scanf("%s %s", account, password);
    Data position = Find(table, account);
    if (position)
    {
        if (strcmp(position->password, password))
        {
            printf("ERROR: Wrong PW\n");
        }
        else
        {
            printf("Login: OK\n");
        }
    }
    else
    {
        printf("ERROR: Not Exist\n");
    }
}

Data Find(HashTable table, const char *account)
{
    int index = Hash(atoi(account + 1), table->tableSize);
    Data position = table->data[index];
    while (position)
    {
        if (strcmp(position->account, account) == 0)
        {
            break;
        }
        position = position->next;
    }
    return position;
}

int Hash(int data, int tableSize)
{
    return data % tableSize;
}

void Apply(HashTable table)
{
    Account account;
    Password password;
    scanf("%s %s", account, password);
    Data position = Find(table, account);
    if (position)
    {
        printf("ERROR: Exist\n");
    }
    else
    {
        int index = Hash(atoi(account + 1), table->tableSize);
        Data data = (Data)malloc(sizeof(DNode));
        strcpy(data->account, account);
        strcpy(data->password, password);
        data->next = table->data[index];
        table->data[index] = data;
        printf("New: OK\n");
    }
}