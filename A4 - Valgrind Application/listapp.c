#include <stdio.h>
#include <stdlib.h>
#include <listutils.h>

int main ( int argc, char *argv[] )
{
   listop *OPS;
   slist *T;
   int s, m;

   if (argc == 1) {
      fprintf(stderr, "*** You should run listapp with the command-file name\n");
      exit(1);
   }

   OPS = freadops(argv[1]);
   if (OPS == NULL) {
      fprintf(stderr, "*** I am unable to read the command file\n");
      exit(2);
   }

   T = (slist *)malloc(sizeof(slist));
   T[0] = listinit();
   s = 1;
   m = 0;
   printf("%%0 = "); listprn(T[0]); printf("\n");

   while (1) {
      if (OPS -> operation == ENDOFOPS) break;
      ++m;
      if (m >= s) {
         s *= 2;
         T = (slist *)realloc(T, s * sizeof(slist));
      }
      if (OPS -> operation == LISTINIT) {
         printf("$ init()\n");
         T[m] = listinit();
      } 
      
      else if (OPS -> operation == LISTKILL) {
         printf("$ kill(%%%d)\n", OPS -> arg1);
         listfree(&T[OPS -> arg1]);
         T[m] = listcopy(T[OPS -> arg1]);
      } 
      
      else if (OPS -> operation == LISTFREE) {
         printf("$ free(%%%d)\n", OPS -> arg1);
         listfree(&T[OPS -> arg1]);
         T[m] = listcopy(T[OPS -> arg1]);
      } 
      
      else if (OPS -> operation == LISTCOPY) {
         printf("$ %%%d\n", OPS -> arg1);
         T[m] = listcopy(T[OPS -> arg1]);
      } 
      
      else if (OPS -> operation == LISTADD) {
         printf("$ %%%d + %d\n", OPS -> arg1, OPS -> arg2);
         T[m] = listadd(T[OPS -> arg1], OPS -> arg2);
      } 
      
      else if (OPS -> operation == LISTSUB) {
         printf("$ %%%d - %d\n", OPS -> arg1, OPS -> arg2);
         T[m] = listsub(T[OPS -> arg1], OPS -> arg2);
      } 
      
      else {
         printf("$ ???\n");
         T[m] = listinit();
      }
      printf("  %%%d = ", m); listprn(T[m]); printf("\n");
      ++OPS;
   }

   for(int i = 0; i <= m;i++) listfree(&T[i]);
   free(T);
   OPS-= m;
   free(OPS);
   exit(0);
}