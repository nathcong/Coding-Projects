# Makefile for use with sorting.c

sorting: sorting.o
	gcc -std=c17 -Wall -g -o sorting sorting.o

sorting.o: sorting.c
	gcc -std=c17 -Wall -g -c sorting.c

clean:
	rm -rf sorting.o sorting
