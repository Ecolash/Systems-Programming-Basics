#include "soln2.h"

int findterm2(int n, recrel2 R)
{
    if (n == 0) return R.a0;
    else if (n == 1) return R.a1;
    else return R.c1 * findterm2(n - 1, R) + R.c2 * findterm2(n - 2, R) + R.d;
}