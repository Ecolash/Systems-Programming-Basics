#include <stdio.h>
#include <stdlib.h>
#include "setops.h"

void setprint(numset set)
{
    int N = set[0];
    printf("{");

    int j = 1;
    while(j <= N)
    {
        if (set[j] == 1)printf("%d ", j);
        j++;
    }
    printf("}\n");
}

int setsize(numset set)
{
    int N = set[0];
    int j = 1, i = 0;
    while (j <= N)
    {
        if (set[j] == 1)
            i++;
        j++;
    }
    return i;
}

numset setaddelt(numset set, int i)
{
    set[i] = 1;
    return set;
}

numset setdelelt(numset set, int i)
{
    set[i] = 0;
    return set;
}

numset setunion(numset A, numset B)
{
    numset Uset;
    int N = A[0];
    Uset = (int *)calloc((N + 1), sizeof(int));
    Uset[0] = N;
    for (int i = 1; i <= N; i++)
    {
        if (A[i] || B[i]) Uset[i] = 1;
    }
    return Uset;
}

numset setintersection(numset A, numset B)
{
    numset Iset;
    int N = A[0];
    Iset = (int *)calloc((N + 1), sizeof(int));

    Iset[0] = N;
    for (int i = 1; i <= N; i++)
    {
        if (A[i] && B[i]) Iset[i] = 1;
    }
    return Iset;
}
