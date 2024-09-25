#include <stdio.h>
#include <stdlib.h>
#include "secret.h"

int main ( int argc, char *argv[] )
{
   unsigned int guess;
   int h;

   if (argc != 2) {
      fprintf(stderr, "*** Run as: ./guessit YOUR_ROLL_NUMBER\n");
      exit(1);
   }

   if (!validRollNo(argv[1])) {
      fprintf(stderr, "Please run with a valid roll number\n");
      exit(1);
   }

   printf("Guessing the secret 12345\n");
   guess = 12345;
   h = hdistance(argv[1], guess);
   if (h == 0) printf("Wow, you are bang on the target. Well done.\n");
   else printf("Hmmm, you are %d bits away.\n", h);

   exit(0);
}
