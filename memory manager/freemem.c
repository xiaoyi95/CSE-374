// Xiaoyi Ling, Tiffany Luu
// CSE 374 Homework 6
// freemem.c
// Mar 2 2017

// This program free the memory from user, it takes the
// pointer to the memory as an input and put the block
// of memory back to the freelist in the order of increasing
// address. It will also combine the block with existing ones
// in the list if the address is consistant

#include <inttypes.h>
#include "mem_impl.h"
#include "mem.h"
free_node* free_list;

// Inputs: void* p = pointer to a block of memory
// Frees a block of memory back into the free list. Merges the block with
// another if their addresses are next to each other
void freemem(void* p) {
  if (p == NULL) {
    return;
  }
  check_heap();  // Pre-check to make sure free_list is functional
  free_node* pNode = p - sizeof(free_node);
  free_node* temp = free_list;

  // loop through the list until the right location or the end of the list
  while (temp != NULL && temp->next != NULL && pNode > temp->next) {
    temp = temp->next;
  }
  if (temp != NULL && temp->next == NULL) {
    temp->next = pNode;
    pNode->next = NULL;
  } else {
    pNode->next = temp->next;
    temp->next = pNode;
  }

  temp = free_list;
  while (temp != NULL && temp->next != NULL) {
    // check if the blocks can be combined
    uintptr_t end = (uintptr_t)temp + temp->size + sizeof(free_node);
    if (end == (uintptr_t)temp->next) {
      // combine blocks
      temp->size = temp->size + temp->next->size + sizeof(free_node);
      if (temp->next->next != NULL) {
        temp->next = temp->next->next;
      } else {
        temp->next = NULL;
      }
    } else {
      temp =  temp->next;
    }
  }
  check_heap();  // Post-check to make sure free_list if functional
}
