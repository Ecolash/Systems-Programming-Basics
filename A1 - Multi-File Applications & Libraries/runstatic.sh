#!/bin/bash

gcc -Wall -c settype.c
gcc -Wall -c setops.c
ar rcs libsetutils.a settype.o setops.o
gcc -Wall -L. chocolate.c -lsetutils
./a.out
gcc -Wall -L. -DSTAT_MODE chocolate.c -lsetutils
./a.out
rm *.out *.a *.o
