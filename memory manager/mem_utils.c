// Xiaoyi Ling, Tiffany Luu
// CSE 374 Homework 6
// mem_utils.c
// Mar 2 2017

// This program has functions to check for problems in the free list, and also
// to print the start, end, and size of each block.
// It will be used in the freemem and getmem program.

// Includes the libraries and headers used
#include <assert.h>
#include <inttypes.h>
#include "mem_impl.h"
#include "mem.h"

free_node * free_list;  // Access to the free list
uintptr_t min_size;  // Minimum size of blocks on the free list

// Checks for problems in the free list, including: blocks ordered by increasing
// address, block sizes are positive numbers/above min value, blocks do not
// overlap or touch. If there is an error, the program will terminate.
void check_heap() {
  free_node* temp = free_list->next;
  while (temp != NULL && temp->next != NULL) {
    assert(temp < temp->next);
    assert((intptr_t)temp->size > 0);
    assert(temp->size >= min_size);
    uintptr_t endaddress = (uintptr_t)temp + temp->size + sizeof(free_node);
    assert(endaddress < (uintptr_t)temp->next);
    temp = temp->next;
  }
}

// Inputs: free_node * list = the pointer to the free list
// Prints the following information about each block on the free list:
// the start address, the end address, and the size of each block
void print_freelist(free_node * list) {
  if (list != NULL) {
    if (list->next != NULL) {
      printf("There are still blocks on the free_list\n");
      free_node * temp = list;
      while (temp->next != NULL) {
        temp = temp->next;
        uintptr_t endaddress = (uintptr_t)temp + temp->size + 16;
        void* endofblock = (void*)endaddress;
        printf("start of block pointer address: %p\n", temp);
        printf("start of block pointer decimal: %lu\n", (uintptr_t)temp);
        printf("end of block pointer address: %p\n", endofblock);
        printf("end of block pointer decimal: %lu\n", (uintptr_t)endofblock);
        printf("block size: %lu\n", temp->size);
      }
      printf("\n");
    } else {
      printf("There are no blocks on the free_list\n\n");
    }
  }
}
