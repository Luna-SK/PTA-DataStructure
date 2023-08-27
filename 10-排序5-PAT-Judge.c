#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct Node
{
    int perfectNum;
    int totalScore;
    int *scores;
} Node, *PtrToNode;

typedef struct DNode
{
    int userNum, probNum;
    Node *data;
    int *perfectScores;
} DNode, *Data;

Data CreateDataSet();
void Insert(Data dataSet, int id, int prob, int score);
void Sort(int *table, const Data dataSet);
bool Compare(Data dataSet, int a, int b);
void Print(Data dataSet, int *table);

int main(void)
{
    Data dataSet = CreateDataSet();
    int table[dataSet->userNum];
    for (int i = 0; i < dataSet->userNum; i++)
    {
        table[i] = i;
    }
    Sort(table, dataSet);
    Print(dataSet, table);
    return 0;
}

Data CreateDataSet()
{
    Data dataSet = (Data)malloc(sizeof(DNode));
    int submitNum;
    scanf("%d %d %d", &dataSet->userNum, &dataSet->probNum, &submitNum);
    dataSet->perfectScores = (int *)malloc(sizeof(int) * dataSet->probNum);
    for (int i = 0; i < dataSet->probNum; i++)
    {
        scanf("%d", &dataSet->perfectScores[i]);
    }
    dataSet->data = (Node *)malloc(sizeof(Node) * dataSet->userNum);
    for (int i = 0; i < dataSet->userNum; i++)
    {
        dataSet->data[i].totalScore = dataSet->data[i].perfectNum = 0;
        dataSet->data[i].scores = (int *)malloc(sizeof(int) * dataSet->probNum);
        for (int j = 0; j < dataSet->probNum; j++)
        {
            dataSet->data[i].scores[j] = -2;
        }
    }
    for (int i = 0, id, prob, score; i < submitNum; i++)
    {
        scanf("%d %d %d", &id, &prob, &score);
        Insert(dataSet, id - 1, prob - 1, score);
    }
    for (int i = 0; i < dataSet->userNum; i++)
    {
        bool noSubmit = true;
        for (int j = 0; j < dataSet->probNum; j++)
        {
            if (dataSet->data[i].scores[j] >= 0)
            {
                noSubmit = false;
                dataSet->data[i].totalScore += dataSet->data[i].scores[j];
            }
        }
        if (noSubmit)
        {
            dataSet->data[i].totalScore = -1;
        }
    }
    return dataSet;
}

void Insert(Data dataSet, int id, int prob, int score)
{
    if (score > dataSet->data[id].scores[prob])
    {
        dataSet->data[id].scores[prob] = score;
        if (score == dataSet->perfectScores[prob])
        {
            dataSet->data[id].perfectNum++;
        }
    }
}

void Sort(int *table, const Data dataSet)
{
    int Sedgewick[] = {2161, 929, 505, 209, 109, 41, 19, 5, 1, 0};
    int Si = 0;
    while (Sedgewick[Si] >= dataSet->userNum)
    {
        Si++;
    }
    for (int d = Sedgewick[Si]; d > 0; d = Sedgewick[++Si])
    {
        for (int i = d, j, temp; i < dataSet->userNum; i++)
        {
            temp = table[i];
            for (j = i; j >= d && Compare(dataSet, temp, table[j - d]); j -= d)
            {
                table[j] = table[j - d];
            }
            table[j] = temp;
        }
    }
}

bool Compare(Data dataSet, int a, int b)
{
    if (dataSet->data[a].totalScore > dataSet->data[b].totalScore)
    {
        return true;
    }
    else if (dataSet->data[a].totalScore < dataSet->data[b].totalScore)
    {
        return false;
    }
    else
    {
        if (dataSet->data[a].perfectNum > dataSet->data[b].perfectNum)
        {
            return true;
        }
        else if (dataSet->data[a].perfectNum < dataSet->data[b].perfectNum)
        {
            return false;
        }
        else
        {
            if (a < b)
            {
                return true;
            }
            else
            {
                return false;
            }
        }
    }
}

void Print(Data dataSet, int *table)
{
    for (int i = 0, rank; i < dataSet->userNum; i++)
    {
        if (dataSet->data[table[i]].totalScore < 0)
        {
            break;
        }
        if (i == 0 || (i > 0 && dataSet->data[table[i]].totalScore != dataSet->data[table[i - 1]].totalScore))
        {
            rank = i + 1;
            printf("%d %05d ", rank, table[i] + 1);
        }
        else
        {
            printf("%d %05d ", rank, table[i] + 1);
        }
        printf("%d ", dataSet->data[table[i]].totalScore);
        for (int j = 0; j < dataSet->probNum; j++)
        {
            if (dataSet->data[table[i]].scores[j] == -2)
            {
                printf("-");
            }
            else if (dataSet->data[table[i]].scores[j] == -1)
            {
                printf("0");
            }
            else
            {
                printf("%d", dataSet->data[table[i]].scores[j]);
            }
            if (j != dataSet->probNum - 1)
            {
                printf(" ");
            }
            else
            {
                printf("\n");
            }
        }
    }
}

// for (int i = 0; i < dataSet->userNum; i++)
// {
//     printf("%05d %d ", table[i] + 1, dataSet->data[table[i]].totalScore);
//     for (int j = 0; j < dataSet->probNum; j++)
//     {
//         printf("%d ", dataSet->data[table[i]].scores[j]);
//     }
//     printf("\n");
// }