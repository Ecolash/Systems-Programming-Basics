#ifndef __LISTUTILS_H
#define __LISTUTILS_H

/* Data type for storing sorted lists */
typedef struct {
   int n;      /* The number of items in the list */
   int *item;  /* The array storing the items in sorted order */
} slist;

/* Library functions on sorted lists */
slist listinit ( ) ;               /* Create an empty list */
void listkill ( slist * ) ;        /* Convert to empty list */
void listfree ( slist * ) ;        /* Free a list */
slist listcopy ( slist ) ;         /* Copy a list */
slist listadd ( slist , int ) ;    /* Insert an item in a list */
slist listsub ( slist , int ) ;    /* Delete an item from a list */
void  listprn ( slist ) ;          /* Print a list */

/* Data type for storing commands */
typedef struct {
   int operation;   /* one of the above operations on sorted lists */
   int arg1;        /* first argument (if any): an index in a table of lists */
   int arg2;        /* second argument (if any) */
} listop;

/* Operation names */
#define LISTINIT 1
#define LISTKILL 2
#define LISTFREE 3
#define LISTCOPY 4
#define LISTADD 5
#define LISTSUB 6
#define LISTPRN 7
#define ENDOFOPS 0

/* Read a set of commands from a file */
listop *freadops ( char * ) ;

#endif
