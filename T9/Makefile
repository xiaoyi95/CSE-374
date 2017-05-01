#!/bin/bash

makeT9: makeT9.o structures.o
	gcc -Wall -std=c11 -g -o makeT9 makeT9.o structures.o

makeT9.o: header.h makeT9.c structures.o
	gcc -Wall -std=c11 -g -c makeT9.c

structures.o: header.h structures.c
	gcc -Wall -std=c11 -g -c structures.c
clean:
	rm -f *.o makeT9 *~
