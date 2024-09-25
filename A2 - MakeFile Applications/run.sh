#!/bin/bash

MAIN0="./examples.c"
FILE1="../lib/order1/soln1.c"
FILE2="../lib/order2/soln2.c"
FILE3="../lib/order3/soln3.c"

cd lib/
make
cd ../app/
gcc -o a.out "$MAIN0" "$FILE1" "$FILE2" "$FILE3"
./a.out
cd ../lib/
make distclean
cd ../app/
rm -f a.out
echo "All tasks completed successfully!"
