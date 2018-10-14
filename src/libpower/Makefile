all:		test.o libpower.a
		gcc -o test test.c -L. -lpower

lib:		libpower.a
libpower.a:	libpower.o
		ar crv libpower.a libpower.o

libpower.o:	libpower.h libpower.c
		gcc -c libpower.c

clean:
		rm -f libpower.a
		rm -f *.o
		rm -f test
		rm -f *.c~
		rm -f *.h~

