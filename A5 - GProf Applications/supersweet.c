// ALTERNATIVE SOLUTION
// Note : Almost as efficient, but 32 times more space-efficient

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

typedef unsigned long long int ull;

typedef struct
{
    int N;
    int n;
    ull *A;
} coupons;

coupons initempty(int);
void destroycoupons(coupons *);
coupons addcoupon(coupons, int);
int allcoupons(coupons);

coupons initempty(int N)
{
    coupons S;
    int m, i;

    S.N = N;
    S.n = 0;
    m = (N + 63) / 64;
    S.A = (ull *)malloc(m * sizeof(ull));
    for (i = 0; i < m; ++i) S.A[i] = 0;
    return S;
}

coupons addcoupon(coupons S, int c)
{
    if ((S.A[c >> 6] & (1ULL << (c & 63))) == 0)
    {
        ++S.n;
        S.A[c >> 6] |= (1ULL << (c & 63));
    }
    return S;
}

int allcoupons(coupons S)
{
    return (S.n == S.N) ? 1 : 0;
}

void destroycoupons(coupons *S)
{
    free(S->A);
}

#include "choco.c"
