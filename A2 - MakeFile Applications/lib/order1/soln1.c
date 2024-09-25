#include "soln1.h"

int findterm1(int n, recrel1 R)
{
    if (n == 0) return R.a0;
    else return R.c1 * findterm1(n - 1, R) + R.d;
}