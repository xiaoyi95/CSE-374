# Xiaoyi Ling, Tiffany Luu
# CSE 374 Homework 6
# Makefile
# Mar 2 2017

# Makefile for the memory manager program

# default target
bench: bench.o getmem.o freemem.o get_mem_stats.o print_heap.o mem_utils.o
	gcc -Wall -g -std=c11 -o bench bench.o getmem.o freemem.o get_mem_stats.o print_heap.o mem_utils.o

# individual source files
mem_utils.o: mem_utils.c mem.h mem_impl.h
	gcc -Wall -g -std=c11 -c mem_utils.c

get_mem_stats.o: get_mem_stats.c mem.h mem_impl.h
	gcc -Wall -g -std=c11 -c get_mem_stats.c

print_heap.o: print_heap.c mem.h mem_impl.h
	gcc -Wall -g -std=c11 -c print_heap.c

getmem.o: getmem.c mem.h mem_impl.h
	gcc -Wall -g -std=c11 -c getmem.c

freemem.o: freemem.c mem.h mem_impl.h
	gcc -Wall -g -std=c11 -c freemem.c

bench.o: bench.c mem.h mem_impl.h
	gcc -Wall -g -std=c11 -c bench.c

# runs program with the default values
test: bench
	./bench

# runs program calling getmem only
getmem: bench
	./bench 1000 100

# runs program with a fixed random seed for testing
nrand: bench
	./bench 1000 50 10 200 20000 1000

# removes build files and backups
clean:
	rm -f *.o data bench *~
