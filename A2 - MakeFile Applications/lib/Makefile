SHELL=/bin/sh
CC=gcc
CFLAGS=-Wall -O2 -I.
RM = rm -f

LIBNAME = librecrel.a

library:
	cd order1; make
	cd order2; make
	cd order3; make
	ar rcs librecrel.a order1/soln1.o order2/soln2.o order3/soln3.o 

clean:
	cd order1; make clean
	cd order2; make clean
	cd order3; make	clean

distclean:
	cd order1; make clean
	cd order2; make clean
	cd order3; make	clean
	-$(RM) $(LIBNAME)