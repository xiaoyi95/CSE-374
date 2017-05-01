// Xiaoyi Ling, Tiffany Luu
// CSE 374 Homework 6
// get_mem_stats.c
// Mar 2 2017

// Updates the inputted pointers with the current values. total_size is
// calculated as the total memory from the underlying system (malloc),
// total_free is the total memory on the free_list, including the headers,
// and n_free_blocks is the total number of blocks on the list.

// Includes the libraries and headers used
#include <inttypes.h>
#include "mem_impl.h"
#include "mem.h"

free_node * free_list;  // Access to the free list
uintptr_t total_alloc;  // Access to the total memory allocated from malloc

// Inputs: uintptr_t* total_size = total amount of storage in bytes in the
// memory manager, uintptr_t* total_free = total amount of storage in bytes on
// the free list, utintptr_t* n_free_blocks = number of blocks on the free list
// Updates the three inputs with their appropriate values
void get_mem_stats(uintptr_t* total_size, uintptr_t* total_free,
                   uintptr_t* n_free_blocks) {
  if (free_list != NULL) {  // Checks if the free list is initialized
    *total_size = total_alloc;
    uintptr_t freemem = 0;
    uintptr_t freeblocks = 0;
    if (free_list->next != NULL) {
      free_node * temp = free_list;
      while (temp->next != NULL) {  // Traverses the list
        temp = temp->next;
        freemem += temp->size + sizeof(free_node);
        freeblocks++;
      }
    }
    *total_free = freemem;
    *n_free_blocks = freeblocks;
  } else {  // If there is nothing on the free list, return zeros
    *total_size = 0;
    *total_free = 0;
    *n_free_blocks = 0;
  }
}
