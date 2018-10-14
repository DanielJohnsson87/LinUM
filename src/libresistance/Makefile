 CC = gcc
 P_NAME = program
 COMPILE_FLAGS = -Wall -c
 LINK_FLAGS = -Wall -o $(P_NAME)
 all:
	$(CC) $(COMPILE_FLAGS) libtest.c -o libtest.o
	$(CC) $(COMPILE_FLAGS) -fPIC calc_resistance.c -o calc_resistance.o
	$(CC) -shared -L. calc_resistance.o -o libcalc_resistance.so
	$(CC) libtest.o -L. -lcalc_resistance -o program 
 .PHONY: clean
 clean:
	-rm libtest.o calc_resistance.o
