#include <stdio.h>
#include <stdlib.h>
#include "settype.h"

numset setinit(int N)
{
    numset set;
    set = (int *)calloc((N + 1), sizeof(int));
    set[0] = N;
    return set;
}

numset setrand(int N)
{
    numset set;
    set = (int *)calloc((N + 1), sizeof(int));

    for (int i = 1; i <= N; i++)
    {
        int n = (rand() % 2 + 1);
        if (n == 0) set[i] = 0;
        else set[i] = 1;
    }
    return set;
}

numset setrandsize(int N, int t)
{
    numset set;
    set = (int *)calloc((N + 1), sizeof(int));
    set[0] = 0;

    int i = 0;
    while (i < t)
    {
        int n = (rand() % N + 1);
        if (set[n] ==  0) i++;
        set[n] = 1;
    }
    return set;
}

numset setdestroy(numset set)
{
    free(set);
    return NULL;
}