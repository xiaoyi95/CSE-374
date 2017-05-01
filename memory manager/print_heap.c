// Xiaoyi Ling, Tiffany Luu
// CSE 374 Homework 6
// print_heap.c
// Mar 2 2017

// This program prints the address and size of each block
// to a file passed as parameter. The address and size are in
// the form of hex number.

// Includes the libraries and headers used
#include <inttypes.h>
#include "mem_impl.h"
#include "mem.h"

free_node* free_list;  // Access to the free list

// Inputs: FILE * f = the  file for printing the output lines
// Prints lines for each block on the free list to file f, including
// information on the block's address and the length of the block.
void print_heap(FILE * f) {
  // Code for print_heap here
  if (f == NULL) {
    fprintf(stderr, "Error: cannot open file");
  }
  if (free_list->next != NULL) {
    // assign temp variable to freelist
    free_node* temp = free_list->next;
    // loop through list, printing info about blocks
    while (temp != NULL) {
       fprintf(f, "0x%07lx 0x%07lx", (uintptr_t)temp, temp->size);
       fprintf(f, ", %lu\n", temp->size);  // Extra info: size in decimal
       temp = temp->next;
      }
  } else {
    fprintf(f, "The freelist is empty.\n");
  }
  fprintf(f, "\n");
}
