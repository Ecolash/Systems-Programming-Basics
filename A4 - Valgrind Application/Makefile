SHELL := /usr/bin/bash
CC := gcc
CFLAGS = -I. -Wall -fPIC

library: listutils.o
	$(CC) -shared -o liblistutils.so listutils.o

listutils.o: listutils.h

app: library listapp.c
	$(CC) -o listapp -Wall -I. -L. -Wl,-rpath=. listapp.c -llistutils

runapp: app
	valgrind ./listapp ops.txt

genops: library genops.c
	$(CC) -o genops -Wall -I. -L. -Wl,-rpath=. genops.c -llistutils

clean:
	-rm -f listutils.o liblistutils.so listapp genops ops.txt
