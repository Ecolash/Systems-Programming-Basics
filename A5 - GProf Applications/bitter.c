#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

typedef struct {
   int N;
   int *A;
} coupons;
coupons initempty ( int ) ;
void destroycoupons ( coupons * ) ;
coupons addcoupon ( coupons, int ) ;
int allcoupons ( coupons ) ;

coupons initempty ( int N )
{
   coupons S;
   int i;

   S.N = N;
   S.A = (int *)malloc(N * sizeof(int));
   for (i=0; i<N; ++i) S.A[i] = 0;
   return S;
}

coupons addcoupon ( coupons S, int c )
{
   S.A[c] = 1;
   return S;
}

int allcoupons ( coupons S )
{
   int i, n;

   n = 0;
   for (i=0; i<S.N; ++i) {
      if (S.A[i]) ++n;
   }
   return (n == S.N) ? 1 : 0;
}

void destroycoupons ( coupons *S )
{
   free(S -> A);
}

#include "choco.c"
