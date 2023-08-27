#include <stdio.h>
#include <string.h>

const int MAXSTRING = 1000001;
const int MAXPATTERN = 100001;

void KMP(const char *string, const char *pattern);
void BuildMatch(int *match, const char *pattern, int size);

int main(void)
{
    char string[MAXSTRING];
    char pattern[MAXPATTERN];
    scanf("%s", string);
    int n;
    scanf("%d", &n);
    for (int i = 0; i < n; i++)
    {
        scanf("%s", pattern);
        KMP(string, pattern);
    }
    return 0;
}

void KMP(const char *string, const char *pattern)
{
    const int n = strlen(string);
    const int m = strlen(pattern);
    if (n < m)
    {
        printf("Not Found\n");
    }
    else
    {
        int match[m];
        BuildMatch(match, pattern, m);
        int s = 0, p = 0;
        while (s < n && p < m)
        {
            if (string[s] == pattern[p])
            {
                s++;
                p++;
            }
            else if (p > 0)
            {
                p = match[p - 1] + 1;
            }
            else
            {
                s++;
            }
        }
        if (p == m)
        {
            printf("%s\n", string + s - m);
        }
        else
        {
            printf("Not Found\n");
        }
    }
}

void BuildMatch(int *match, const char *pattern, int size)
{
    match[0] = -1;
    for (int i = 1, j; i < size; i++)
    {
        j = match[i - 1];
        while (j >= 0 && pattern[i] != pattern[j + 1])
        {
            j = match[j];
        }
        if (pattern[i] == pattern[j + 1])
        {
            match[i] = j + 1;
        }
        else
        {
            match[i] = -1;
        }
    }
}