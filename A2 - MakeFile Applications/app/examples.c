#include <stdio.h>

#include "../lib/order1/soln1.h"
#include "../lib/order2/soln2.h"
#include "../lib/order3/soln3.h"

int main()
{
    int n;
    printf("n = ");
    scanf("%d", &n);

    recrel1 R1 = {0, 2, 1};
    recrel2 R2 = {5, 6, 1, 1, -5};
    recrel3 R3 = {0, 1, 1, 2, 1};

    int ans1 = findterm1(n, R1);
    int ans2 = findterm2(n, R2);
    int ans3 = findterm3(n, R3);

    printf("ToH(%d) = %d \n", n, ans1);
    printf("Fib(%d) + 5 = %d \n", n, ans2);
    printf("Fib(%d) = %d \n", n, ans3);
    return 0;
}