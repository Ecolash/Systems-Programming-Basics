#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <listutils.h>

#define MDEFAULT 100

int main ( int argc, char *argv[] )
{
   int i, m, t, j, k;
   FILE *fp;

   srand((unsigned int)time(NULL));
   m = (argc > 1) ? atoi(argv[1]) : MDEFAULT;
   if (m <= 0) m = MDEFAULT;
   fp = (FILE *)fopen("ops.txt", "w");
   if (fp == NULL) {
      fprintf(stderr, "*** Unable to write to command file\n");
      exit(1);
   }
   fprintf(fp, "%d\n", m);
   for (i=1; i<=m; ++i) {
      t = rand() % 16;
      if ((t == LISTKILL) || (t == LISTFREE))
         j = rand() % i;
      else
         j = (rand() % 4) ? i - 1 : rand() % i;
      k = 1 + rand() % 9;
      if (t == 0) {
         fprintf(fp, "%d\n", LISTINIT);
      } else if (t == 1) {
         fprintf(fp, "%d %d\n", LISTKILL, j);
      } else if (t == 2) {
         fprintf(fp, "%d %d\n", LISTFREE, j);
      } else if (t <= 4) {
         fprintf(fp, "%d %d\n", LISTCOPY, j);
      } else if (t <= 11) {
         fprintf(fp, "%d %d %d\n", LISTADD, j, k);
      } else {
         fprintf(fp, "%d %d %d\n", LISTSUB, j, k);
      }
   }
   fclose(fp);
}
