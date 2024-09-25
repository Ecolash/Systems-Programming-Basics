#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "settype.h"
#include "setops.h"

int howmanypackets(int N)
{
    int i = 0;
    numset S = setinit(N);

    while(setsize(S) < N)
    {
        int n = 1 + rand() % N;
        S = setaddelt(S, n);
        i++;

#ifdef STAT_MODE
#else
        printf("Packet %d has coupon %d, Available coupons: ", i, n);
        setprint(S);
#endif
    }
    return i;
}

int main()
{
    int N = 0;
    srand((unsigned int)time(NULL));
    printf("Number of coupons (N): ");
    scanf("%d", &N);

#ifdef STAT_MODE
    int sum = 0;
    printf("+++ Statistics mode\n");
    for (int i = 0; i < 1000; i++)
    {
        int x = howmanypackets(N);
        sum = sum + x;
    }
    float ans = sum/1000.0;
    printf("--- Average number of packets to buy = %f\n", ans);

#undef STAT_MODE
#else
    printf("+++ Interactive mode\n");
    int i = howmanypackets(N);
    printf("--- %d packets were bought\n\n", i);

#endif
    return 0;
}