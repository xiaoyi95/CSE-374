// Xiaoyi Ling, Tiffany Luu
// CSE 374 Homework 6
// getmem.c
// Mar 2 2017

// This program gives memory to the user by finding a block equal to or larger
// than the requested size from the free list. The blocks returned are in
// multiples of 16. If the block found is significantly larger than the request,
// the block will be split to the appropriate size to be returned to the user.
// If the block is only slightly larger than requested size, that block will be
// removed from the list and returned to the user.

// The minimum split size and thus minimum block size is currently 64, so all
// blocks on the free list should be greater than 64 and all blocks returned
// will have a size of at least 64, even for smaller calls. This threshold can
// be adjusted by the user.

// Includes the libraries and headers used
#include <inttypes.h>
#include <stdlib.h>
#include "mem_impl.h"
#include "mem.h"

#define MALLOC_SIZE 8000  // Default size for adding a block to the free list
#define MIN_SPLIT 64  // Split threshold and minimum size of return block

free_node * free_list;  // global variable for the free list
uintptr_t total_alloc;  // global variable for total of requested memory
uintptr_t min_size = MIN_SPLIT;  // global variable for min block size

// Declarations to for functions in the file
free_node * add_node(free_node *, uintptr_t);
free_node * split(free_node *, uintptr_t);
free_node * return_block(free_node *, uintptr_t);

// Inputs: uintptr_t size = size of the block of memory needed
// Returns a pointer to a block of memory that is at least size bytes large
void* getmem(uintptr_t size) {
  // Checks if the size passed in by the user is positive
  if ((intptr_t)size <= 0)
    return NULL;

  // Initializes the free list
  if (free_list == NULL) {
    free_list = (free_node*)malloc(sizeof(free_node));
    free_list->size = 0;
    free_list->next = NULL;
    total_alloc = 0;
  }

  check_heap();  // Pre-check to make sure free_list is functional
  void* paddress;  // Address of the block to be returned
  uintptr_t msize;  // Size of block needed from the free list

  // Rounds the size up to a multiple of 16
  if (size % 16 != 0) {
    msize = size + (16 - (size % 16));
  } else {
    msize = size;
  }

  // Returned block needs to be at least the defined minimum size
  // If rounded up the requested size to the minimum size
  if (msize < MIN_SPLIT)
    msize = MIN_SPLIT;

  // Checks the current list for a large enough block and returns it
  free_node * hold = return_block(free_list, msize);

  // If there is no block large enough on the free list, add a block
  if (hold != NULL) {
    paddress = hold + 1;
  } else {
    if (msize > MALLOC_SIZE) {  // Add a larger block
      hold = add_node(free_list, msize);
    } else {  // Add a block of the default size
      hold = add_node(free_list, MALLOC_SIZE);
    }
    if (hold == NULL)  // If malloc fails, return NULL
      return NULL;
    hold = return_block(free_list, msize);  // Search the free list again
    paddress = hold + 1;
  }

  check_heap();  // Post-check to make sure free_list is functional
  return paddress;
}

// Inputs: free_node * list = the free list, uintptr_t size = size of
// the block to be added
// Adds a node to the correct position on the free list
// Returns the address to the header of the added node
free_node * add_node(free_node * list, uintptr_t size) {
  free_node * temp = list;
  free_node * add = (free_node*)malloc(sizeof(free_node)+size);
  if (add == NULL)  // If malloc fails, return null
    return NULL;
  total_alloc += sizeof(free_node) + size;
  add->size = size;
  add->next = NULL;
  // Traverses the list and checks the addresses of the block
  while (temp->next != NULL) {
    if ((uintptr_t)add < (uintptr_t)(temp->next)) {
      add->next = temp->next;
      temp->next = add;
      return add;
    }
    temp = temp->next;
  }
  // If it reaches the end, add the block to the end of the list
  if (temp->next == NULL) {
    temp->next = add;
    return add;
  }
  return NULL;  // If adding the node fails
}

// Inputs: free_node * block = pointer to block that will be split
// uintptr_t size = size of the block that is needed
// Returns the block that has been split from the free list
free_node * split(free_node * block, uintptr_t size) {
  // Calculates the block address and updates the size of the blocks
  uintptr_t address = (uintptr_t)block + block->size - size;
  block->size = block->size - (size + sizeof(free_node));
  free_node * new = (void*)address;
  new->size = size;
  new->next = NULL;
  return new;
}

// Inputs: free_node * list = pointer to the free list
// uintptr_t size = size of the block that is needed from the free list
// Returns a block that has been removed from the free list, or NULL if
// the free list does not contain a large enough block
free_node * return_block(free_node * list, uintptr_t size) {
  free_node * temp = list;
  while (temp->next != NULL) {
    if (temp->next->size >= size) {  // If block is large enough
      if (temp->next->size - size > MIN_SPLIT) {  // Checks the split threshold
        return split(temp->next, size);
      } else {  // Returns the whole block if less than split threshold
        free_node * new = temp->next;
        temp->next = temp->next->next;
        return new;
      }
    } else {
      temp = temp->next;
    }
  }
  return NULL;
}


