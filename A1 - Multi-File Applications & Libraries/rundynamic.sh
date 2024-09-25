 #!/bin/bash

gcc -Wall -fPIC -c settype.c
gcc -Wall -fPIC -c setops.c
gcc -shared -o libsetutils.so settype.o setops.o
gcc -L. -Wl,-rpath=. chocolate.c -lsetutils
./a.out
gcc -L. -Wl,-rpath=. -DSTAT_MODE chocolate.c -lsetutils
./a.out
rm *.out *.so *.o
