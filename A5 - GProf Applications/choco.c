double H ( int n )
{
   double h = 0;
   int i;

   for (i=1; i<=n; ++i) h += 1. / (double)i;
   return h;
}

int nexttrial ( int N )
{
   int cnt;
   coupons S;

   S = initempty(N);
   cnt = 0;
   while (!allcoupons(S)) {
      ++cnt;
      S = addcoupon(S,rand() % N);
   }
   destroycoupons(&S);
   return cnt;
}

int main ( int argc, char *argv[] )
{
   int N, ntrial, i, cntsum;
   clock_t t1, t2;

   if (argc != 3) {
      fprintf(stderr, "Run with two arguments: (1) No of coupons, and (2) No of trials\n");
      exit(1);
   }

   srand((unsigned int)time(NULL));
   N = atoi(argv[1]);
   ntrial = atoi(argv[2]);

   t1 = clock();
   cntsum = 0;
   for (i=0; i<ntrial; ++i) cntsum += nexttrial(N);
   t2 = clock();

   printf("Average number of purchases per trial = %lf\n", (double)cntsum / (double)ntrial);
   printf("Theoretical average                   = %lf\n", N * H(N));
   printf("Time per trial (in microseconds)      = %lf\n", (double)(t2 - t1) / (double)CLOCKS_PER_SEC / (double)ntrial * 1000000.);
   exit(0);
}
