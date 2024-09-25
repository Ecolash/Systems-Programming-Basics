#include "soln3.h"

int findterm3(int n, recrel3 R)
{
    if (n == 0) return R.a0;
    else if (n == 1) return R.a1;
    else if (n == 2) return R.a2;

    else return R.c2 * findterm3(n - 2, R) + R.c3 * findterm3(n - 3, R);
}