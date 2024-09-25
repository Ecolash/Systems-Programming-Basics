#include <stdio.h>
#include <stdlib.h>
#include <listutils.h>

/* Return an empty list. You should not pass an unitnitialized list as an argument to
   the list library functions.
*/
slist listinit ( )
{
   return (slist){0, NULL};
}

/* Since slist is a struct and its fields are to be modified, a pointer to it is passed. */
void listkill ( slist *L )
{
   if (L->item) free(L->item);
   L -> n = 0;
   L -> item = NULL;
}

/* Since slist is a struct and its fields are to be modified, a pointer to it is passed. */
void listfree ( slist *L )
{
   if (L -> item) free(L -> item);
   L -> n = 0;
   L -> item = NULL;
}

/* Return a copy of L. The return variable should be different from the argument. */
slist listcopy ( slist L )
{
   slist K;
   int i;

   K.n = L.n;
   if (L.n > 0) {
      K.item = (int *)malloc(L.n * sizeof(int));
      for (i=0; i<L.n; ++i) K.item[i] = L.item[i];
   } else {
      K.item = NULL;
   }

   return K;
}

/* NOTE:
   Our lists are sorted, so the insertion/deletion positions can be obtained by
   bimary search in O(log n) time. But copying the input to the output will take
   Theta(n) time anyway. For simplicity, linear search is therefore used.
*/

/* Add the element x to the list L, and return a new list storing L + x.
   A list can store multiple items of the same value.
   The return variable may or may not be the same as the argument.
*/
slist listadd ( slist L, int x )
{
   slist K;
   int i, j, inserted;

   /* The new list has size one more than the size of the argument */
   K.n = L.n + 1;
   K.item = (int *)malloc(K.n * sizeof(int));

   /* Copy loop with insertion */
   /* i is used for reading from L, and j is used for writing to K. */
   i = j = inserted = 0;
   while (i < L.n) {
      if ((L.item[i] < x) || (inserted)) { /* insertion position not reached or x is already inserted */
         K.item[j] = L.item[i];
         ++i; ++j;
      } else {                             /* insert x without consuming the next item from L */
         K.item[j] = x;
         ++j;
         inserted = 1;
      }
   }

   if (inserted == 0) K.item[j] = x;
   return K;
}

/* Remove the element x to the list L, and return a new list storing L - x.
   If x is not present in L, then L - x = L. Otherwise, only one copy of x in L is removed.
   The return variable may or may not be the same as the argument.
*/
slist listsub ( slist L, int x )
{
   slist K;
   int i, j, found, deleted;

   /* First, search for x in L */
   found = 0;
   for (i=0; i<L.n; ++i) if (L.item[i] == x) { found = 1; break; }

   /* If x is not present in L, return a copy of L */
   if (!found) return listcopy(L);

   K.n = L.n - 1;

   if (K.n == 0) return (slist){0, NULL};  /* Deletion from a list with only one item */

   /* Copy loop with deletion */
   /* i is used for reading from L, and j is used for writing to K. */
   K.item = (int *)malloc(K.n * sizeof(int));
   i = j = deleted = 0;
   while (i < L.n) {
      if ((L.item[i] < x) || (deleted)) {  /* If x is not yet found or deletion is already done */
         K.item[j] = L.item[i];
         ++i; ++j;
      } else {                             /* Skip copying x from L to K */
         ++i;
         deleted = 1;
      }
   }

   return K;
}

/* Print a list L from beginning to end (should be a sorted printing with possible repetitions */
void listprn ( slist L )
{
   int i;

   printf("{");
   for (i=0; i<L.n; ++i) {
      printf( " %d", L.item[i]);
      if (i < L.n - 1) printf(",");
   }
   printf(" }");
}

listop *freadops ( char *fname )
{
   FILE *fp;
   listop *C;
   int i, m;

   fp = (FILE *)fopen(fname, "r");

   if (fp == NULL) return NULL;  /* Unable to open input file */

   fscanf(fp, "%d", &m);         /* Read the number of operations */

   /* The operation list is terminated by the special operation ENDOFOPS, so we use
      m + 1 listops */
   C = (listop *)malloc((m + 1) * sizeof(listop));

   for (i=0; i<m; ++i) {
      fscanf(fp, "%d", &C[i].operation);
      if (C[i].operation == LISTINIT) {  /* No operands to listinit() */
         C[i].arg1 = C[i].arg2 = 0;
      } else {                           /* At least once operand for the operation */
         fscanf(fp, "%d", &C[i].arg1);
         if ( (C[i].operation == LISTADD) || (C[i].operation == LISTSUB) )  /* Two operands needed */
            fscanf(fp, "%d", &C[i].arg2);
         else                                                               /* One operand only */
            C[i].arg2 = 0;
      }
   }

   fclose(fp);

   /* Terminate the list of operations */
   C[m].operation = ENDOFOPS;
   C[m].arg1 = C[m].arg2 = 0;

   return C;
}