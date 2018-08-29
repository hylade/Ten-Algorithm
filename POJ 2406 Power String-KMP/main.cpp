#include <iostream>
#include <cstdio>
#include <string.h>
using namespace std;

char str[10000];
int next1[10000];
int len;

void get_next(char* p)
{
    int pLen = strlen(p);
    next1[0] = -1;
    int k = -1;
    int j = 0;
    while (j < pLen)
    {
        if (k == -1 || p[j] == p[k])
        {
            j++, k++;
            if (p[j] != p[k])
                next1[j] = k;
            else
                next1[j] = next1[k];
        }
        else
            k = next1[k];
    }
}

int main()
{
    while (~scanf("%s", str) && strcmp(str, "."))
    {
        len = strlen(str);
        get_next(str);
        int ans = 1;
        if (len % (len - next1[len]) == 0)
            ans = len / (len - next1[len]);
        printf("%d", ans);
    }

    return 0;
}
