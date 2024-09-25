#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

typedef struct {
   int N;
   int size;
   int *A;
} coupons;

coupons initempty ( int ) ;
void destroycoupons ( coupons * ) ;
coupons addcoupon ( coupons, int ) ;
int allcoupons ( coupons ) ;

coupons initempty ( int N )
{
   coupons S;
   S.A = (int *)malloc(N * sizeof(int));
   for (int i = 0; i < N; ++i) S.A[i] = 0;
   S.N = N;
   S.size = 0;
   return S;
}

coupons addcoupon ( coupons S, int c )
{
   if(S.A[c]==0){
      S.A[c]++;
      S.size++;
   }
   return S;
}

int allcoupons (coupons S )
{
   return (S.size == S.N) ? 1 : 0;
}

void destroycoupons ( coupons *S )
{
   free(S -> A);
}

#include "choco.c"