#!/bin/bash
make runapp
cp OPS.txt ops.txt
gcc -shared -o liblistutils.so listutils.o
gcc -o listapp -Wall -I. -L. -Wl,-rpath=. listapp.c -llistutils
valgrind ./listapp ops.txt
make clean
echo "All tasks completed successfully!"
