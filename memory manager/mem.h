// Xiaoyi Ling, Tiffany Luu
// CSE 374 Homework 6
// mem.h
// Mar 2 2017

// Header file that allows user to use memory functions

#ifndef MEM_H
#define MEM_H

#include <inttypes.h>
#include <stdio.h>

// Declares memory functions
void* getmem(uintptr_t size);
void freemem(void* p);
void get_mem_stats(uintptr_t* total_size, uintptr_t* total_free,
                   uintptr_t* n_free_blocks);
void print_heap(FILE * f);

#endif
